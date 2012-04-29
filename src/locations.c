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
	LOCATIONS_CHECK_CONDITION(arg != NULL,LOCATIONS_ERROR_INVALID_PARAMETER,"LOCATIONS_ERROR_INVALID_PARAMETER") \

/*
* Internal Implementation
*/

static int __convert_error_code(int code, char *func_name)
{
	int ret;
	char *msg = "LOCATIONS_ERROR_NONE";
	switch (code) {
	case LOCATION_ERROR_NONE:
		ret = LOCATIONS_ERROR_NONE;
		msg = "LOCATIONS_ERROR_NONE";
		break;
	case LOCATION_ERROR_NETWORK_FAILED:
	case LOCATION_ERROR_NETWORK_NOT_CONNECTED:
		ret = LOCATIONS_ERROR_NETWORK_FAILED;
		msg = "LOCATIONS_ERROR_NETWORK_FAILED";
		break;
	case LOCATION_ERROR_NOT_ALLOWED:
		ret = LOCATIONS_ERROR_GPS_SETTING_OFF;
		msg = "LOCATIONS_ERROR_GPS_SETTING_OFF";
		break;
	case LOCATION_ERROR_NOT_AVAILABLE:
	case LOCATION_ERROR_CONFIGURATION:
	case LOCATION_ERROR_PARAMETER:
	case LOCATION_ERROR_UNKNOWN:
	default:
		msg = "LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE";
		ret = LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;
	}
	LOGE("[%s] %s(0x%08x) : core fw error(0x%x)", func_name, msg, ret, code);
	return ret;
}

static void __cb_service_updated(GObject * self, guint type, gpointer data, gpointer accuracy, gpointer userdata)
{
	LOGI("[%s] Callback function has been invoked. ", __FUNCTION__);
	location_manager_s *handle = (location_manager_s *) userdata;
	if (type == VELOCITY_UPDATED && handle->user_cb[_LOCATIONS_EVENT_TYPE_VELOCITY]) {
		LocationVelocity *vel = (LocationVelocity *) data;
		LOGI("[%s] Current velocity: timestamp : %d, speed: %f, direction : %f, climb : %f", __FUNCTION__,
		     vel->timestamp, vel->speed, vel->direction, vel->climb);
		((location_velocity_updated_cb) handle->user_cb[_LOCATIONS_EVENT_TYPE_VELOCITY]) (vel->speed, vel->direction,
												  vel->climb, vel->timestamp,
												  handle->user_data
												  [_LOCATIONS_EVENT_TYPE_VELOCITY]);
	}
	if (type == POSITION_UPDATED && handle->user_cb[_LOCATIONS_EVENT_TYPE_POSITION]) {
		LocationPosition *pos = (LocationPosition *) data;
		LOGI("[%s] Current position: timestamp : %d, latitude : %f, altitude: %f, longitude: %f", __FUNCTION__,
		     pos->timestamp, pos->latitude, pos->altitude, pos->longitude);
		((location_position_updated_cb) handle->user_cb[_LOCATIONS_EVENT_TYPE_POSITION]) (pos->latitude, pos->longitude,
												  pos->altitude, pos->timestamp,
												  handle->user_data
												  [_LOCATIONS_EVENT_TYPE_POSITION]);
	}
}

static void __cb_service_enabled(GObject * self, guint status, gpointer userdata)
{
	LOGI("[%s] Callback function has been invoked. ", __FUNCTION__);
	location_manager_s *handle = (location_manager_s *) userdata;
	if (handle->user_cb[_LOCATIONS_EVENT_TYPE_SERVICE_STATE]) {
		((location_service_state_changed_cb)
		 handle->user_cb[_LOCATIONS_EVENT_TYPE_SERVICE_STATE]) (LOCATIONS_SERVICE_ENABLED,
									handle->user_data[_LOCATIONS_EVENT_TYPE_SERVICE_STATE]);
	}
}

static void __cb_service_disabled(GObject * self, guint status, gpointer userdata)
{
	LOGI("[%s] Callback function has been invoked. ", __FUNCTION__);
	location_manager_s *handle = (location_manager_s *) userdata;
	if (handle->user_cb[_LOCATIONS_EVENT_TYPE_SERVICE_STATE])
		((location_service_state_changed_cb)
		 handle->user_cb[_LOCATIONS_EVENT_TYPE_SERVICE_STATE]) (LOCATIONS_SERVICE_DISABLED,
									handle->user_data[_LOCATIONS_EVENT_TYPE_SERVICE_STATE]);
}

static void __cb_zone_in(GObject * self, guint type, gpointer position, gpointer accuracy, gpointer userdata)
{
	location_manager_s *handle = (location_manager_s *) userdata;
	if (handle->user_cb[_LOCATIONS_EVENT_TYPE_BOUNDARY]) {
		LocationPosition *pos = (LocationPosition *) position;
		((location_zone_changed_cb) handle->user_cb[_LOCATIONS_EVENT_TYPE_BOUNDARY]) (LOCATIONS_BOUNDARY_IN,
											      pos->latitude, pos->longitude,
											      pos->altitude, pos->timestamp,
											      handle->user_data
											      [_LOCATIONS_EVENT_TYPE_BOUNDARY]);
	}
}

static void __cb_zone_out(GObject * self, guint type, gpointer position, gpointer accuracy, gpointer userdata)
{
	location_manager_s *handle = (location_manager_s *) userdata;
	if (handle->user_cb[_LOCATIONS_EVENT_TYPE_BOUNDARY]) {
		LocationPosition *pos = (LocationPosition *) position;
		((location_zone_changed_cb) handle->user_cb[_LOCATIONS_EVENT_TYPE_BOUNDARY]) (LOCATIONS_BOUNDARY_OUT,
											      pos->latitude, pos->longitude,
											      pos->altitude, pos->timestamp,
											      handle->user_data
											      [_LOCATIONS_EVENT_TYPE_BOUNDARY]);
	}
}

static int __set_callback(_location_event_e type, location_manager_h manager, void *callback, void *user_data)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(callback);
	location_manager_s *handle = (location_manager_s *) manager;
	handle->user_cb[type] = callback;
	handle->user_data[type] = user_data;
	LOGI("[%s] event type : %d. ", __FUNCTION__, type);
	return LOCATIONS_ERROR_NONE;
}

static int __unset_callback(_location_event_e type, location_manager_h manager)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	location_manager_s *handle = (location_manager_s *) manager;
	handle->user_cb[type] = NULL;
	handle->user_data[type] = NULL;
	LOGI("[%s] event type : %d. ", __FUNCTION__, type);
	return LOCATIONS_ERROR_NONE;
}

static void __foreach_boundary(LocationBoundary * boundary, void *user_data)
{
	location_manager_s *handle = (location_manager_s *) user_data;

	if (handle != NULL && boundary != NULL) {
		int ret = -1;
		location_bounds_h bounds;
		if (boundary->type == LOCATION_BOUNDARY_CIRCLE) {
			location_coords_s center;
			center.latitude = boundary->circle.center->latitude;
			center.longitude = boundary->circle.center->longitude;
			ret = location_bounds_create_circle(center, boundary->circle.radius, &bounds);
		} else if (boundary->type == LOCATION_BOUNDARY_RECT) {
			location_coords_s left_top;
			location_coords_s right_bottom;
			left_top.latitude = boundary->rect.left_top->latitude;
			left_top.longitude = boundary->rect.left_top->longitude;
			right_bottom.latitude = boundary->rect.right_bottom->latitude;
			right_bottom.longitude = boundary->rect.right_bottom->longitude;
			ret = location_bounds_create_rect(left_top, right_bottom, &bounds);
		} else if (boundary->type == LOCATION_BOUNDARY_POLYGON) {
			GList *list = boundary->polygon.position_list;
			int size = g_list_length(list);
			if (size > 0) {
				location_coords_s coords[size];
				int cnt = 0;
				while (list) {
					LocationPosition *pos = list->data;
					coords[cnt].latitude = pos->latitude;
					coords[cnt].longitude = pos->longitude;
					list = g_list_next(list);
					cnt++;
				}
				ret = location_bounds_create_polygon(coords, size, &bounds);
			}
		} else {
			LOGI("[%s] Invalid boundary type : %d", __FUNCTION__, boundary->type);
		}

		if (ret != LOCATIONS_ERROR_NONE) {
			LOGI("[%s] Failed to create location_bounds : (0x%08x) ", __FUNCTION__, ret);
		} else {
			if (handle->is_continue_foreach_bounds) {
				handle->is_continue_foreach_bounds =
				    ((location_bounds_cb) handle->user_cb[_LOCATIONS_EVENT_TYPE_FOREACH_BOUNDS]) (bounds,
														  handle->
														  user_data
														  [_LOCATIONS_EVENT_TYPE_FOREACH_BOUNDS]);
			}
			location_bounds_destroy(bounds);
		}
	} else {
		LOGI("[%s]  __foreach_boundary() has been failed", __FUNCTION__);
	}
}

/////////////////////////////////////////
// Location Manager
////////////////////////////////////////

/*
* Public Implementation
*/

bool location_manager_is_supported_method(location_method_e method)
{
	LocationMethod _method = LOCATION_METHOD_NONE;
	switch (method) {
	case LOCATIONS_METHOD_HYBRID:
		_method = LOCATION_METHOD_HYBRID;
		break;
	case LOCATIONS_METHOD_GPS:
		_method = LOCATION_METHOD_GPS;
		break;
	case LOCATIONS_METHOD_WPS:
		_method = LOCATION_METHOD_WPS;
		break;
	case LOCATIONS_METHOD_SPS:
		_method = LOCATION_METHOD_SPS;
		break;
	default:
		_method = LOCATION_METHOD_NONE;
		break;
	}
	return location_is_supported_method(_method);
}

int location_manager_create(location_method_e method, location_manager_h * manager)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	if (location_init() != LOCATION_ERROR_NONE)
		return LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;

	LocationMethod _method = LOCATION_METHOD_NONE;
	switch (method) {
	case LOCATIONS_METHOD_NONE:
		_method = LOCATION_METHOD_NONE;
		break;
	case LOCATIONS_METHOD_HYBRID:
		_method = LOCATION_METHOD_HYBRID;
		break;
	case LOCATIONS_METHOD_GPS:
		_method = LOCATION_METHOD_GPS;
		break;
	case LOCATIONS_METHOD_WPS:
		_method = LOCATION_METHOD_WPS;
		break;
	case LOCATIONS_METHOD_SPS:
		_method = LOCATION_METHOD_SPS;
		break;
	default:
		{
			LOGE("[%s] LOCATIONS_ERROR_INVALID_PARAMETER(0x%08x) : Out of range (location_method_e) - method : %d ",
			     __FUNCTION__, LOCATIONS_ERROR_INVALID_PARAMETER, method);
			return LOCATIONS_ERROR_INVALID_PARAMETER;
		}
	}

	location_manager_s *handle = (location_manager_s *) malloc(sizeof(location_manager_s));
	if (handle == NULL) {
		LOGE("[%s] OUT_OF_MEMORY(0x%08x)", __FUNCTION__, LOCATIONS_ERROR_OUT_OF_MEMORY);
		return LOCATIONS_ERROR_OUT_OF_MEMORY;
	}

	memset(handle, 0, sizeof(location_manager_s));

	handle->object = location_new(_method);
	if (handle->object == NULL) {
		LOGE("[%s] LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE(0x%08x) : fail to location_new", __FUNCTION__,
		     LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE);
		free(handle);
		return LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;
	}
	handle->method = method;
	handle->is_continue_foreach_bounds = TRUE;
	*manager = (location_manager_h) handle;
	return LOCATIONS_ERROR_NONE;
}

int location_manager_destroy(location_manager_h manager)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	location_manager_s *handle = (location_manager_s *) manager;

	int ret = location_free(handle->object);
	if (ret != LOCATIONS_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}
	free(handle);
	return LOCATIONS_ERROR_NONE;
}

int location_manager_start(location_manager_h manager)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	location_manager_s *handle = (location_manager_s *) manager;

	g_signal_connect(handle->object, "service-enabled", G_CALLBACK(__cb_service_enabled), handle);
	g_signal_connect(handle->object, "service-disabled", G_CALLBACK(__cb_service_disabled), handle);
	g_signal_connect(handle->object, "service-updated", G_CALLBACK(__cb_service_updated), handle);
	g_signal_connect(handle->object, "zone-in", G_CALLBACK(__cb_zone_in), handle);
	g_signal_connect(handle->object, "zone-out", G_CALLBACK(__cb_zone_out), handle);

	int ret = location_start(handle->object);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}
	return LOCATIONS_ERROR_NONE;
}

int location_manager_stop(location_manager_h manager)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	location_manager_s *handle = (location_manager_s *) manager;

	int ret = location_stop(handle->object);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}
	return LOCATIONS_ERROR_NONE;
}

int location_manager_add_boundary(location_manager_h manager, const location_bounds_h bounds)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(bounds);

	location_manager_s *handle = (location_manager_s *) manager;
	int ret = location_boundary_add(handle->object,(LocationBoundary*)bounds);

	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}
	return LOCATIONS_ERROR_NONE;
}

int location_manager_remove_boundary(location_manager_h manager, const location_bounds_h bounds)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(bounds);

	location_manager_s *handle = (location_manager_s *) manager;
	int ret = location_boundary_remove(handle->object, (LocationBoundary*)bounds);

	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}
	return LOCATIONS_ERROR_NONE;
}

int location_manager_foreach_boundary(location_manager_h manager, location_bounds_cb callback, void *user_data)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(callback);

	location_manager_s *handle = (location_manager_s *) manager;
	handle->user_cb[_LOCATIONS_EVENT_TYPE_FOREACH_BOUNDS] = callback;
	handle->user_data[_LOCATIONS_EVENT_TYPE_FOREACH_BOUNDS] = user_data;
	handle->is_continue_foreach_bounds = TRUE;
	int ret = location_boundary_foreach(handle->object, __foreach_boundary, handle);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}
	return LOCATIONS_ERROR_NONE;
}

int location_manager_get_method(location_manager_h manager, location_method_e * method)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(method);
	location_manager_s *handle = (location_manager_s *) manager;
	LocationMethod _method = LOCATION_METHOD_NONE;
	g_object_get(handle->object, "method", &_method, NULL);
	switch (_method) {
	case LOCATION_METHOD_NONE:
		*method = LOCATIONS_METHOD_NONE;
		break;
	case LOCATION_METHOD_HYBRID:
	case LOCATION_METHOD_CPS:
	case LOCATION_METHOD_IPS:
		*method = LOCATIONS_METHOD_HYBRID;
		break;
	case LOCATION_METHOD_GPS:
		*method = LOCATIONS_METHOD_GPS;
		break;
	case LOCATION_METHOD_WPS:
		*method = LOCATIONS_METHOD_WPS;
		break;
	case LOCATION_METHOD_SPS:
		*method = LOCATIONS_METHOD_SPS;
		break;
	default:
		{
			LOGE("[%s] LOCATIONS_ERROR_INVALID_PARAMETER(0x%08x) : Out of range (location_method_e) - method : %d ",
			     __FUNCTION__, LOCATIONS_ERROR_INVALID_PARAMETER, method);
			return LOCATIONS_ERROR_INVALID_PARAMETER;
		}
	}
	//*method = handle->method;
	return LOCATIONS_ERROR_NONE;
}

int location_manager_get_position(location_manager_h manager, double *altitude, double *latitude, double *longitude,
				  time_t * timestamp)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(altitude);
	LOCATIONS_NULL_ARG_CHECK(latitude);
	LOCATIONS_NULL_ARG_CHECK(longitude);
	LOCATIONS_NULL_ARG_CHECK(timestamp);

	location_manager_s *handle = (location_manager_s *) manager;
	int ret;
	LocationPosition *pos = NULL;
	LocationAccuracy *acc = NULL;
	ret = location_get_position(handle->object, &pos, &acc);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}

	if (pos->status == LOCATION_STATUS_NO_FIX) {
		*altitude = -1;
		*latitude = -1;
		*longitude = -1;
	} else {
		if (pos->status == LOCATION_STATUS_3D_FIX) {
			*altitude = pos->altitude;
		} else {
			*altitude = -1;
		}
		*latitude = pos->latitude;
		*longitude = pos->longitude;
	}
	*timestamp = pos->timestamp;
	location_position_free(pos);
	location_accuracy_free(acc);
	return LOCATIONS_ERROR_NONE;
}

int location_manager_get_velocity(location_manager_h manager, int *climb, int *direction, int *speed, time_t * timestamp)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(climb);
	LOCATIONS_NULL_ARG_CHECK(direction);
	LOCATIONS_NULL_ARG_CHECK(speed);
	LOCATIONS_NULL_ARG_CHECK(timestamp);

	location_manager_s *handle = (location_manager_s *) manager;
	int ret;
	LocationVelocity *vel = NULL;
	LocationAccuracy *acc = NULL;
	ret = location_get_velocity(handle->object, &vel, &acc);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}

	*climb = vel->climb;
	*direction = vel->direction;
	*speed = vel->speed;
	*timestamp = vel->timestamp;
	location_velocity_free(vel);
	location_accuracy_free(acc);
	return LOCATIONS_ERROR_NONE;
}

int location_manager_get_accuracy(location_manager_h manager, location_accuracy_level_e * level, double *horizontal,
				  double *vertical)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(level);
	LOCATIONS_NULL_ARG_CHECK(horizontal);
	LOCATIONS_NULL_ARG_CHECK(vertical);
	location_manager_s *handle = (location_manager_s *) manager;

	int ret;
	LocationPosition *pos = NULL;
	LocationAccuracy *acc = NULL;
	ret = location_get_position(handle->object, &pos, &acc);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}

	*level = acc->level;
	*horizontal = acc->horizontal_accuracy;
	*vertical = acc->vertical_accuracy;
	location_position_free(pos);
	location_accuracy_free(acc);
	return LOCATIONS_ERROR_NONE;
}

int location_manager_get_last_position(location_manager_h manager, double *altitude, double *latitude, double *longitude,
				       time_t * timestamp)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(altitude);
	LOCATIONS_NULL_ARG_CHECK(latitude);
	LOCATIONS_NULL_ARG_CHECK(longitude);
	LOCATIONS_NULL_ARG_CHECK(timestamp);

	location_manager_s *handle = (location_manager_s *) manager;

	int ret;
	LocationPosition *last_pos = NULL;
	LocationAccuracy *last_acc = NULL;
	ret = location_get_last_position(handle->object, &last_pos, &last_acc);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}

	if (last_pos->status == LOCATION_STATUS_NO_FIX) {
		*altitude = -1;
		*latitude = -1;
		*longitude = -1;
	} else {
		if (last_pos->status == LOCATION_STATUS_3D_FIX) {
			*altitude = last_pos->altitude;
		} else {
			*altitude = -1;
		}
		*latitude = last_pos->latitude;
		*longitude = last_pos->longitude;
	}
	*timestamp = last_pos->timestamp;
	location_position_free(last_pos);
	location_accuracy_free(last_acc);
	return LOCATIONS_ERROR_NONE;
}

int location_manager_get_last_velocity(location_manager_h manager, int *climb, int *direction, int *speed, time_t * timestamp)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(climb);
	LOCATIONS_NULL_ARG_CHECK(direction);
	LOCATIONS_NULL_ARG_CHECK(speed);
	LOCATIONS_NULL_ARG_CHECK(timestamp);

	location_manager_s *handle = (location_manager_s *) manager;

	int ret;
	LocationVelocity *last_vel = NULL;
	LocationAccuracy *last_acc = NULL;
	ret = location_get_last_velocity(handle->object, &last_vel, &last_acc);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}

	*climb = last_vel->climb;
	*direction = last_vel->direction;
	*speed = last_vel->speed;
	*timestamp = last_vel->timestamp;
	location_velocity_free(last_vel);
	location_accuracy_free(last_acc);
	return LOCATIONS_ERROR_NONE;
}

int location_manager_get_last_accuracy(location_manager_h manager, location_accuracy_level_e * level, double *horizontal,
				       double *vertical)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(level);
	LOCATIONS_NULL_ARG_CHECK(horizontal);
	LOCATIONS_NULL_ARG_CHECK(vertical);
	location_manager_s *handle = (location_manager_s *) manager;

	int ret;
	LocationPosition *last_pos = NULL;
	LocationAccuracy *last_acc = NULL;
	ret = location_get_last_position(handle->object, &last_pos, &last_acc);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}

	*level = last_acc->level;
	*horizontal = last_acc->horizontal_accuracy;
	*vertical = last_acc->vertical_accuracy;
	location_position_free(last_pos);
	location_accuracy_free(last_acc);
	return LOCATIONS_ERROR_NONE;
}

int location_manager_set_position_updated_cb(location_manager_h manager, location_position_updated_cb callback, int interval,
					     void *user_data)
{
	LOCATIONS_CHECK_CONDITION(interval >= 1
				  && interval <= 120, LOCATIONS_ERROR_INVALID_PARAMETER, "LOCATIONS_ERROR_INVALID_PARAMETER");
	LOCATIONS_NULL_ARG_CHECK(manager);
	location_manager_s *handle = (location_manager_s *) manager;
	g_object_set(handle->object, "update-interval", interval, NULL);
	return __set_callback(_LOCATIONS_EVENT_TYPE_POSITION, manager, callback, user_data);
}

int location_manager_unset_position_updated_cb(location_manager_h manager)
{
	return __unset_callback(_LOCATIONS_EVENT_TYPE_POSITION, manager);
}

int location_manager_set_velocity_updated_cb(location_manager_h manager, location_velocity_updated_cb callback, void *user_data)
{
	return __set_callback(_LOCATIONS_EVENT_TYPE_VELOCITY, manager, callback, user_data);
}

int location_manager_unset_velocity_updated_cb(location_manager_h manager)
{
	return __unset_callback(_LOCATIONS_EVENT_TYPE_VELOCITY, manager);
}

int location_manager_set_service_state_changed_cb(location_manager_h manager, location_service_state_changed_cb callback,
						  void *user_data)
{
	return __set_callback(_LOCATIONS_EVENT_TYPE_SERVICE_STATE, manager, callback, user_data);
}

int location_manager_unset_service_state_changed_cb(location_manager_h manager)
{
	return __unset_callback(_LOCATIONS_EVENT_TYPE_SERVICE_STATE, manager);
}

int location_manager_set_zone_changed_cb(location_manager_h manager, location_zone_changed_cb callback, void *user_data)
{
	return __set_callback(_LOCATIONS_EVENT_TYPE_BOUNDARY, manager, callback, user_data);
}

int location_manager_unset_zone_changed_cb(location_manager_h manager)
{
	return __unset_callback(_LOCATIONS_EVENT_TYPE_BOUNDARY, manager);
}

int location_manager_send_command(const char *cmd)
{
	LOCATIONS_NULL_ARG_CHECK(cmd);

	int ret;
	ret = location_send_command(cmd);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}

	return LOCATIONS_ERROR_NONE;
}

/////////////////////////////////////////
// GPS Status & Satellites
////////////////////////////////////////

int gps_status_get_nmea(location_manager_h manager, char **nmea)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(nmea);
	location_manager_s *handle = (location_manager_s *) manager;

	if (handle->method == LOCATIONS_METHOD_HYBRID) {
		LocationMethod _method = LOCATION_METHOD_NONE;
		g_object_get(handle->object, "method", &_method, NULL);
		if (_method != LOCATION_METHOD_GPS) {
			LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__,
			     LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
			return LOCATIONS_ERROR_INCORRECT_METHOD;
		}
	} else if (handle->method != LOCATIONS_METHOD_GPS) {
		LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__,
		     LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
		return LOCATIONS_ERROR_INCORRECT_METHOD;
	}
	gchar *nmea_data = NULL;
	g_object_get(handle->object, "nmea", &nmea_data, NULL);
	if (nmea_data == NULL) {
		LOGE("[%s] LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE(0x%08x) : nmea data is NULL ", __FUNCTION__,
		     LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE);
		return LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;
	}
	*nmea = NULL;
	*nmea = strdup(nmea_data);
	if (*nmea == NULL) {
		LOGE("[%s] LOCATIONS_ERROR_OUT_OF_MEMORY(0x%08x) : fail to strdup ", __FUNCTION__,
		     LOCATIONS_ERROR_OUT_OF_MEMORY);
		return LOCATIONS_ERROR_OUT_OF_MEMORY;
	}
	g_free(nmea_data);
	return LOCATIONS_ERROR_NONE;
}

int gps_status_get_satellite(location_manager_h manager, int *num_of_active, int *num_of_inview, time_t *timestamp)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(num_of_active);
	LOCATIONS_NULL_ARG_CHECK(num_of_inview);
	LOCATIONS_NULL_ARG_CHECK(timestamp);
	location_manager_s *handle = (location_manager_s *) manager;
	if (handle->method == LOCATIONS_METHOD_HYBRID) {
		LocationMethod _method = LOCATION_METHOD_NONE;
		g_object_get(handle->object, "method", &_method, NULL);
		if (_method != LOCATION_METHOD_GPS) {
			LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__,
			     LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
			return LOCATIONS_ERROR_INCORRECT_METHOD;
		}
	} else if (handle->method != LOCATIONS_METHOD_GPS) {
		LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__,
		     LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
		return LOCATIONS_ERROR_INCORRECT_METHOD;
	}

	LocationSatellite *sat = NULL;
	g_object_get(handle->object, "satellite", &sat, NULL);
	if (sat == NULL) {
		LOGE("[%s] LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE(0x%08x) : satellite is NULL ", __FUNCTION__,
		     LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE);
		return LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;
	}

	*num_of_active = sat->num_of_sat_used;
	*num_of_inview = sat->num_of_sat_inview;
	*timestamp = sat->timestamp;
	location_satellite_free(sat);
	sat = NULL;
	return LOCATIONS_ERROR_NONE;
}

int gps_status_foreach_satellites_in_view(location_manager_h manager, gps_status_get_satellites_cb callback, void *user_data)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(callback);
	location_manager_s *handle = (location_manager_s *) manager;
	if (handle->method == LOCATIONS_METHOD_HYBRID) {
		LocationMethod _method = LOCATION_METHOD_NONE;
		g_object_get(handle->object, "method", &_method, NULL);
		if (_method != LOCATION_METHOD_GPS) {
			LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__,
			     LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
			return LOCATIONS_ERROR_INCORRECT_METHOD;
		}
	} else if (handle->method != LOCATIONS_METHOD_GPS) {
		LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__,
		     LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
		return LOCATIONS_ERROR_INCORRECT_METHOD;
	}

	LocationSatellite *sat = NULL;
	g_object_get(handle->object, "satellite", &sat, NULL);
	if (sat == NULL) {
		LOGE("[%s] LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE(0x%08x) : satellite is NULL ", __FUNCTION__,
		     LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE);
		return LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE;
	}

	int i;
	for (i = 0; i < sat->num_of_sat_inview; i++) {
		guint prn;
		gboolean used;
		guint elevation;
		guint azimuth;
		gint snr;
		location_satellite_get_satellite_details(sat, i, &prn, &used, &elevation, &azimuth, &snr);
		if (callback(azimuth, elevation, prn, snr, used, user_data) != TRUE)
			break;
	}
	location_satellite_free(sat);
	sat = NULL;
	return LOCATIONS_ERROR_NONE;
}

int gps_status_get_last_satellite(location_manager_h manager, int *num_of_active, int *num_of_inview, time_t *timestamp)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(num_of_active);
	LOCATIONS_NULL_ARG_CHECK(num_of_inview);
	LOCATIONS_NULL_ARG_CHECK(timestamp);
	location_manager_s *handle = (location_manager_s *) manager;
	int ret;
	if (handle->method == LOCATIONS_METHOD_HYBRID) {
		LocationMethod _method = LOCATION_METHOD_NONE;
		g_object_get(handle->object, "method", &_method, NULL);
		if (_method != LOCATION_METHOD_GPS) {
			LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__,
			     LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
			return LOCATIONS_ERROR_INCORRECT_METHOD;
		}
	} else if (handle->method != LOCATIONS_METHOD_GPS) {
		LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__,
		     LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
		return LOCATIONS_ERROR_INCORRECT_METHOD;
	}

	LocationSatellite *last_sat = NULL;
	ret = location_get_last_satellite(handle->object, &last_sat);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}

	*num_of_active = last_sat->num_of_sat_used;
	*num_of_inview = last_sat->num_of_sat_inview;
	*timestamp = last_sat->timestamp;
	location_satellite_free(last_sat);
	return LOCATIONS_ERROR_NONE;
}

int gps_status_foreach_last_satellites_in_view(location_manager_h manager, gps_status_get_satellites_cb callback,
					       void *user_data)
{
	LOCATIONS_NULL_ARG_CHECK(manager);
	LOCATIONS_NULL_ARG_CHECK(callback);
	location_manager_s *handle = (location_manager_s *) manager;
	int ret;
	if (handle->method == LOCATIONS_METHOD_HYBRID) {
		LocationMethod _method = LOCATION_METHOD_NONE;
		g_object_get(handle->object, "method", &_method, NULL);
		if (_method != LOCATION_METHOD_GPS) {
			LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__,
			     LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
			return LOCATIONS_ERROR_INCORRECT_METHOD;
		}
	} else if (handle->method != LOCATIONS_METHOD_GPS) {
		LOGE("[%s] LOCATIONS_ERROR_INCORRECT_METHOD(0x%08x) : method - %d", __FUNCTION__,
		     LOCATIONS_ERROR_INCORRECT_METHOD, handle->method);
		return LOCATIONS_ERROR_INCORRECT_METHOD;
	}

	LocationSatellite *last_sat = NULL;
	ret = location_get_last_satellite(handle->object, &last_sat);
	if (ret != LOCATION_ERROR_NONE) {
		return __convert_error_code(ret, (char *)__FUNCTION__);
	}

	int i;
	for (i = 0; i < last_sat->num_of_sat_inview; i++) {
		guint prn;
		gboolean used;
		guint elevation;
		guint azimuth;
		gint snr;
		location_satellite_get_satellite_details(last_sat, i, &prn, &used, &elevation, &azimuth, &snr);
		if (callback(azimuth, elevation, prn, snr, used, user_data) != TRUE) {
			break;
		}
	}
	location_satellite_free(last_sat);
	return LOCATIONS_ERROR_NONE;
}
