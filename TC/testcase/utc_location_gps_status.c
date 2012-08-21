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

static void utc_location_gps_status_get_nmea_p(void);
static void utc_location_gps_status_get_nmea_n(void);
static void utc_location_gps_status_get_nmea_n_02(void);
static void utc_location_gps_status_get_nmea_n_03(void);
static void utc_location_gps_status_get_satellite_p(void);
static void utc_location_gps_status_get_satellite_n(void);
static void utc_location_gps_status_get_satellite_n_02(void);
static void utc_location_gps_status_get_satellite_n_03(void);
static void utc_location_gps_status_get_satellite_n_04(void);
static void utc_location_gps_status_get_satellite_n_05(void);
static void utc_location_gps_status_get_satellite_n_06(void);
static void utc_location_gps_status_foreach_satellites_in_view_p(void);
static void utc_location_gps_status_foreach_satellites_in_view_n(void);
static void utc_location_gps_status_foreach_satellites_in_view_n_02(void);
static void utc_location_gps_status_foreach_satellites_in_view_n_03(void);
static void utc_location_gps_status_foreach_last_satellites_in_view_p(void);
static void utc_location_gps_status_foreach_last_satellites_in_view_n(void);
static void utc_location_gps_status_foreach_last_satellites_in_view_n_02(void);
static void utc_location_gps_status_get_last_satellite_p(void);
static void utc_location_gps_status_get_last_satellite_n(void);
static void utc_location_gps_status_get_last_satellite_n_02(void);
static void utc_location_gps_status_get_last_satellite_n_03(void);
static void utc_location_gps_status_get_last_satellite_n_04(void);



struct tet_testlist tet_testlist[] = {
	{utc_location_gps_status_get_nmea_p, POSITIVE_TC_IDX},
	{utc_location_gps_status_get_nmea_n, NEGATIVE_TC_IDX},
	{utc_location_gps_status_get_nmea_n_02, NEGATIVE_TC_IDX},
//      {utc_location_gps_status_get_nmea_n_03, NEGATIVE_TC_IDX}, //Can't check created location_manager_h
	{utc_location_gps_status_get_satellite_p, POSITIVE_TC_IDX},
	{utc_location_gps_status_get_satellite_n, NEGATIVE_TC_IDX},
	{utc_location_gps_status_get_satellite_n_02, NEGATIVE_TC_IDX},
//      {utc_location_gps_status_get_satellite_n_03, NEGATIVE_TC_IDX}, //Can't check created location_manager_h
	{utc_location_gps_status_get_satellite_n_04, NEGATIVE_TC_IDX},
	{utc_location_gps_status_get_satellite_n_05, NEGATIVE_TC_IDX},
	{utc_location_gps_status_get_satellite_n_06, NEGATIVE_TC_IDX},
	{utc_location_gps_status_foreach_satellites_in_view_p, POSITIVE_TC_IDX},
	{utc_location_gps_status_foreach_satellites_in_view_n, NEGATIVE_TC_IDX},
	{utc_location_gps_status_foreach_satellites_in_view_n_02, NEGATIVE_TC_IDX},
//      {utc_location_gps_status_foreach_satellites_in_view_n_03, NEGATIVE_TC_IDX }, //Can't check created location_manager_h
	{utc_location_gps_status_foreach_last_satellites_in_view_p, POSITIVE_TC_IDX},
	{utc_location_gps_status_foreach_last_satellites_in_view_n, NEGATIVE_TC_IDX},
	{utc_location_gps_status_foreach_last_satellites_in_view_n_02, NEGATIVE_TC_IDX},
	{utc_location_gps_status_get_last_satellite_p, POSITIVE_TC_IDX},
	{utc_location_gps_status_get_last_satellite_n, NEGATIVE_TC_IDX},
	{utc_location_gps_status_get_last_satellite_n_02, NEGATIVE_TC_IDX},
	{utc_location_gps_status_get_last_satellite_n_03, NEGATIVE_TC_IDX},
	{utc_location_gps_status_get_last_satellite_n_04, NEGATIVE_TC_IDX},
	{NULL, 0},
};

static GMainLoop *g_mainloop = NULL;
static GThread *event_thread;

gpointer GmainThread(gpointer data)
{
	g_mainloop = g_main_loop_new(NULL, 0);
	g_main_loop_run(g_mainloop);

	return NULL;
}

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

static location_manager_h manager;

static void startup(void)
{
	g_setenv("PKG_NAME", "com.samsung.capi-location-gps-status-test", 1);
	g_setenv("LOCATION_TEST_ENABLE", "1", 1);

#if !GLIB_CHECK_VERSION (2, 31, 0)
	if (!g_thread_supported()) {
		g_thread_init(NULL);
	}
#endif

	GError *gerr = NULL;
	event_thread = g_thread_create(GmainThread, NULL, 1, &gerr);

	int ret;
	ret = location_manager_create(LOCATIONS_METHOD_GPS, &manager);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_create() is failed");

	/* You don't need it
	   ret = location_manager_set_service_state_changed_cb(manager, capi_state_changed_cb, NULL);
	   validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_set_service_state_changed_cb() is failed");
	 */

	ret = location_manager_start(manager);
	validate_and_next(__func__, ret, LOCATIONS_ERROR_NONE, "location_manager_start() is failed");

	wait_for_service(__func__);
}

static void cleanup(void)
{
	unprepare(manager);
	g_main_loop_quit(g_mainloop);
	g_thread_join(event_thread);
}

static void utc_location_gps_status_get_nmea_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	char *nmea;
	ret = gps_status_get_nmea(manager, &nmea);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_gps_status_get_nmea_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = gps_status_get_nmea(manager, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_get_nmea_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	char *nmea;
	ret = gps_status_get_nmea(NULL, &nmea);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_gps_status_get_nmea_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	char *nmea;
	location_manager_h manager_02;
	ret = gps_status_get_nmea(manager_02, &nmea);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);

}

static void utc_location_gps_status_get_satellite_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	int num_of_active, num_of_inview;
	time_t timestamp;
	ret = gps_status_get_satellite(manager, &num_of_active, &num_of_inview, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_gps_status_get_satellite_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = gps_status_get_satellite(manager, NULL, NULL, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_get_satellite_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	int num_of_active, num_of_inview;
	time_t timestamp;
	ret = gps_status_get_satellite(NULL, &num_of_active, &num_of_inview, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_get_satellite_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	int num_of_active, num_of_inview;
	time_t timestamp;
	location_manager_h manager_02;
	ret = gps_status_get_satellite(manager_02, &num_of_active, &num_of_inview, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_get_satellite_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	int num_of_inview;
	time_t timestamp;
	ret = gps_status_get_satellite(manager, NULL, &num_of_inview, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_get_satellite_n_05(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	int num_of_active;
	time_t timestamp;
	ret = gps_status_get_satellite(manager, &num_of_active, NULL, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_get_satellite_n_06(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	int num_of_active, num_of_inview;
	ret = gps_status_get_satellite(manager, &num_of_active, &num_of_inview, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static bool capi_gps_status_get_satellites_cb(unsigned int azimuth, unsigned int elevation, unsigned int prn, int snr,
					      bool is_in_use, void *user_data)
{
	return true;
}

static void utc_location_gps_status_foreach_satellites_in_view_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = gps_status_foreach_satellites_in_view(manager, capi_gps_status_get_satellites_cb, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_gps_status_foreach_satellites_in_view_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = gps_status_foreach_satellites_in_view(manager, NULL, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_foreach_satellites_in_view_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = gps_status_foreach_satellites_in_view(NULL, capi_gps_status_get_satellites_cb, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_foreach_satellites_in_view_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	location_manager_h manager_02;
	ret = gps_status_foreach_satellites_in_view(manager_02, capi_gps_status_get_satellites_cb, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static bool capi_last_satellites_foreach_cb(unsigned int azimuth, unsigned int elevation, unsigned int prn, int snr, bool is_in_use,
				       void *user_data)
{
	printf("[Last Satellite information]  azimuth  : %d, elevation : %d, prn :%d, snr : %d, used: %d\n", azimuth, elevation,
	       prn, snr, is_in_use);
	return true;
}

static void utc_location_gps_status_foreach_last_satellites_in_view_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	ret = gps_status_foreach_last_satellites_in_view(manager, capi_last_satellites_foreach_cb, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_gps_status_foreach_last_satellites_in_view_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = gps_status_foreach_last_satellites_in_view(manager, NULL, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_foreach_last_satellites_in_view_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;
	ret = gps_status_foreach_last_satellites_in_view(NULL, capi_last_satellites_foreach_cb, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_get_last_satellite_p(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	time_t timestamp;
	int num_of_inview, num_of_active;
	ret = gps_status_get_last_satellite(manager, &num_of_active, &num_of_inview, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_NONE);
}

static void utc_location_gps_status_get_last_satellite_n(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	time_t timestamp;
	int num_of_inview, num_of_active;
	ret = gps_status_get_last_satellite(NULL, &num_of_active, &num_of_inview, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_get_last_satellite_n_02(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	time_t timestamp;
	int num_of_inview;
	ret = gps_status_get_last_satellite(manager, NULL, &num_of_inview, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_get_last_satellite_n_03(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	time_t timestamp;
	int num_of_active;
	ret = gps_status_get_last_satellite(manager, &num_of_active, NULL, &timestamp);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}

static void utc_location_gps_status_get_last_satellite_n_04(void)
{
	int ret = LOCATIONS_ERROR_NONE;

	int num_of_inview, num_of_active;
	ret = gps_status_get_last_satellite(manager, &num_of_active, &num_of_inview, NULL);
	validate_eq(__func__, ret, LOCATIONS_ERROR_INVALID_PARAMETER);
}


