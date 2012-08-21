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

static void utc_location_location_manager_create_p(void);
static void utc_location_location_manager_create_p_02(void);
static void utc_location_location_manager_create_p_03(void);
static void utc_location_location_manager_create_p_04(void);
static void utc_location_location_manager_create_p_05(void);
static void utc_location_location_manager_create_n(void);
static void utc_location_location_manager_create_n_02(void);
static void utc_location_location_manager_create_n_03(void);
static void utc_location_location_manager_create_n_04(void);
static void utc_location_location_manager_create_n_05(void);
static void utc_location_location_manager_create_n_06(void);
static void utc_location_location_manager_add_boundary_p(void);
static void utc_location_location_manager_add_boundary_n(void);
static void utc_location_location_manager_add_boundary_n_02(void);
static void utc_location_location_manager_add_boundary_n_03(void);
static void utc_location_location_manager_add_boundary_n_04(void);
static void utc_location_location_manager_foreach_boundary_p(void);
static void utc_location_location_manager_foreach_boundary_n(void);
static void utc_location_location_manager_foreach_boundary_n_02(void);
static void utc_location_location_manager_foreach_boundary_n_03(void);
static void utc_location_location_manager_foreach_boundary_n_04(void);
static void utc_location_location_manager_remove_boundary_p(void);
static void utc_location_location_manager_remove_boundary_n(void);
static void utc_location_location_manager_remove_boundary_n_02(void);
static void utc_location_location_manager_remove_boundary_n_03(void);
static void utc_location_location_manager_remove_boundary_n_04(void);
static void utc_location_location_manager_get_method_p(void);
static void utc_location_location_manager_get_method_n(void);
static void utc_location_location_manager_get_method_n_02(void);
static void utc_location_location_manager_get_method_n_03(void);
static void utc_location_location_manager_get_method_n_04(void);
static void utc_location_location_manager_get_position_p(void);
static void utc_location_location_manager_get_position_n(void);
static void utc_location_location_manager_get_position_n_02(void);
static void utc_location_location_manager_get_position_n_03(void);
static void utc_location_location_manager_get_position_n_04(void);
static void utc_location_location_manager_get_position_n_05(void);
static void utc_location_location_manager_get_position_n_06(void);
static void utc_location_location_manager_get_velocity_p(void);
static void utc_location_location_manager_get_velocity_n(void);
static void utc_location_location_manager_get_velocity_n_02(void);
static void utc_location_location_manager_get_velocity_n_03(void);
static void utc_location_location_manager_get_velocity_n_04(void);
static void utc_location_location_manager_get_velocity_n_05(void);
static void utc_location_location_manager_get_velocity_n_06(void);
static void utc_location_location_manager_get_accuracy_p(void);
static void utc_location_location_manager_get_accuracy_n(void);
static void utc_location_location_manager_get_accuracy_n_02(void);
static void utc_location_location_manager_get_accuracy_n_03(void);
static void utc_location_location_manager_get_accuracy_n_04(void);
static void utc_location_location_manager_get_accuracy_n_05(void);
static void utc_location_location_manager_get_accuracy_n_06(void);
static void utc_location_location_bounds_foreach_polygon_coords_p(void);
static void utc_location_location_bounds_foreach_polygon_coords_n(void);
static void utc_location_location_bounds_foreach_polygon_coords_n_02(void);
static void utc_location_location_bounds_get_circle_coords_p(void);
static void utc_location_location_bounds_get_circle_coords_n(void);
static void utc_location_location_bounds_get_circle_coords_n_02(void);
static void utc_location_location_bounds_get_circle_coords_n_03(void);
static void utc_location_location_bounds_get_rect_coords_p(void);
static void utc_location_location_bounds_get_rect_coords_n(void);
static void utc_location_location_bounds_get_rect_coords_n_02(void);
static void utc_location_location_bounds_get_rect_coords_n_03(void);
static void utc_location_location_bounds_contains_coordinates_p(void);
static void utc_location_location_bounds_contains_coordinates_p_02(void);
static void utc_location_location_bounds_contains_coordinates_n(void);
static void utc_location_location_bounds_contains_coordinates_n_02(void);
static void utc_location_location_manager_get_last_accuracy_p(void);
static void utc_location_location_manager_get_last_accuracy_n(void);
static void utc_location_location_manager_get_last_accuracy_n_02(void);
static void utc_location_location_manager_get_last_accuracy_n_03(void);
static void utc_location_location_manager_get_last_accuracy_n_04(void);
static void utc_location_location_manager_get_last_position_p(void);
static void utc_location_location_manager_get_last_position_n(void);
static void utc_location_location_manager_get_last_position_n_02(void);
static void utc_location_location_manager_get_last_position_n_03(void);
static void utc_location_location_manager_get_last_position_n_04(void);
static void utc_location_location_manager_get_last_position_n_05(void);
static void utc_location_location_manager_get_last_velocity_p(void);
static void utc_location_location_manager_get_last_velocity_n(void);
static void utc_location_location_manager_get_last_velocity_n_02(void);
static void utc_location_location_manager_get_last_velocity_n_03(void);
static void utc_location_location_manager_get_last_velocity_n_04(void);
static void utc_location_location_manager_get_last_velocity_n_05(void);
static void utc_location_location_manager_is_supported_method_p(void);
static void utc_location_location_manager_is_supported_method_p_02(void);
static void utc_location_location_manager_is_supported_method_p_03(void);
static void utc_location_location_manager_is_supported_method_p_04(void);
static void utc_location_location_manager_is_supported_method_n(void);
static void utc_location_location_manager_is_supported_method_n_02(void);
static void utc_location_location_manager_send_command_p(void);
static void utc_location_location_manager_send_command_n(void);
static void utc_location_location_manager_destroy_p(void);
static void utc_location_location_manager_destroy_n(void);
static void utc_location_location_manager_destroy_n_02(void);

struct tet_testlist tet_testlist[] = {
	{utc_location_location_manager_create_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_create_p_02, POSITIVE_TC_IDX},
	{utc_location_location_manager_create_p_03, POSITIVE_TC_IDX},
      { utc_location_location_manager_create_p_04, POSITIVE_TC_IDX },
//      { utc_location_location_manager_create_p_05, POSITIVE_TC_IDX }, // LOCATIONS_METHOD_NONE is a negative TC.
	{utc_location_location_manager_create_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_create_n_02, NEGATIVE_TC_IDX},
	{utc_location_location_manager_create_n_03, NEGATIVE_TC_IDX},
	{utc_location_location_manager_create_n_04, NEGATIVE_TC_IDX},
	{utc_location_location_manager_create_n_05, NEGATIVE_TC_IDX},
	{utc_location_location_manager_create_n_06, NEGATIVE_TC_IDX},
	{utc_location_location_manager_add_boundary_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_add_boundary_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_add_boundary_n_02, NEGATIVE_TC_IDX},
	{utc_location_location_manager_add_boundary_n_03, NEGATIVE_TC_IDX},
	{utc_location_location_manager_add_boundary_n_04, NEGATIVE_TC_IDX},
	{utc_location_location_manager_foreach_boundary_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_foreach_boundary_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_foreach_boundary_n_02, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_foreach_boundary_n_03, NEGATIVE_TC_IDX }, // Can't check created location_manager_h
	{utc_location_location_manager_foreach_boundary_n_04, NEGATIVE_TC_IDX},
	{utc_location_location_manager_remove_boundary_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_remove_boundary_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_remove_boundary_n_02, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_remove_boundary_n_03, NEGATIVE_TC_IDX },  // Can't check created location_manager_h
	{utc_location_location_manager_remove_boundary_n_04, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_method_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_get_method_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_method_n_02, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_method_n_03, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_get_method_n_04, NEGATIVE_TC_IDX }, // Can't check created location_manager_h
	{utc_location_location_manager_get_position_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_get_position_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_position_n_02, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_get_position_n_03, NEGATIVE_TC_IDX },  // Can't check created location_manager_h
	{utc_location_location_manager_get_position_n_04, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_position_n_05, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_position_n_06, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_velocity_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_get_velocity_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_velocity_n_02, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_get_velocity_n_03, NEGATIVE_TC_IDX }, // Can't check created location_manager_h
	{utc_location_location_manager_get_velocity_n_04, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_velocity_n_05, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_velocity_n_06, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_accuracy_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_get_accuracy_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_accuracy_n_02, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_get_accuracy_n_03, NEGATIVE_TC_IDX }, // Can't check created location_manager_h
	{utc_location_location_manager_get_accuracy_n_04, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_accuracy_n_05, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_accuracy_n_06, NEGATIVE_TC_IDX},
	{utc_location_location_bounds_foreach_polygon_coords_p, POSITIVE_TC_IDX},
	{utc_location_location_bounds_foreach_polygon_coords_n, NEGATIVE_TC_IDX},
	{utc_location_location_bounds_foreach_polygon_coords_n_02, NEGATIVE_TC_IDX},
	{utc_location_location_bounds_get_circle_coords_p, POSITIVE_TC_IDX},
	{utc_location_location_bounds_get_circle_coords_n, NEGATIVE_TC_IDX},
	{utc_location_location_bounds_get_circle_coords_n_02, NEGATIVE_TC_IDX},
	{utc_location_location_bounds_get_circle_coords_n_03, NEGATIVE_TC_IDX},
	{utc_location_location_bounds_get_rect_coords_p, POSITIVE_TC_IDX},
	{utc_location_location_bounds_get_rect_coords_n, NEGATIVE_TC_IDX},
	{utc_location_location_bounds_get_rect_coords_n_02, NEGATIVE_TC_IDX},
	{utc_location_location_bounds_get_rect_coords_n_03, NEGATIVE_TC_IDX},
	{utc_location_location_bounds_contains_coordinates_p, POSITIVE_TC_IDX},
	{utc_location_location_bounds_contains_coordinates_p_02, POSITIVE_TC_IDX},
	{utc_location_location_bounds_contains_coordinates_n, NEGATIVE_TC_IDX},
	{utc_location_location_bounds_contains_coordinates_n_02, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_accuracy_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_get_last_accuracy_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_accuracy_n_02, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_accuracy_n_03, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_accuracy_n_04, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_position_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_get_last_position_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_position_n_02, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_position_n_03, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_position_n_04, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_position_n_05, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_velocity_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_get_last_velocity_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_velocity_n_02, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_velocity_n_03, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_velocity_n_04, NEGATIVE_TC_IDX},
	{utc_location_location_manager_get_last_velocity_n_05, NEGATIVE_TC_IDX},
	{utc_location_location_manager_is_supported_method_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_is_supported_method_p_02, POSITIVE_TC_IDX},
	{utc_location_location_manager_is_supported_method_p_03, POSITIVE_TC_IDX},
	{utc_location_location_manager_is_supported_method_p_04, POSITIVE_TC_IDX},
	{utc_location_location_manager_is_supported_method_n, NEGATIVE_TC_IDX},
	{utc_location_location_manager_is_supported_method_n_02, NEGATIVE_TC_IDX},
	{utc_location_location_manager_destroy_p, POSITIVE_TC_IDX},
	{utc_location_location_manager_destroy_n, NEGATIVE_TC_IDX},
//      { utc_location_location_manager_destroy_n_02, NEGATIVE_TC_IDX }, // Can't check created location_manager_h
	{NULL, 0},
};

static bool service_enabled = false;
static bool touch_foreach_bounds = false;

static GMainLoop *g_mainloop = NULL;
static GThread *event_thread;

gpointer GmainThread(gpointer data)
{
	g_mainloop = g_main_loop_new(NULL, 0);
	g_main_loop_run(g_mainloop);
	return NULL;
}

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

static void wait_for_service(char *api_name)
{
	int timeout = 0;
	for (timeout; timeout < 60; timeout++) {
		if (service_enabled) {
			dts_message(api_name, "Location Service Enabled!!!!");
			break;
		} else {
			dts_message(api_name, "Location Service Disabled!!!!");
			sleep(1);
		}
	}
}

static void wait_for_bounds_foreach(char *api_name)
{
	int timeout = 0;
	for (timeout; timeout < 30; timeout++) {
		if (touch_foreach_bounds) {
			dts_message(api_name, "bound foreach called!!!!");
			break;
		} else {
			dts_message(api_name, "No bound foreach!!!!");
			sleep(1);
		}
	}
}

static void __state_changed_cb(location_service_state_e state, void *user_data)
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

static bool __location_bounds_cb(location_bounds_h bounds, void *user_data)
{
	if (bounds == NULL)
		printf("bounds ==NULL\n");
	else {
		location_bounds_type_e type;
		location_bounds_get_type(bounds, &type);
		dts_message(__func__, "__location_bounds_cb - type : %d!!!!", type);
		touch_foreach_bounds = TRUE;
	}
	return TRUE;
}

static location_manager_h manager;
static location_bounds_h bounds_rect;
static location_bounds_h bounds_circle;
static location_bounds_h bounds_poly;

static void startup(void)
{
	g_setenv("PKG_NAME", "com.samsung.capi-location-manager-test", 1);
	g_setenv("LOCATION_TEST_ENABLE", "1", 1);

#if !GLIB_CHECK_VERSION (2, 31, 0)
	if (!g_thread_supported()) {
		g_thread_init(NULL);
	}
#endif

	event_thread = g_thread_create(GmainThread, NULL, 1, NULL);
}

static void cleanup(void)
{
	if (manager) {
		location_manager_unset_service_state_changed_cb(manager);
		location_manager_stop(manager);
		location_manager_destroy(manager);
		manager = NULL;
	}

	service_enabled = false;
	touch_foreach_bounds = false;
	g_main_loop_quit(g_mainloop);
	g_thread_join(event_thread);
}

static void utc_location_location_manager_create_p(void)
{
	int ret;

	ret = location_manager_create(LOCATIONS_METHOD_HYBRID, &manager);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_create() is failed");

	ret = location_manager_set_service_state_changed_cb(manager, __state_changed_cb, NULL);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_set_service_state_changed_cb() is failed");

	ret = location_manager_start(manager);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_start() is failed");

	wait_for_service(__func__);

	/*
	   location_manager_stop(manager); //If you call start() and then stop(), service_enabled always set false.
	   location_manager_unset_service_state_changed_cb(manager);
	 */

	validate_eq(__func__, service_enabled, true);
}

static void utc_location_location_manager_create_p_02(void)
{
	int ret;
	location_manager_h manager_02;

	ret = location_manager_create(LOCATIONS_METHOD_GPS, &manager_02);

	/* We don't need it
	   validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_create() is failed");

	   ret = location_manager_set_service_state_changed_cb(manager_02, __state_changed_cb, NULL);
	   validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_set_service_state_changed_cb() is failed");

	   ret = location_manager_start(manager_02);
	   validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_start() is failed");

	   wait_for_service(__func__);

	   location_manager_stop(manager_02);
	   location_manager_unset_service_state_changed_cb(manager_02);
	 */

	location_manager_destroy(manager_02);

	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_create_p_03(void)
{
	int ret;
	location_manager_h manager_02;

	ret = location_manager_create(LOCATIONS_METHOD_WPS, &manager_02);

	/* We don't need it
	   validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_create() is failed");

	   ret = location_manager_set_service_state_changed_cb(manager_02, __state_changed_cb, NULL);
	   validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_set_service_state_changed_cb() is failed");

	   ret = location_manager_start(manager_02);
	   validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_start() is failed");

	   wait_for_service(__func__);

	   location_manager_stop(manager_02);
	   location_manager_unset_service_state_changed_cb(manager_02);
	 */

	location_manager_destroy(manager_02);

	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_create_p_04(void)
{
	int ret;
	location_manager_h manager_02;

	ret = location_manager_create(LOCATIONS_METHOD_CPS, &manager_02);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_create() is failed");

	ret = location_manager_set_service_state_changed_cb(manager_02, __state_changed_cb, NULL);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_set_service_state_changed_cb() is failed");

	ret = location_manager_start(manager_02);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_start() is failed");

	wait_for_service(__func__);

	location_manager_stop(manager_02);
	location_manager_unset_service_state_changed_cb(manager_02);
	location_manager_destroy(manager_02);

	validate_eq(__func__, service_enabled, TRUE);
}

static void utc_location_location_manager_create_p_05(void)
{
	int ret;
	location_manager_h manager_02;

	ret = location_manager_create(LOCATIONS_METHOD_NONE, &manager_02);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_create() is failed");

	ret = location_manager_set_service_state_changed_cb(manager_02, __state_changed_cb, NULL);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_set_service_state_changed_cb() is failed");

	ret = location_manager_start(manager_02);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_start() is failed");

	wait_for_service(__func__);

	location_manager_stop(manager_02);
	location_manager_unset_service_state_changed_cb(manager_02);
	location_manager_destroy(manager_02);

	validate_eq(__func__, service_enabled, TRUE);
}

static void utc_location_location_manager_create_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_manager_create(LOCATIONS_METHOD_HYBRID, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_location_manager_create_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_manager_create(LOCATIONS_METHOD_NONE, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_location_manager_create_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_manager_create(LOCATIONS_METHOD_GPS, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_location_manager_create_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_manager_create(LOCATIONS_METHOD_WPS, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_location_manager_create_n_05(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_manager_create(LOCATIONS_METHOD_CPS, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_location_manager_create_n_06(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;

	ret = location_manager_create(LOCATIONS_METHOD_CPS + 1, &manager_02);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_location_manager_add_boundary_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	//Add the circle bounds
	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;
	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	validate_and_next(__func__, ret, LOCATION_BOUNDS_ERROR_NONE, "location_bounds_create_circle() is failed");

	ret = location_manager_add_boundary(manager, bounds_circle);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_add_boundary() is failed");

	//Add the rect bounds
	location_coords_s left_top;
	left_top.latitude = 30;
	left_top.longitude = 30;

	location_coords_s right_bottom;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	validate_and_next(__func__, ret, LOCATION_BOUNDS_ERROR_NONE, "location_bounds_create_rect() is failed");

	ret = location_manager_add_boundary(manager, bounds_rect);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_add_boundary() is failed");

	//Add the polygon bounds

	int poly_size = 3;
	location_coords_s coord_list[poly_size];

	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 30;

	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	validate_and_next(__func__, ret, LOCATION_BOUNDS_ERROR_NONE, "location_bounds_create_polygon() is failed");

	ret = location_manager_add_boundary(manager, bounds_poly);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_add_boundary_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_add_boundary(NULL, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_add_boundary_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_add_boundary(manager, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_add_boundary_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	//Add the circle bounds
	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;
	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	validate_and_next(__func__, ret, LOCATION_BOUNDS_ERROR_NONE, "location_bounds_create_circle() is failed");

	ret = location_manager_add_boundary(NULL, bounds_circle);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_add_boundary_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;

	//Add the circle bounds
	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;
	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	validate_and_next(__func__, ret, LOCATION_BOUNDS_ERROR_NONE, "location_bounds_create_circle() is failed");

	ret = location_manager_add_boundary(manager_02, bounds_circle);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_foreach_boundary_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_foreach_boundary(manager, __location_bounds_cb, (void *)manager);
	validate_and_next(__func__, ret, LOCATION_BOUNDS_ERROR_NONE, "location_manager_foreach_boundary() is failed");
	wait_for_bounds_foreach(__func__);
	validate_eq(__func__, touch_foreach_bounds, TRUE);
}

static void utc_location_location_manager_foreach_boundary_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_foreach_boundary(NULL, NULL, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_foreach_boundary_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_foreach_boundary(NULL, __location_bounds_cb, (void *)manager);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_foreach_boundary_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;
	ret = location_manager_foreach_boundary(manager_02, __location_bounds_cb, (void *)manager);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_foreach_boundary_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;
	ret = location_manager_foreach_boundary(manager, NULL, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_remove_boundary_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_remove_boundary(manager, bounds_rect);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_remove_boundary(rect) is failed");
	ret = location_manager_remove_boundary(manager, bounds_circle);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_remove_boundary(circle) is failed");
	ret = location_manager_remove_boundary(manager, bounds_poly);
	location_bounds_destroy(bounds_rect);
	location_bounds_destroy(bounds_circle);
	location_bounds_destroy(bounds_poly);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_remove_boundary_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_remove_boundary(NULL, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_remove_boundary_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_remove_boundary(NULL, bounds_rect);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_remove_boundary_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;
	ret = location_manager_remove_boundary(manager_02, bounds_rect);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_remove_boundary_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_remove_boundary(manager, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_method_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_method_e method;
	ret = location_manager_get_method(manager, &method);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_get_method_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_get_method(NULL, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_location_manager_get_method_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_get_method(manager, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_location_manager_get_method_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_method_e method;
	ret = location_manager_get_method(NULL, &method);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_location_manager_get_method_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;
	location_method_e method;
	ret = location_manager_get_method(manager_02, &method);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_location_manager_get_position_p(void)
{

	int ret = LOCATIONS_ERROR_NONE;

	double altitude;
	double latitude;
	double longitude;
	time_t timestamp;

	ret = location_manager_get_position(manager, &altitude, &latitude, &longitude, &timestamp);
	dts_message(__func__, "altitude : %lf, latitude : %lf, longitude : %lf, timestamp:%d", latitude, latitude, longitude,
		    timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_get_position_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double latitude;
	double longitude;
	time_t timestamp;

	ret = location_manager_get_position(manager, NULL, &latitude, &longitude, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_position_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double altitude;
	double latitude;
	double longitude;
	time_t timestamp;

	ret = location_manager_get_position(NULL, &altitude, &latitude, &longitude, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_position_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double altitude;
	double latitude;
	double longitude;
	time_t timestamp;
	location_manager_h manager_02;

	ret = location_manager_get_position(manager_02, &altitude, &latitude, &longitude, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_position_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double altitude;
	double longitude;
	time_t timestamp;

	ret = location_manager_get_position(manager, &altitude, NULL, &longitude, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_position_n_05(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double altitude;
	double latitude;
	time_t timestamp;

	ret = location_manager_get_position(manager, &altitude, &latitude, NULL, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_position_n_06(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double altitude;
	double latitude;
	double longitude;

	ret = location_manager_get_position(manager, &altitude, &latitude, &longitude, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_velocity_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int climb;
	int direction;
	int speed;
	time_t timestamp;

	ret = location_manager_get_velocity(manager, &climb, &direction, &speed, &timestamp);
	dts_message(__func__, "climb : %lf, direction : %lf, speed : %lf, timestamp:%d", climb, direction, speed, timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_get_velocity_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int direction;
	int speed;
	time_t timestamp;

	ret = location_manager_get_velocity(manager, NULL, &direction, &speed, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_velocity_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int climb;
	int direction;
	int speed;
	time_t timestamp;

	ret = location_manager_get_velocity(NULL, &climb, &direction, &speed, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_velocity_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int climb;
	int direction;
	int speed;
	time_t timestamp;
	location_manager_h manager_02;

	ret = location_manager_get_velocity(manager_02, &climb, &direction, &speed, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_velocity_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int climb;
	int speed;
	time_t timestamp;

	ret = location_manager_get_velocity(manager, &climb, NULL, &speed, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_velocity_n_05(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int climb;
	int direction;
	time_t timestamp;

	ret = location_manager_get_velocity(manager, &climb, &direction, NULL, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_velocity_n_06(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int climb;
	int direction;
	int speed;

	ret = location_manager_get_velocity(manager, &climb, &direction, &speed, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_accuracy_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_accuracy_level_e level;
	double horizontal;
	double vertical;

	ret = location_manager_get_accuracy(manager, &level, &horizontal, &vertical);
	dts_message(__func__, "Level : %lf, horizontal : %lf, vertical : %lf", level, horizontal, vertical);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_get_accuracy_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_manager_get_accuracy(manager, NULL, NULL, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_accuracy_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_accuracy_level_e level;
	double horizontal;
	double vertical;

	ret = location_manager_get_accuracy(NULL, &level, &horizontal, &vertical);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_accuracy_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_accuracy_level_e level;
	double horizontal;
	double vertical;
	location_manager_h manager_02;

	ret = location_manager_get_accuracy(manager_02, &level, &horizontal, &vertical);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_accuracy_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double horizontal;
	double vertical;

	ret = location_manager_get_accuracy(manager, NULL, &horizontal, &vertical);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_accuracy_n_05(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_accuracy_level_e level;
	double vertical;

	ret = location_manager_get_accuracy(manager, &level, NULL, &vertical);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_accuracy_n_06(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_accuracy_level_e level;
	double horizontal;

	ret = location_manager_get_accuracy(manager, &level, &horizontal, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static bool capi_poly_coords_cb(location_coords_s coords, void *user_data)
{
	printf("location_bounds_foreach_rect_coords(latitude : %lf, longitude: %lf) \n", coords.latitude, coords.longitude);
	return TRUE;
}

static void utc_location_location_bounds_foreach_polygon_coords_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	//Add the polygon bounds
	int poly_size = 3;
	location_coords_s coord_list[poly_size];

	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 30;

	location_bounds_h bounds_poly;
	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_bounds_create_polygon() is failed");

	ret = location_bounds_foreach_polygon_coords(bounds_poly, capi_poly_coords_cb, NULL);

	location_bounds_destroy(bounds_poly);

	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_bounds_foreach_polygon_coords_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_bounds_foreach_polygon_coords(NULL, capi_poly_coords_cb, NULL);

	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_bounds_foreach_polygon_coords_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	//Add the polygon bounds
	int poly_size = 3;
	location_coords_s coord_list[poly_size];

	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 30;

	location_bounds_h bounds_poly;
	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_bounds_create_polygon() is failed");

	ret = location_bounds_foreach_polygon_coords(bounds_poly, NULL, NULL);

	location_bounds_destroy(bounds_poly);

	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_bounds_get_circle_coords_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;
	location_bounds_h bounds_circle;
	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_bounds_create_circle() is failed");

	location_coords_s center2;
	double radius2;
	ret = location_bounds_get_circle_coords(bounds_circle, &center2, &radius2);

	location_bounds_destroy(bounds_circle);

	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_bounds_get_circle_coords_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_coords_s center2;
	double radius2;
	ret = location_bounds_get_circle_coords(NULL, &center2, &radius2);

	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_bounds_get_circle_coords_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;
	location_bounds_h bounds_circle;
	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_bounds_create_circle() is failed");

	double radius2;
	ret = location_bounds_get_circle_coords(bounds_circle, NULL, &radius2);

	location_bounds_destroy(bounds_circle);

	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_bounds_get_circle_coords_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;
	location_bounds_h bounds_circle;
	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_bounds_create_circle() is failed");

	location_coords_s center2;
	ret = location_bounds_get_circle_coords(bounds_circle, &center2, NULL);

	location_bounds_destroy(bounds_circle);

	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_bounds_get_rect_coords_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	//Add the rect bounds
	location_coords_s left_top;
	left_top.latitude = 30;
	left_top.longitude = 30;

	location_coords_s right_bottom;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	location_bounds_h bounds_rect;
	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_bounds_create_rect() is failed");

	location_coords_s left_top2;
	location_coords_s right_bottom2;
	ret = location_bounds_get_rect_coords(bounds_rect, &left_top2, &right_bottom2);

	location_bounds_destroy(bounds_rect);

	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_bounds_get_rect_coords_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_coords_s left_top2;
	location_coords_s right_bottom2;
	ret = location_bounds_get_rect_coords(NULL, &left_top2, &right_bottom2);

	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_bounds_get_rect_coords_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	//Add the rect bounds
	location_coords_s left_top;
	left_top.latitude = 30;
	left_top.longitude = 30;

	location_coords_s right_bottom;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	location_bounds_h bounds_rect;
	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_bounds_create_rect() is failed");

	location_coords_s right_bottom2;
	ret = location_bounds_get_rect_coords(bounds_rect, NULL, &right_bottom2);

	location_bounds_destroy(bounds_rect);

	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_bounds_get_rect_coords_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	//Add the rect bounds
	location_coords_s left_top;
	left_top.latitude = 30;
	left_top.longitude = 30;

	location_coords_s right_bottom;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	location_bounds_h bounds_rect;
	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_bounds_create_rect() is failed");

	location_coords_s left_top2;
	ret = location_bounds_get_rect_coords(bounds_rect, &left_top2, NULL);

	location_bounds_destroy(bounds_rect);

	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_bounds_contains_coordinates_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	//Add the polygon bounds
	int poly_size = 3;
	location_coords_s coord_list[poly_size];

	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 10;

	location_bounds_h bounds_poly;
	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_bounds_create_polygon() is failed");

	location_coords_s test_coords;
	test_coords.latitude = 20;
	test_coords.longitude = 12;
	bool contained = FALSE;
	contained = location_bounds_contains_coordinates(bounds_poly, test_coords);

	location_bounds_destroy(bounds_poly);

	validate_eq(__func__, contained, TRUE);
}

static void utc_location_location_bounds_contains_coordinates_p_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	//Add the polygon bounds
	int poly_size = 3;
	location_coords_s coord_list[poly_size];

	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 10;

	location_bounds_h bounds_poly;
	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_bounds_create_polygon() is failed");

	location_coords_s test_coords;
	test_coords.latitude = 50;
	test_coords.longitude = 50;
	bool contained = FALSE;
	contained = location_bounds_contains_coordinates(bounds_poly, test_coords);

	location_bounds_destroy(bounds_poly);

	validate_eq(__func__, contained, FALSE);
}


static void utc_location_location_bounds_contains_coordinates_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_coords_s test_coords;
	test_coords.latitude = 12;
	test_coords.longitude = 12;
	ret = location_bounds_contains_coordinates(NULL, test_coords);

	validate_eq(__func__, ret, FALSE);
}

static void utc_location_location_bounds_contains_coordinates_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	//Add the polygon bounds
	int poly_size = 3;
	location_coords_s coord_list[poly_size];

	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 10;

	location_bounds_h bounds_poly;
	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_bounds_create_polygon() is failed");

	location_coords_s coord_test;
	coord_test.latitude = -91;
	coord_test.longitude = 181;
	ret = location_bounds_contains_coordinates(bounds_poly, coord_test);

	location_bounds_destroy(bounds_poly);

	validate_eq(__func__, ret, FALSE);
}

static void utc_location_location_manager_get_last_accuracy_p(void)
{

	int ret = LOCATIONS_ERROR_NONE;

	double horizontal, vertical;
	location_accuracy_level_e level;

	ret = location_manager_get_last_accuracy(manager, &level, &horizontal, &vertical);
	dts_message(__func__, "Level : %d, horizontal: %g, vertical : %g\n", level, horizontal, vertical);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_get_last_accuracy_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double horizontal, vertical;
	location_accuracy_level_e level;

	ret = location_manager_get_last_accuracy(NULL, &level, &horizontal, &vertical);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_accuracy_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double horizontal, vertical;

	ret = location_manager_get_last_accuracy(manager, NULL, &horizontal, &vertical);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_accuracy_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double vertical;
	location_accuracy_level_e level;

	ret = location_manager_get_last_accuracy(manager, &level, NULL, &vertical);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_accuracy_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double horizontal;
	location_accuracy_level_e level;

	ret = location_manager_get_last_accuracy(manager, &level, &horizontal, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_position_p(void)
{

	int ret = LOCATIONS_ERROR_NONE;

	double altitude;
	double latitude;
	double longitude;
	time_t timestamp;

	ret = location_manager_get_last_position(manager, &altitude, &latitude, &longitude, &timestamp);
	dts_message(__func__, "altitude : %lf, latitude : %lf, longitude : %lf, timestamp:%d", latitude, latitude, longitude,
		    timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_get_last_position_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double altitude;
	double latitude;
	double longitude;
	time_t timestamp;

	ret = location_manager_get_last_position(NULL, &altitude, &latitude, &longitude, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_position_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double latitude;
	double longitude;
	time_t timestamp;

	ret = location_manager_get_last_position(manager, NULL, &latitude, &longitude, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_position_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double altitude;
	double longitude;
	time_t timestamp;

	ret = location_manager_get_last_position(manager, &altitude, NULL, &longitude, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_position_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double altitude;
	double latitude;
	time_t timestamp;

	ret = location_manager_get_last_position(manager, &altitude, &latitude, NULL, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_position_n_05(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	double altitude;
	double latitude;
	double longitude;

	ret = location_manager_get_last_position(manager, &altitude, &latitude, &longitude, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_velocity_p(void)
{

	int ret = LOCATIONS_ERROR_NONE;

	int climb;
	int direction;
	int speed;
	time_t timestamp;

	ret = location_manager_get_last_velocity(manager, &climb, &direction, &speed, &timestamp);
	dts_message(__func__, "climb : %lf, direction : %lf, speed : %lf, timestamp:%d", climb, direction, speed, timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_get_last_velocity_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int climb;
	int direction;
	int speed;
	time_t timestamp;

	ret = location_manager_get_last_velocity(NULL, &climb, &direction, &speed, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_velocity_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int direction;
	int speed;
	time_t timestamp;

	ret = location_manager_get_last_velocity(manager, NULL, &direction, &speed, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_velocity_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int climb;
	int speed;
	time_t timestamp;

	ret = location_manager_get_last_velocity(manager, &climb, NULL, &speed, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_velocity_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int climb;
	int direction;
	time_t timestamp;

	ret = location_manager_get_last_velocity(manager, &climb, &direction, NULL, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_get_last_velocity_n_05(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int climb;
	int direction;
	int speed;

	ret = location_manager_get_last_velocity(manager, &climb, &direction, &speed, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_is_supported_method_p(void)
{
	bool supported = FALSE;
	supported = location_manager_is_supported_method(LOCATIONS_METHOD_HYBRID);
	validate_eq(__func__, supported, TRUE);
}

static void utc_location_location_manager_is_supported_method_p_02(void)
{
	bool supported = FALSE;
	supported = location_manager_is_supported_method(LOCATIONS_METHOD_GPS);
	validate_eq(__func__, supported, TRUE);
}

static void utc_location_location_manager_is_supported_method_p_03(void)
{
	bool supported = FALSE;
	supported = location_manager_is_supported_method(LOCATIONS_METHOD_WPS);
	validate_eq(__func__, supported, TRUE);
}

static void utc_location_location_manager_is_supported_method_p_04(void)
{
	bool supported = FALSE;
	supported = location_manager_is_supported_method(LOCATIONS_METHOD_CPS);
	validate_eq(__func__, supported, TRUE);
}

static void utc_location_location_manager_is_supported_method_n(void)
{
	bool supported = FALSE;
	supported = location_manager_is_supported_method(LOCATIONS_METHOD_NONE);
	validate_eq(__func__, supported, FALSE);
}

static void utc_location_location_manager_is_supported_method_n_02(void)
{
	bool supported = FALSE;
	supported = location_manager_is_supported_method(LOCATIONS_METHOD_CPS + 1);
	validate_eq(__func__, supported, FALSE);
}

static void utc_location_location_manager_send_command_p(void)
{

	int ret = LOCATIONS_ERROR_NONE;

	const *str = "command";
	ret = location_manager_send_command(str);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_location_manager_send_command_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_manager_send_command(NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_location_manager_destroy_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = location_manager_destroy(manager);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);

}

static void utc_location_location_manager_destroy_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = location_manager_destroy(NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_location_manager_destroy_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	location_manager_h manager_02;

	ret = location_manager_destroy(manager_02);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}
