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

#ifndef __TIZEN_LOCATION_LOCATIONS_PRIVATE_H__
#define	__TIZEN_LOCATION_LOCATIONS_PRIVATE_H__

#include <location/location.h>
#include <locations.h>
#include <location_bounds.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	_LOCATIONS_EVENT_TYPE_SERVICE_STATE,
	_LOCATIONS_EVENT_TYPE_POSITION,
	_LOCATIONS_EVENT_TYPE_VELOCITY,
	_LOCATIONS_EVENT_TYPE_BOUNDARY,
	_LOCATIONS_EVENT_TYPE_SATELLITE,
	_LOCATIONS_EVENT_TYPE_FOREACH_BOUNDS,
	_LOCATIONS_EVENT_TYPE_NUM
}_location_event_e;

typedef struct _location_manager_s{
	LocationObject* object;
	const void* user_cb[_LOCATIONS_EVENT_TYPE_NUM];
	void* user_data[_LOCATIONS_EVENT_TYPE_NUM];
	location_method_e method;
	bool is_continue_foreach_bounds;
} location_manager_s;

#ifdef __cplusplus
}
#endif

#endif //__TIZEN_LOCATION_LOCATIONS_PRIVATE_H__
