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

#include <tet_api.h>
#include <locations.h>
#include <glib.h>

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

static void startup(void);
static void cleanup(void);

void (*tet_startup) (void) = startup;
void (*tet_cleanup) (void) = cleanup;

static void utc_location_location_manager_start_p(void);
static void utc_location_location_manager_start_n(void);
static void utc_location_location_manager_start_n_02(void);
static void utc_location_location_manager_set_position_updated_callback_p(void);
static void utc_location_location_manager_set_position_updated_callback_n(void);
static void utc_location_location_manager_set_position_updated_callback_n_02(void);
static void utc_location_location_manager_set_position_updated_callback_n_03(void);
static void utc_location_location_manager_set_position_updated_callback_n_04(void);
static void utc_location_location_manager_set_position_updated_callback_n_05(void);
static void utc_location_location_manager_unset_position_updated_callback_p(void);
static void utc_location_location_manager_unset_position_updated_callback_n(void);
static void utc_location_location_manager_set_velocity_updated_callback_p(void);
static void utc_location_location_manager_set_velocity_updated_callback_n(void);
static void utc_location_location_manager_set_velocity_updated_callback_n_02(void);
static void utc_location_location_manager_set_velocity_updated_callback_n_03(void);
static void utc_location_location_manager_unset_velocity_updated_callback_p(void);
static void utc_location_location_manager_unset_velocity_updated_callback_n(void);
static void utc_location_location_manager_set_service_state_changed_callback_p(void);
static void utc_location_location_manager_set_service_state_changed_callback_n(void);
static void utc_location_location_manager_set_service_state_changed_callback_n_02(void);
static void utc_location_location_manager_set_service_state_changed_callback_n_03(void);
static void utc_location_location_manager_unset_service_state_changed_callback_p(void);
static void utc_location_location_manager_unset_service_state_changed_callback_n(void);
static void utc_location_location_manager_set_zone_changed_callback_p(void);
static void utc_location_location_manager_set_zone_changed_callback_n(void);
static void utc_location_location_manager_set_zone_changed_callback_n_02(void);
static void utc_location_location_manager_set_zone_changed_callback_n_03(void);
static void utc_location_location_manager_unset_zone_changed_callback_p(void);
static void utc_location_location_manager_unset_zone_changed_callback_n(void);
static void utc_location_location_manager_stop_p(void);
static void utc_location_location_manager_stop_n(void);
static void utc_location_location_manager_stop_n_02(void);

struct tet_testlist tet_testlist[] = {
	{utc_location_location_manager_start_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_start_n, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_start_n_02, NEGATIVE_TC_IDX }, //Can't check address of created location_manager_h
	{utc_location_location_manager_set_position_updated_callback_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_set_position_updated_callback_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_unset_position_updated_callback_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_unset_position_updated_callback_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_set_velocity_updated_callback_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_set_velocity_updated_callback_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_set_velocity_updated_callback_n_02, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_set_velocity_updated_callback_n_03, NEGATIVE_TC_IDX }, //Can't check address of created location_manager_h
	{utc_location_location_manager_unset_velocity_updated_callback_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_unset_velocity_updated_callback_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_set_service_state_changed_callback_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_set_service_state_changed_callback_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_set_service_state_changed_callback_n_02, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_set_service_state_changed_callback_n_03, NEGATIVE_TC_IDX }, // Can't check address of created location_manager_h
	{utc_location_location_manager_unset_service_state_changed_callback_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_unset_service_state_changed_callback_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_set_zone_changed_callback_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_set_zone_changed_callback_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_set_zone_changed_callback_n_02, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_set_zone_changed_callback_n_03, NEGATIVE_TC_IDX }, // Can't check address of created location_manager_h
	{utc_location_location_manager_unset_zone_changed_callback_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_unset_zone_changed_callback_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_stop_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_stop_n, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_stop_n_02, NEGATIVE_TC_IDX }, //Can't check address of created location_manager_h
	{NULL, 0},
};

static bool service_enabled = false;

static void validate_and_next(char *api_name, int act_ret, int ext_ret, char *fail_msg)
{
	dts_message(api_name, "Actual Result : %d, Expected Result : %d", act_ret, ext_ret);
	if (act_ret != ext_ret) {
		dts_message(api_name, "Fail Message: %s", fail_msg);
		dts_fail(api_name);
	}
}

static void validate_eq(char *api_name, int act_ret, int ext_ret)
{
	dts_message(api_name, "Actual Result : %d, Expected Result : %d", act_ret, ext_ret);
	if (act_ret == ext_ret) {
		dts_pass(api_name);
	} else {
		dts_fail(api_name);
	}
}

static void validate_neq(char *api_name, int act_ret, int ext_ret)
{
	dts_message(api_name, "Actual Result : %d, N-Expected Result : %d", act_ret, ext_ret);
	if (act_ret != ext_ret) {
		dts_pass(api_name);
	} else {
		dts_fail(api_name);
	}
}

static void unprepare(location_manager_h manager)
{
	location_manager_unset_service_state_changed_cb(manager);
	location_manager_destroy(manager);
	service_enabled = false;
}

static void wait_for_service(char *api_name)
{
	int timeout = 0;
	for (timeout; timeout < 30; timeout++) {
		if (service_enabled) {
			dts_message(api_name, "Location Service Enabled!!!!");
			break;
		} else {
			dts_message(api_name, "Location Service Disabled!!!!");
			sleep(1);
		}
	}
}

static void capi_state_changed_cb(location_service_state_e state, void *user_data)
{
	switch (state) {
	case LOCATIONS_SERVICE_ENABLED:
		service_enabled = true;
		break;
	case LOCATIONS_SERVICE_DISABLED:
		service_enabled = false;
		break;
	default:
		break;
	}
}

static GMainLoop *g_mainloop = NULL;
static GThread *event_thread;

gpointer GmainThread(gpointer data)
{
	g_mainloop = g_main_loop_new(NULL, 0);
	g_main_loop_run(g_mainloop);
	return NULL;
}

static location_manager_h manager;

static void startup(void)
{
	g_setenv("PKG_NAME", "com.samsung.capi-location-manager-callback-test", 1);
	g_setenv("LOCATION_TEST_ENABLE", "1", 1);

#if !GLIB_CHECK_VERSION (2, 31, 0)
	if (!g_thread_supported()) {
		g_thread_init(NULL);
	}
#endif

	GError *gerr = NULL;
	event_thread = g_thread_create(GmainThread, NULL, 1, &gerr);

}

static void cleanup(void)
{
	unprepare(manager);
	g_main_loop_quit(g_mainloop);
	g_thread_join(event_thread);
}

static void capi_position_updated_cb(double latitude, double longitude, double altitude, time_t timestamp, void *user_data)
{
}

static void capi_zone_changed_cb(location_boundary_state_e state, double latitude, double longitude, double altitude,
				 time_t timestamp, void *user_data)
{
}

static void capi_velocity_updated_cb(double speed, double direction, double climb, time_t timestamp, void *user_data)
{
}

static bool capi_geocoder_get_position_cb(double latitude, double longitude, void *user_data)
{
	return true;
}

static void utc_location_location_manager_start_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_manager_create(LOCATIONS_METHOD_HYBRID, &manager);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_create() is failed");

	ret = location_manager_set_service_state_changed_cb(manager, capi_state_changed_cb, NULL);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_set_service_state_changed_cb() is failed");

	ret = location_manager_start(manager);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_start() is failed");
	wait_for_service(__func__);

	validate_eq(__func__, service_enabled, true);

}

static void utc_location_location_manager_start_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_manager_start(NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_start_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_manager_h manager_02;

	ret = location_manager_start(manager_02);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_set_position_updated_callback_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_position_updated_cb(manager, capi_position_updated_cb, 1, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_position_updated_callback_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_position_updated_cb(manager, NULL, 1, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_position_updated_callback_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_position_updated_cb(NULL, capi_position_updated_cb, 1, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_position_updated_callback_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;
	ret = location_manager_set_position_updated_cb(manager_02, capi_position_updated_cb, 1, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_position_updated_callback_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_position_updated_cb(manager, capi_position_updated_cb, 0, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_position_updated_callback_n_05(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_position_updated_cb(manager, capi_position_updated_cb, 121, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_unset_position_updated_callback_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_unset_position_updated_cb(manager);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_unset_position_updated_callback_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_unset_position_updated_cb(NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_velocity_updated_callback_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_velocity_updated_cb(manager, capi_velocity_updated_cb, 1, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_velocity_updated_callback_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_velocity_updated_cb(manager, NULL, 1, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);

}

static void utc_location_location_manager_set_velocity_updated_callback_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_velocity_updated_cb(NULL, capi_velocity_updated_cb, 1, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);

}

static void utc_location_location_manager_set_velocity_updated_callback_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;
	ret = location_manager_set_velocity_updated_cb(manager_02, capi_velocity_updated_cb, 1, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);

}

static void utc_location_location_manager_unset_velocity_updated_callback_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_unset_velocity_updated_cb(manager);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_unset_velocity_updated_callback_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_unset_velocity_updated_cb(NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_service_state_changed_callback_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_service_state_changed_cb(manager, capi_state_changed_cb, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_service_state_changed_callback_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_service_state_changed_cb(manager, NULL, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_service_state_changed_callback_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_service_state_changed_cb(NULL, capi_state_changed_cb, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_service_state_changed_callback_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;
	ret = location_manager_set_service_state_changed_cb(manager_02, capi_state_changed_cb, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_unset_service_state_changed_callback_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_unset_service_state_changed_cb(manager);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_unset_service_state_changed_callback_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_unset_service_state_changed_cb(NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);

}

static void utc_location_location_manager_set_zone_changed_callback_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_zone_changed_cb(manager, capi_zone_changed_cb, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);

}

static void utc_location_location_manager_set_zone_changed_callback_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_zone_changed_cb(manager, NULL, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_zone_changed_callback_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_set_zone_changed_cb(NULL, capi_zone_changed_cb, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_set_zone_changed_callback_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;
	ret = location_manager_set_zone_changed_cb(manager_02, capi_zone_changed_cb, NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_unset_zone_changed_callback_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_unset_zone_changed_cb(manager);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_unset_zone_changed_callback_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_unset_zone_changed_cb(NULL);
	validate_neq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_stop_p(void)
{

	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_stop(manager);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_stop_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_manager_stop(NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_stop_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;

	ret = location_manager_stop(manager_02);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}
