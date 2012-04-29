/*
* Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locations_private.h>
#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "TIZEN_N_LOCATION_MANAGER"

/*
* Internal Macros
*/
#define LOCATIONS_CHECK_CONDITION(condition,error,msg)	\
		if(condition) {} else \
		{ LOGE("[%s] %s(0x%08x)",__FUNCTION__, msg,error); return error;}; \

#define LOCATIONS_NULL_ARG_CHECK(arg)	\
	LOCATIONS_CHECK_CONDITION(arg != NULL,LOCATION_BOUNDS_ERROR_INVALID_PARAMETER,"LOCATION_BOUNDS_ERROR_INVALID_PARAMETER") \

static void __free_position_list(gpointer data)
{
	if (data == NULL) return;

	LocationPosition *position = (LocationPosition*) data;
	location_position_free(position);
}

static location_bounds_type_e __convert_bounds_type(LocationBoundaryType type)
{
	location_bounds_type_e ret;
	switch(type)
	{
	case LOCATION_BOUNDARY_NONE:
	case LOCATION_BOUNDARY_RECT:
		ret = LOCATION_BOUNDS_RECT;
		break;
	case LOCATION_BOUNDARY_CIRCLE:
		ret = LOCATION_BOUNDS_CIRCLE;
		break;
	case LOCATION_BOUNDARY_POLYGON:
		ret = LOCATION_BOUNDS_POLYGON;
		break;
	}
	return ret;
}

int location_bounds_create_rect(location_coords_s top_left, location_coords_s bottom_right, location_bounds_h* bounds)
{
	LOCATIONS_NULL_ARG_CHECK(bounds);
	LOCATIONS_CHECK_CONDITION(top_left.latitude>=-90 && top_left.latitude<=90,LOCATION_BOUNDS_ERROR_INVALID_PARAMETER,"LOCATION_BOUNDS_ERROR_INVALID_PARAMETER");
	LOCATIONS_CHECK_CONDITION(top_left.longitude>=-180 && top_left.longitude<=180,LOCATION_BOUNDS_ERROR_INVALID_PARAMETER, "LOCATION_BOUNDS_ERROR_INVALID_PARAMETER");
	LOCATIONS_CHECK_CONDITION(bottom_right.latitude>=-90 && bottom_right.latitude<=90,LOCATION_BOUNDS_ERROR_INVALID_PARAMETER, "LOCATION_BOUNDS_ERROR_INVALID_PARAMETER");
	LOCATIONS_CHECK_CONDITION(bottom_right.longitude>=-180 && bottom_right.longitude<=180,LOCATION_BOUNDS_ERROR_INVALID_PARAMETER, "LOCATION_BOUNDS_ERROR_INVALID_PARAMETER");

	LocationPosition *lt = location_position_new(0, top_left.latitude, top_left.longitude, 0, LOCATION_STATUS_2D_FIX);
	if (lt ==NULL)
	{
		LOGE("[%s] LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_position_new", __FUNCTION__, LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY);
		return LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY;
	}

	LocationPosition *rb = location_position_new(0, bottom_right.latitude, bottom_right.longitude, 0, LOCATION_STATUS_2D_FIX);
	if (rb ==NULL)
	{
		LOGE("[%s] LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_position_new", __FUNCTION__, LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY);
		location_position_free (lt);
		return LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY;
	}

	LocationBoundary *boundary = location_boundary_new_for_rect(lt, rb);
	location_position_free (rb);
	location_position_free (lt);

	if(!boundary)
	{
		LOGE("[%s] LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_boundary_new_for_rect", __FUNCTION__, LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY);
		return LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY;
	}

	*bounds = (location_bounds_h)boundary;
	return LOCATION_BOUNDS_ERROR_NONE;
}

int location_bounds_create_circle(location_coords_s center, double radius, location_bounds_h* bounds)
{
	LOCATIONS_NULL_ARG_CHECK(bounds);
	LOCATIONS_CHECK_CONDITION(radius>=0,LOCATION_BOUNDS_ERROR_INVALID_PARAMETER,"LOCATION_BOUNDS_ERROR_INVALID_PARAMETER");
	LOCATIONS_CHECK_CONDITION(center.latitude>=-90 && center.latitude<=90,LOCATION_BOUNDS_ERROR_INVALID_PARAMETER,"LOCATION_BOUNDS_ERROR_INVALID_PARAMETER");
	LOCATIONS_CHECK_CONDITION(center.longitude>=-180 && center.longitude<=180,LOCATION_BOUNDS_ERROR_INVALID_PARAMETER, "LOCATION_BOUNDS_ERROR_INVALID_PARAMETER");

	LocationPosition *ct = location_position_new(0, center.latitude, center.longitude, 0, LOCATION_STATUS_2D_FIX);
	if (ct ==NULL)
	{
		LOGE("[%s] LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_position_new", __FUNCTION__, LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY);
		return LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY;
	}

	LocationBoundary *boundary = location_boundary_new_for_circle(ct,radius);
	location_position_free (ct);

	if(!boundary)
	{
		LOGE("[%s] LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_boundary_new_for_circle", __FUNCTION__, LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY);
		return LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY;
	}

	*bounds = (location_bounds_h)boundary;
	return LOCATION_BOUNDS_ERROR_NONE;
}

int location_bounds_create_polygon(location_coords_s* coords_list, int length, location_bounds_h* bounds)
{
	LOCATIONS_NULL_ARG_CHECK(coords_list);
	LOCATIONS_NULL_ARG_CHECK(bounds);
	LOCATIONS_CHECK_CONDITION(length>=3,LOCATION_BOUNDS_ERROR_INVALID_PARAMETER,"LOCATION_BOUNDS_ERROR_INVALID_PARAMETER");

	int i;
	GList* position_list = NULL;
	LocationPosition *position = NULL;
	bool isValid;
	
	for(i=0;i<length;i++)
	{
		if(coords_list[i].latitude < -90 || coords_list[i].latitude > 90 || coords_list[i].longitude < -180 || coords_list[i].longitude > 180)
		{
			LOGE("[%s] LOCATION_BOUNDS_ERROR_INVALID_PARAMETER(0x%08x)", __FUNCTION__, LOCATION_BOUNDS_ERROR_INVALID_PARAMETER);
			isValid = FALSE;
			break;
		}	

		position = location_position_new(0, coords_list[i].latitude, coords_list[i].longitude, 0.0, LOCATION_STATUS_2D_FIX);
		position_list = g_list_append(position_list,position);
		location_position_free(position);
		isValid = TRUE;
	}

	if(!isValid)
	{
		g_list_free_full(position_list, (GDestroyNotify)__free_position_list);
		return LOCATION_BOUNDS_ERROR_INVALID_PARAMETER;
	}
		
	if (position_list ==NULL)
	{
		LOGE("[%s] LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_position_new", __FUNCTION__, LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY);
		return LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY;
	}

	LocationBoundary *boundary =  location_boundary_new_for_polygon(position_list);

	if(!boundary)
	{
		LOGE("[%s] LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_boundary_new_for_rect", __FUNCTION__, LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY);
		return LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY;
	}

	*bounds = (location_bounds_h)boundary;
	return LOCATION_BOUNDS_ERROR_NONE;
}

bool location_bounds_is_contains_coordinates(location_bounds_h bounds, location_coords_s coords)
{
	if (!bounds)
		return FALSE;

	if (coords.latitude < -90 ||  coords.latitude > 90 || coords.longitude < -180 || coords.longitude > 180)
		return FALSE;

	LocationPosition *pos = location_position_new(0, coords.latitude, coords.longitude, 0, LOCATION_STATUS_2D_FIX);
	if (!pos)
		return FALSE;

	gboolean is_inside = location_boundary_if_inside((LocationBoundary*)bounds, pos);
	location_position_free (pos);
	bool result = is_inside?TRUE:FALSE;
	return result;
}

int location_bounds_get_type(location_bounds_h bounds, location_bounds_type_e *type)
{
	LOCATIONS_NULL_ARG_CHECK(bounds);
	LOCATIONS_NULL_ARG_CHECK(type);	
	*type = __convert_bounds_type(((LocationBoundary*)bounds)->type);
	return LOCATION_BOUNDS_ERROR_NONE;
}

int location_bounds_get_rect_coords(location_bounds_h bounds, location_coords_s  *top_left, location_coords_s  *bottom_right)
{
	LOCATIONS_NULL_ARG_CHECK(bounds);
	LOCATIONS_NULL_ARG_CHECK(top_left);
	LOCATIONS_NULL_ARG_CHECK(bottom_right);
	if( __convert_bounds_type(((LocationBoundary*)bounds)->type) != LOCATION_BOUNDS_RECT)
	{
		LOGE("[%s] LOCATION_BOUNDS_ERROR_INCORRECT_TYPE(0x%08x)", __FUNCTION__, LOCATION_BOUNDS_ERROR_INCORRECT_TYPE);
	}

	top_left->latitude = ((LocationBoundary*)bounds)->rect.left_top->latitude;
	top_left->longitude = ((LocationBoundary*)bounds)->rect.left_top->longitude;
	bottom_right->latitude =((LocationBoundary*)bounds)->rect.right_bottom->latitude;
	bottom_right->longitude = ((LocationBoundary*)bounds)->rect.right_bottom->longitude;
	return LOCATION_BOUNDS_ERROR_NONE;
}

int location_bounds_get_circle_coords(location_bounds_h bounds, location_coords_s  *center, double *radius)
{
	LOCATIONS_NULL_ARG_CHECK(bounds);
	LOCATIONS_NULL_ARG_CHECK(center);
	LOCATIONS_NULL_ARG_CHECK(radius);
	if( __convert_bounds_type(((LocationBoundary*)bounds)->type) != LOCATION_BOUNDS_CIRCLE)
	{
		LOGE("[%s] LOCATION_BOUNDS_ERROR_INCORRECT_TYPE(0x%08x)", __FUNCTION__, LOCATION_BOUNDS_ERROR_INCORRECT_TYPE);
	}

	center->latitude = ((LocationBoundary*)bounds)->circle.center->latitude;
	center->longitude =((LocationBoundary*)bounds)->circle.center->longitude;
	*radius = ((LocationBoundary*)bounds)->circle.radius;
	return LOCATION_BOUNDS_ERROR_NONE;
}

int location_bounds_foreach_polygon_coords(location_bounds_h bounds, polygon_coords_cb callback, void *user_data)
{
	LOCATIONS_NULL_ARG_CHECK(bounds);
	LOCATIONS_NULL_ARG_CHECK(callback);	
	if( __convert_bounds_type(((LocationBoundary*)bounds)->type) != LOCATION_BOUNDS_POLYGON)
	{
		LOGE("[%s] LOCATION_BOUNDS_ERROR_INCORRECT_TYPE(0x%08x)", __FUNCTION__, LOCATION_BOUNDS_ERROR_INCORRECT_TYPE);
	}

	GList *list = ((LocationBoundary*)bounds)->polygon.position_list;
	while(list)
	{
		LocationPosition *pos = list->data;
		location_coords_s coords;
		coords.latitude = pos->latitude;
		coords.longitude = pos->longitude;
		
		if ( callback(coords, user_data) != TRUE )
		{
			LOGI("[%s] User quit the loop ",  __FUNCTION__);
			break;
		}
		list = g_list_next(list);
	}
	return LOCATION_BOUNDS_ERROR_NONE;
}

int location_bounds_destroy(location_bounds_h bounds)
{
	LOCATIONS_NULL_ARG_CHECK(bounds);
	location_boundary_free((LocationBoundary*)bounds);
	return LOCATION_BOUNDS_ERROR_NONE;
}

