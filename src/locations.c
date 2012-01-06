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
	LOCATIONS_CHECK_CONDITION(arg != NULL,LOCATIONS_ERROR_INVALID_PARAMETER,"LOCATIONS_ERROR_INVALID_PARAMETER")


/*
* Internal Implementation
*/

int _convert_error_code(int code,char *func_name)
{
	int ret;
	char* msg = "LOCATIONS_ERROR_NONE";
	switch(code)
	{
		case LOCATION_ERROR_NONE:
			ret = LOCATIONS_ERROR_NONE;
			msg = "LOCATIONS_ERROR_NONE";
			break;
		case LOCATION_ERROR_NETWORK_FAILED:
			ret = LOCATIONS_ERROR_NETWORK_FAILED;
			msg = "LOCATIONS_ERROR_NETWORK_FAILED";
			break;
		case LOCATION_ERROR_NOT_ALLOWED:
			ret = LOCATIONS_ERROR_GPS_SETTING_OFF;
			msg = "LOCATIONS_ERROR_GPS_SETTING_OFF";
			break;
		case  LOCATION_ERROR_NOT_AVAILABLE:
		case LOCATION_ERROR_CONFIGURATION:
		case LOCATION_ERROR_PARAMETER:
		case  LOCATION_ERROR_UNKNOWN:
		default:
			msg = "LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE";
			ret = LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;	
	}
	LOGE("[%s] %s(0x%08x) : core fw error(0x%x)",func_name,msg, ret, code);
	return ret;	
}

void cb_service_updated (GObject *self,  guint type, gpointer data, gpointer accuracy, gpointer userdata)
{
	LOGI("[%s] Callback function has been invoked. ",__FUNCTION__);
	location_manager_s * handle = (location_manager_s*)userdata;
	if( type == VELOCITY_UPDATED && handle->user_cb[_LOCATIONS_EVENT_TYPE_VELOCITY])
	{
		LocationVelocity *vel = (LocationVelocity*) data;
		LOGI("[%s] Current velocity: timestamp : %d, speed: %f, direction : %f, climb : %f",  __FUNCTION__ ,	vel->timestamp, vel->speed,	vel->direction,	vel->climb);
		((location_velocity_updated_cb)handle->user_cb[_LOCATIONS_EVENT_TYPE_VELOCITY])(vel->speed, vel->direction,vel->climb, vel->timestamp ,handle->user_data[_LOCATIONS_EVENT_TYPE_VELOCITY]);
	}
	if( type == POSITION_UPDATED && handle->user_cb[_LOCATIONS_EVENT_TYPE_POSITION])
	{
		LocationPosition *pos = (LocationPosition*) data;
		LOGI("[%s] Current position: timestamp : %d, latitude : %f, altitude: %f, longitude: %f",  __FUNCTION__ ,	 pos->timestamp, pos->latitude,	pos->altitude,	pos->longitude);
		((location_position_updated_cb)handle->user_cb[_LOCATIONS_EVENT_TYPE_POSITION])(pos->latitude, pos->longitude,pos->altitude, pos->timestamp ,handle->user_data[_LOCATIONS_EVENT_TYPE_POSITION]);
	}
}

void cb_service_enabled (GObject *self, guint status, gpointer userdata)
{
	LOGI("[%s] Callback function has been invoked. ",__FUNCTION__);
	location_manager_s * handle = (location_manager_s*)userdata;
	if(handle->user_cb[_LOCATIONS_EVENT_TYPE_SERVICE_STATE])
	{
		((location_service_state_changed_cb)handle->user_cb[_LOCATIONS_EVENT_TYPE_SERVICE_STATE])(LOCATIONS_SERVICE_ENABLED,handle->user_data[_LOCATIONS_EVENT_TYPE_SERVICE_STATE]);
	}
}

void cb_service_disabled (GObject *self, guint status, gpointer userdata)
{
	LOGI("[%s] Callback function has been invoked. ",__FUNCTION__);
	location_manager_s * handle = (location_manager_s*)userdata;
	if( handle->user_cb[_LOCATIONS_EVENT_TYPE_SERVICE_STATE] )
		((location_service_state_changed_cb)handle->user_cb[_LOCATIONS_EVENT_TYPE_SERVICE_STATE])(LOCATIONS_SERVICE_DISABLED,handle->user_data[_LOCATIONS_EVENT_TYPE_SERVICE_STATE]);
}

void cb_zone_in (GObject *self, guint type, gpointer position, gpointer accuracy, gpointer userdata)
{
	location_manager_s * handle = (location_manager_s*)userdata;
	if( handle->user_cb[_LOCATIONS_EVENT_TYPE_BOUNDARY] )
	{
		LocationPosition *pos = (LocationPosition*) position;
		((location_zone_changed_cb)handle->user_cb[_LOCATIONS_EVENT_TYPE_BOUNDARY])(LOCATIONS_BOUNDARY_IN,	pos->latitude,pos->longitude,pos->altitude, pos->timestamp ,handle->user_data[_LOCATIONS_EVENT_TYPE_BOUNDARY]); 
	}
}

void cb_zone_out (GObject *self, guint type, gpointer position, gpointer accuracy, gpointer userdata)
{
	location_manager_s * handle = (location_manager_s*)userdata;
	if( handle->user_cb[_LOCATIONS_EVENT_TYPE_BOUNDARY] )
	{
		LocationPosition *pos = (LocationPosition*) position;
		((location_zone_changed_cb)handle->user_cb[_LOCATIONS_EVENT_TYPE_BOUNDARY])(LOCATIONS_BOUNDARY_OUT,	pos->latitude,pos->longitude,pos->altitude, pos->timestamp ,handle->user_data[_LOCATIONS_EVENT_TYPE_BOUNDARY]); 
	}
}

int _set_callback(_location_event_e type, location_manager_h manager, void* callback, void *user_data)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(callback);
	location_manager_s * handle = (location_manager_s *) manager; 
	handle->user_cb[type] = callback;
	handle->user_data[type] = user_data;
	LOGI("[%s] event type : %d. ",__FUNCTION__, type);
	return LOCATIONS_ERROR_NONE; 
}

int _unset_callback(_location_event_e type, location_manager_h manager)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	location_manager_s * handle = (location_manager_s *) manager; 
	handle->user_cb[type] = NULL;
	handle->user_data[type] = NULL;
	LOGI("[%s] event type : %d. ",__FUNCTION__, type);
	return LOCATIONS_ERROR_NONE; 
}

void  _remove_boundary(LocationBoundary *boundary, void *user_data)
{
	LocationObject* loc = (LocationObject*) user_data;
	if (loc != NULL && boundary != NULL) 
	{
		int ret = location_boundary_remove(loc, boundary);
		if(ret != LOCATION_ERROR_NONE)
		{
			LOGI("[%s] Failed to remove boundary : 0x%x. ",__FUNCTION__, ret);
		}
		else
		{
			LOGI("[%s] Delete previous boundary - type : %d ",__FUNCTION__, boundary->type);
		}
	}
}

/////////////////////////////////////////
// Location Manager
////////////////////////////////////////

/*
* Public Implementation
*/

int	location_manager_create(location_method_e method, location_manager_h* manager)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	if(location_init()!=LOCATION_ERROR_NONE)
		return LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;

	LocationMethod _method = LOCATION_METHOD_NONE;
	switch(method)
	{
		case LOCATIONS_METHOD_NONE :
			_method = LOCATION_METHOD_NONE;
			break;
		case LOCATIONS_METHOD_HYBRID :
			_method = LOCATION_METHOD_HYBRID;
			break;
		case LOCATIONS_METHOD_GPS:
			_method = LOCATION_METHOD_GPS;
			break;
		case LOCATIONS_METHOD_WPS :
			_method = LOCATION_METHOD_WPS;
			break;
		case LOCATIONS_METHOD_SPS :
			_method = LOCATION_METHOD_SPS;
			break;
		default :
		{
			LOGE("[%s] LOCATIONS_ERROR_INVALID_PARAMETER(0x%08x) : Out of range (location_method_e) - method : %d ",__FUNCTION__,LOCATIONS_ERROR_INVALID_PARAMETER, method);
			return LOCATIONS_ERROR_INVALID_PARAMETER;
		}
	}

	location_manager_s *handle = (location_manager_s*)malloc(sizeof(location_manager_s));
	if(handle==NULL)
	{
		LOGE("[%s] OUT_OF_MEMORY(0x%08x)", __FUNCTION__, LOCATIONS_ERROR_OUT_OF_MEMORY);
		return LOCATIONS_ERROR_OUT_OF_MEMORY;
	}

	memset(handle, 0 , sizeof(location_manager_s));
	
	handle->object = location_new(_method);
	if(handle->object  == NULL)
	{
		LOGE("[%s] LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE(0x%08x) : fail to location_new", __FUNCTION__, LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE);
		free(handle);
		return LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;
	}
	handle->method = method;
	handle->boundary= NULL;
	*manager = (location_manager_h)handle;
	return LOCATIONS_ERROR_NONE;
}

int	location_manager_destroy(location_manager_h manager)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	location_manager_s *handle = (location_manager_s*)manager;

	if(handle->boundary)
	{
		location_boundary_free(handle->boundary);
	}
		
	int ret = location_free(handle->object);
	if(ret!=LOCATIONS_ERROR_NONE)
	{
		return _convert_error_code(ret,(char*)__FUNCTION__);
	}
	free(handle);
	return LOCATIONS_ERROR_NONE;
}

int	location_manager_start(location_manager_h manager)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	location_manager_s *handle = (location_manager_s*)manager;
		
	g_signal_connect (handle->object, "service-enabled", G_CALLBACK(cb_service_enabled), handle);
	g_signal_connect (handle->object, "service-disabled", G_CALLBACK(cb_service_disabled), handle);
	g_signal_connect (handle->object, "service-updated", G_CALLBACK(cb_service_updated), handle);
	g_signal_connect (handle->object, "zone-in", G_CALLBACK(cb_zone_in), handle);
	g_signal_connect (handle->object, "zone-out", G_CALLBACK(cb_zone_out), handle);
	
	int ret = location_start (handle->object);
	if( ret != LOCATION_ERROR_NONE)
	{
		return _convert_error_code(ret,(char*)__FUNCTION__);
	}
	return LOCATIONS_ERROR_NONE;
}

int	location_manager_stop(location_manager_h manager)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	location_manager_s *handle = (location_manager_s*)manager;
		
	int ret = location_stop (handle->object);
	if( ret != LOCATION_ERROR_NONE)
	{
		return _convert_error_code(ret,(char*)__FUNCTION__);
	}
	return LOCATIONS_ERROR_NONE;
}

int	location_manager_set_boundary_rect(location_manager_h manager, double top_left_latitude,double top_left_longitude,double bottom_right_latitude,double bottom_right_longitude)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_CHECK_CONDITION(top_left_latitude>=-90 && top_left_latitude<=90,LOCATIONS_ERROR_INVALID_PARAMETER,"LOCATIONS_ERROR_INVALID_PARAMETER");
	LOCATIONS_CHECK_CONDITION(top_left_longitude>=-180 && bottom_right_longitude<=180,LOCATIONS_ERROR_INVALID_PARAMETER, "LOCATIONS_ERROR_INVALID_PARAMETER");
	LOCATIONS_CHECK_CONDITION(bottom_right_latitude>=-90 && bottom_right_latitude<=90,LOCATIONS_ERROR_INVALID_PARAMETER, "LOCATIONS_ERROR_INVALID_PARAMETER");
	LOCATIONS_CHECK_CONDITION(bottom_right_longitude>=-180 && bottom_right_longitude<=180,LOCATIONS_ERROR_INVALID_PARAMETER, "LOCATIONS_ERROR_INVALID_PARAMETER");

	location_manager_s *handle = (location_manager_s*)manager;

	int ret;
	ret = location_boundary_foreach(handle->object, _remove_boundary,handle->object );
	if(ret != LOCATION_ERROR_NONE)
	{
		LOGI("[%s] Failed to foreach boundary : 0x%x. ",__FUNCTION__, ret);
	}

	LocationPosition *rb = location_position_new(0, bottom_right_latitude, bottom_right_longitude, 0, LOCATION_STATUS_2D_FIX);
	if (rb ==NULL)
	{
		LOGE("[%s] LOCATIONS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_position_new", __FUNCTION__, LOCATIONS_ERROR_OUT_OF_MEMORY);
		return LOCATIONS_ERROR_OUT_OF_MEMORY;
	}
	LocationPosition *lt = location_position_new(0, top_left_latitude, top_left_longitude, 0, LOCATION_STATUS_2D_FIX);
	if (lt ==NULL)
	{
		LOGE("[%s] LOCATIONS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_position_new", __FUNCTION__, LOCATIONS_ERROR_OUT_OF_MEMORY);
		location_position_free (rb);
		return LOCATIONS_ERROR_OUT_OF_MEMORY;
	}

	LocationBoundary* bound = NULL;
	bound = location_boundary_new_for_rect(lt, rb);
	location_position_free (rb);
	location_position_free (lt);
	
	if(bound)
	{
		ret = location_boundary_add(handle->object, bound);
		if(handle->boundary)
		{
			location_boundary_free(handle->boundary);
			handle->boundary = NULL;
		}
		handle->boundary = location_boundary_copy(bound);
		location_boundary_free(bound);
		if( ret != LOCATION_ERROR_NONE)
		{
			return _convert_error_code(ret,(char*)__FUNCTION__);
		}
	}
	else
	{
		LOGE("[%s] LOCATIONS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_boundary_new_for_rect", __FUNCTION__, LOCATIONS_ERROR_OUT_OF_MEMORY);
		return LOCATIONS_ERROR_OUT_OF_MEMORY;
	}
	return LOCATIONS_ERROR_NONE;
}

int	location_manager_set_boundary_circle(location_manager_h manager, double center_latitude,double center_longitude, double radius)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	
	LOCATIONS_CHECK_CONDITION(center_latitude>=-90 && center_latitude<=90,LOCATIONS_ERROR_INVALID_PARAMETER,"LOCATIONS_ERROR_INVALID_PARAMETER");
	LOCATIONS_CHECK_CONDITION(center_longitude>=-180 && center_longitude<=180,LOCATIONS_ERROR_INVALID_PARAMETER,"LOCATIONS_ERROR_INVALID_PARAMETER");
	LOCATIONS_CHECK_CONDITION(radius>=0,LOCATIONS_ERROR_INVALID_PARAMETER,"LOCATIONS_ERROR_INVALID_PARAMETER");

	location_manager_s *handle = (location_manager_s*)manager;	

	int ret;
	ret = location_boundary_foreach(handle->object, _remove_boundary, handle->object);
	if(ret != LOCATION_ERROR_NONE)
	{
		LOGI("[%s] Failed to foreach boundary : 0x%x. ",__FUNCTION__, ret);
	}

	LocationPosition *center = location_position_new(0, center_latitude, center_longitude, 0, LOCATION_STATUS_2D_FIX);
	if (center ==NULL)
	{
		LOGE("[%s] LOCATIONS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_position_new", __FUNCTION__, LOCATIONS_ERROR_OUT_OF_MEMORY);
		return LOCATIONS_ERROR_OUT_OF_MEMORY;
	}

	LocationBoundary* bound = NULL;
	bound = location_boundary_new_for_circle(center,radius);
	location_position_free (center);
	if(bound)
	{
		ret = location_boundary_add(handle->object, bound);
		if(handle->boundary)
		{
			location_boundary_free(handle->boundary);
			handle->boundary = NULL;
		}
		handle->boundary = location_boundary_copy(bound);
		location_boundary_free(bound);
		if( ret != LOCATION_ERROR_NONE)
		{
			return _convert_error_code(ret,(char*)__FUNCTION__);
		}
	}
	else
	{
		LOGE("[%s] LOCATIONS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_boundary_new_for_circle", __FUNCTION__, LOCATIONS_ERROR_OUT_OF_MEMORY);
		return LOCATIONS_ERROR_OUT_OF_MEMORY;
	}
	return LOCATIONS_ERROR_NONE;
}

int location_manager_is_boundary_contains_coordinate(location_manager_h manager, double latitude, double longitude, bool *contained)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(contained);
	
	LOCATIONS_CHECK_CONDITION(latitude>=-90 && latitude<=90,LOCATIONS_ERROR_INVALID_PARAMETER,"LOCATIONS_ERROR_INVALID_PARAMETER");
	LOCATIONS_CHECK_CONDITION(longitude>=-180 && longitude<=180,LOCATIONS_ERROR_INVALID_PARAMETER,"LOCATIONS_ERROR_INVALID_PARAMETER");

	location_manager_s *handle = (location_manager_s*)manager;	

	if(handle->boundary==NULL)
	{
		LOGI("[%s] There is no boundary ",__FUNCTION__);
		*contained = FALSE;
		return LOCATIONS_ERROR_NONE;
	}

	LocationPosition *pos = location_position_new(0, latitude, longitude, 0, LOCATION_STATUS_2D_FIX);
	if (pos ==NULL)
	{
		LOGE("[%s] LOCATIONS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to location_position_new", __FUNCTION__, LOCATIONS_ERROR_OUT_OF_MEMORY);
		*contained = FALSE;
		return LOCATIONS_ERROR_OUT_OF_MEMORY;
	}
	gboolean is_inside = location_boundary_if_inside(handle->boundary, pos);
	
	if(is_inside)
	{
		*contained = TRUE;
	}
	else
	{
		*contained = FALSE;
	}
	location_position_free (pos);
	return LOCATIONS_ERROR_NONE;
}

int	location_manager_get_method(location_manager_h manager, location_method_e* method)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(method);
	location_manager_s *handle = (location_manager_s*)manager;
	LocationMethod _method = LOCATION_METHOD_NONE;	
	g_object_get(handle->object, "method", &_method, NULL);
	switch(_method)
	{
		case LOCATION_METHOD_NONE :
			*method = LOCATIONS_METHOD_NONE;
			break;
		case LOCATION_METHOD_HYBRID :
		case LOCATION_METHOD_CPS:
		case LOCATION_METHOD_IPS :
			*method = LOCATIONS_METHOD_HYBRID;
			break;
		case LOCATION_METHOD_GPS:
			*method = LOCATIONS_METHOD_GPS;
			break;
		case LOCATION_METHOD_WPS :
			*method = LOCATIONS_METHOD_WPS;
			break;
		case LOCATION_METHOD_SPS :
			*method = LOCATIONS_METHOD_SPS;
			break;
		default :
		{
			LOGE("[%s] LOCATIONS_ERROR_INVALID_PARAMETER(0x%08x) : Out of range (location_method_e) - method : %d ",__FUNCTION__,LOCATIONS_ERROR_INVALID_PARAMETER, method);
			return LOCATIONS_ERROR_INVALID_PARAMETER;
		}
	}
	//*method = handle->method;
	return LOCATIONS_ERROR_NONE;
}


int	location_manager_get_position(location_manager_h manager, double *altitude, double *latitude, double *longitude, time_t *timestamp)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(altitude);
	LOCATIONS_NULL_ARG_CHECK(latitude);
	LOCATIONS_NULL_ARG_CHECK(longitude);
	LOCATIONS_NULL_ARG_CHECK(timestamp);

	location_manager_s *handle = (location_manager_s*)manager;
	int ret;
	LocationPosition *pos = NULL;
	LocationAccuracy *acc = NULL;
	ret = location_get_position(handle->object, &pos, &acc);
	if( ret != LOCATION_ERROR_NONE)
	{
		return _convert_error_code(ret,(char*)__FUNCTION__);
	}

	if(pos->status == LOCATION_STATUS_NO_FIX)
	{
		*altitude = -1;
		*latitude = -1;
		*longitude =-1;
	}
	else
	{
		if(pos->status == LOCATION_STATUS_3D_FIX)
		{
			*altitude = pos->altitude;
		}
		else
		{
			*altitude = -1;
		}
		*latitude = pos->latitude;
		*longitude = pos->longitude;
	}
	*timestamp = pos->timestamp;
	location_position_free (pos);
	location_accuracy_free (acc);
	return LOCATIONS_ERROR_NONE;
}

int	location_manager_get_velocity(location_manager_h manager, int *climb, int *direction, int *speed, time_t *timestamp)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(climb);
	LOCATIONS_NULL_ARG_CHECK(direction);
	LOCATIONS_NULL_ARG_CHECK(speed);
	LOCATIONS_NULL_ARG_CHECK(timestamp);

	location_manager_s *handle = (location_manager_s*)manager;
	int ret;
	LocationVelocity *vel = NULL;
	LocationAccuracy *acc = NULL;
	ret = location_get_velocity(handle->object, &vel, &acc);
	if( ret != LOCATION_ERROR_NONE)
	{
		return _convert_error_code(ret,(char*)__FUNCTION__);
	}

	*climb = vel->climb;
	*direction = vel->direction;
	*speed = vel->speed;
	*timestamp = vel->timestamp;
	location_velocity_free(vel);
	location_accuracy_free(acc);
	return LOCATIONS_ERROR_NONE;
}

int	location_manager_get_accuracy(location_manager_h manager, location_accuracy_level_e *level, double *horizontal, double *vertical)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(level);
	LOCATIONS_NULL_ARG_CHECK(horizontal);
	LOCATIONS_NULL_ARG_CHECK(vertical);
	location_manager_s *handle = (location_manager_s*)manager;

	int ret;
	LocationPosition *pos = NULL;
	LocationAccuracy *acc = NULL;
	ret = location_get_position(handle->object, &pos, &acc);
	if( ret != LOCATION_ERROR_NONE)
	{
		return _convert_error_code(ret,(char*)__FUNCTION__);
	}
	
	*level = acc->level;
	*horizontal = acc->horizontal_accuracy;	
	*vertical = acc->vertical_accuracy;
	location_position_free(pos);
	location_accuracy_free(acc);
	return LOCATIONS_ERROR_NONE;			
}

int	location_manager_set_position_updated_cb(location_manager_h manager, location_position_updated_cb callback, void *user_data)
{
	return _set_callback(_LOCATIONS_EVENT_TYPE_POSITION,manager,callback,user_data);
}

int	location_manager_unset_position_updated_cb(location_manager_h manager)
{
	return _unset_callback(_LOCATIONS_EVENT_TYPE_POSITION,manager);
}

int	location_manager_set_velocity_updated_cb(location_manager_h manager, location_velocity_updated_cb callback, void *user_data)
{
	return _set_callback(_LOCATIONS_EVENT_TYPE_VELOCITY,manager,callback,user_data);
}

int	location_manager_unset_velocity_updated_cb(location_manager_h manager)
{
	return _unset_callback(_LOCATIONS_EVENT_TYPE_VELOCITY,manager);
}

int	location_manager_set_service_state_changed_cb(location_manager_h manager, location_service_state_changed_cb callback, void *user_data)
{
	return _set_callback(_LOCATIONS_EVENT_TYPE_SERVICE_STATE,manager,callback,user_data);
}

int	location_manager_unset_service_state_changed_cb(location_manager_h manager)
{
	return _unset_callback(_LOCATIONS_EVENT_TYPE_SERVICE_STATE,manager);
}

int	location_manager_set_zone_changed_cb(location_manager_h manager, location_zone_changed_cb callback, void *user_data)
{
	return _set_callback(_LOCATIONS_EVENT_TYPE_BOUNDARY,manager,callback,user_data);
}

int	location_manager_unset_zone_changed_cb(location_manager_h manager)
{
	return _unset_callback(_LOCATIONS_EVENT_TYPE_BOUNDARY,manager);
}

/////////////////////////////////////////
// GPS Status & Satellites
////////////////////////////////////////

int	gps_status_get_nmea(location_manager_h manager, char** nmea)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(nmea);
	location_manager_s *handle = (location_manager_s*)manager;

	if(handle->method == LOCATIONS_METHOD_HYBRID)
	{
		LocationMethod _method = LOCATION_METHOD_NONE;	
		g_object_get(handle->object, "method", &_method, NULL);
		if(_method!=LOCATION_METHOD_GPS)
		{
			LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__, LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
			return LOCATIONS_ERROR_INCORRECT_METHOD;
		}	
	}
	else if(handle->method != LOCATIONS_METHOD_GPS)
	{
		LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__, LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
		return LOCATIONS_ERROR_INCORRECT_METHOD;
	}
	gchar* nmea_data = NULL;
	g_object_get(handle->object, "nmea", &nmea_data, NULL);	
	if(nmea_data == NULL)
	{
		LOGE("[%s] LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE(0x%08x) : nmea data is NULL ",__FUNCTION__,LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE);
		return LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;
	}	
	*nmea = NULL;
	*nmea = strdup(nmea_data);
	if(*nmea == NULL)
	{
		LOGE("[%s] LOCATIONS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to strdup ",__FUNCTION__,LOCATIONS_ERROR_OUT_OF_MEMORY);
		return LOCATIONS_ERROR_OUT_OF_MEMORY;
	}
	g_free(nmea_data);
	return LOCATIONS_ERROR_NONE;
}

int  gps_status_get_satellite_count_in_view(location_manager_h manager, int *count)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(count);
	location_manager_s *handle = (location_manager_s*)manager;
	if(handle->method == LOCATIONS_METHOD_HYBRID)
	{
		LocationMethod _method = LOCATION_METHOD_NONE;	
		g_object_get(handle->object, "method", &_method, NULL);
		if(_method!=LOCATION_METHOD_GPS)
		{
			LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__, LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
			return LOCATIONS_ERROR_INCORRECT_METHOD;
		}	
	}
	else if(handle->method != LOCATIONS_METHOD_GPS)
	{
		LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__, LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
		return LOCATIONS_ERROR_INCORRECT_METHOD;
	}
	
	LocationSatellite *sat = NULL;
 	g_object_get (handle->object, "satellite", &sat, NULL);
	if (sat == NULL) 
	{
		LOGE("[%s] LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE(0x%08x) : satellite is NULL ",__FUNCTION__,LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE);
		return LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;
	}
	*count = sat->num_of_sat_inview;
	location_satellite_free (sat);
	sat = NULL;
	return LOCATIONS_ERROR_NONE;
}

int  gps_status_foreach_satellites_in_view (location_manager_h manager, gps_status_get_satellites_cb callback, void *user_data)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(callback);
	location_manager_s *handle = (location_manager_s*)manager;
	if(handle->method == LOCATIONS_METHOD_HYBRID)
	{
		LocationMethod _method = LOCATION_METHOD_NONE;	
		g_object_get(handle->object, "method", &_method, NULL);
		if(_method!=LOCATION_METHOD_GPS)
		{
			LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__, LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
			return LOCATIONS_ERROR_INCORRECT_METHOD;
		}	
	}
	else if(handle->method != LOCATIONS_METHOD_GPS)
	{
		LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__, LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
		return LOCATIONS_ERROR_INCORRECT_METHOD;
	}
	
	LocationSatellite *sat = NULL;
 	g_object_get (handle->object, "satellite", &sat, NULL);
	if (sat == NULL) 
	{
		LOGE("[%s] LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE(0x%08x) : satellite is NULL ",__FUNCTION__,LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE);
		return LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;
	}

	int i;
	for (i=0; i<sat->num_of_sat_inview; i++) 
	{
		guint prn;
		gboolean used;
		guint elevation;
		guint azimuth;
		gint snr;
		location_satellite_get_satellite_details(sat, i, &prn, &used, &elevation, &azimuth, &snr);
		if ( callback(azimuth, elevation, prn, snr, used, user_data) != TRUE )
			break;
	}
	location_satellite_free (sat);	
	sat = NULL;
	return LOCATIONS_ERROR_NONE;
}

int  gps_status_get_active_satellite_count(location_manager_h manager, int *count)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(count);
	location_manager_s *handle = (location_manager_s*)manager;
	if(handle->method == LOCATIONS_METHOD_HYBRID)
	{
		LocationMethod _method = LOCATION_METHOD_NONE;	
		g_object_get(handle->object, "method", &_method, NULL);
		if(_method!=LOCATION_METHOD_GPS)
		{
			LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__, LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
			return LOCATIONS_ERROR_INCORRECT_METHOD;
		}	
	}
	else if(handle->method != LOCATIONS_METHOD_GPS)
	{
		LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__, LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
		return LOCATIONS_ERROR_INCORRECT_METHOD;
	}
	
	LocationSatellite *sat = NULL;
 	g_object_get (handle->object, "satellite", &sat, NULL);
	if (sat == NULL) 
	{
		LOGE("[%s] LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE(0x%08x) : satellite is NULL ",__FUNCTION__,LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE);
		return LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;
	}
	*count = sat->num_of_sat_used;
	location_satellite_free (sat);
	sat = NULL;
	return LOCATIONS_ERROR_NONE;
}
