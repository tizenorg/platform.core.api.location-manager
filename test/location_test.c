/*
 * Copyright (c) 2011-2013 Samsung Electronics Co., Ltd All Rights Reserved
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
#include <glib.h>
#include <locations.h>
#include <location_bounds.h>

static location_manager_h manager;
static GMainLoop *g_mainloop = NULL;
static char *menu;

static void location_cleanup();
static int location_test();

static gboolean exit_program(gpointer data)
{
	g_main_loop_quit(g_mainloop);

	return FALSE;
}

static gboolean wait_test()
{
	location_cleanup();
	location_test();

	return FALSE;
}

#if 0
void zone_event_cb(location_boundary_state_e state, double latitude, double longitude, double altitude, time_t timestamp,
                   void *user_data)
{
	if (state == LOCATIONS_BOUNDARY_IN) {
		printf("Entering zone\n");
	} else {		/* state == LOCATIONS_BOUNDARY_OUT */
		printf("Leaving zone\n");
	}

	printf("Latitude: %lf, longitude: %lf, altitude: %lf\n", latitude, longitude, altitude);

	printf("Time: %s\n", ctime(&timestamp));
}

static bool last_satellites_foreach_cb(unsigned int azimuth, unsigned int elevation, unsigned int prn, int snr, bool is_in_use,
                                       void *user_data)
{
	printf("[Last Satellite information]	azimuth	: %d, elevation: %d, prn: %d, snr: %d, used: %d\n", azimuth, elevation,
	       prn, snr, is_in_use);
	return true;
}
#endif

static bool satellites_foreach_cb(unsigned int azimuth, unsigned int elevation, unsigned int prn, int snr, bool is_in_use,
                                  void *user_data)
{
	printf("[Satellite information]	azimuth	: %d, elevation: %d, prn: %d, snr: %d, used: %d\n", azimuth, elevation, prn,
	       snr, is_in_use);
	return true;
}

static void _state_change_cb(location_service_state_e state, void *user_data)
{
	fprintf(stderr, "--------------------------state change %d---------\n", state);
	location_manager_h lm = (location_manager_h) user_data;
	if (state == LOCATIONS_SERVICE_ENABLED) {
		int ret;
		double altitude;
		double latitude;
		double longitude;
		time_t timestamp;
		ret = location_manager_get_position(lm, &altitude, &latitude, &longitude, &timestamp);
		if (ret != LOCATIONS_ERROR_NONE) {
			printf(" Fail: location_manager_get_position ---> %d \n", ret);
		} else {
			printf("[%ld] alt: %g, lat %g, long %g\n", timestamp, altitude, latitude, longitude);
		}

		location_accuracy_level_e level;
		double horizontal;
		double vertical;
		ret = location_manager_get_accuracy(lm, &level, &horizontal, &vertical);
		if (ret != LOCATIONS_ERROR_NONE) {
			printf(" Fail: location_manager_get_accuracy ---> %d \n", ret);
		} else {
			printf("Level: %d, horizontal: %g, vertical %g\n", level, horizontal, vertical);
		}

		char *nmea;
		ret = gps_status_get_nmea(lm, &nmea);
		if (ret != LOCATIONS_ERROR_NONE) {
			printf(" Fail: gps_status_get_nmea ---> %d \n", ret);
		} else {
			printf("NMEA: %s\n", nmea);
			free(nmea);
		}

		int num_of_view = 0, num_of_active = 0;
		ret = gps_status_get_satellite(lm, &num_of_active, &num_of_view, &timestamp);
		if (ret != LOCATIONS_ERROR_NONE) {
			printf(" Fail: gps_status_get_satellite_count_in_view ---> %d \n", ret);
		} else {
			printf("[%ld] Satellite number of active: %d, in view: %d\n", timestamp, num_of_active, num_of_view);
		}

		if (num_of_view) {
			ret = gps_status_foreach_satellites_in_view(lm, satellites_foreach_cb, user_data);
			if (ret != LOCATIONS_ERROR_NONE) {
				printf(" Fail: gps_status_foreach_satellites_in_view ---> %d \n", ret);
			}
		}
		g_timeout_add_seconds(1, wait_test, NULL);
	}
}

#if 0
static bool __poly_coords_cb(location_coords_s coords, void *user_data)
{
	printf("location_bounds_foreach_rect_coords(latitude: %lf, longitude: %lf) \n", coords.latitude, coords.longitude);
	return TRUE;
}

static bool __location_bounds_cb(location_bounds_h bounds, void *user_data)
{
	if (bounds == NULL)
		printf("bounds ==NULL\n");
	else {
		location_bounds_type_e type;
		location_bounds_get_type(bounds, &type);
		if (type == LOCATION_BOUNDS_CIRCLE) {
			location_coords_s center;
			double radius;
			location_bounds_get_circle_coords(bounds, &center, &radius);
			printf("location_bounds_get_circle_coords(center: %lf, %lf, radius: %lf) \n", center.latitude,
			       center.longitude, radius);

		} else if (type == LOCATION_BOUNDS_RECT) {
			location_coords_s left_top;
			location_coords_s right_bottom;
			location_bounds_get_rect_coords(bounds, &left_top, &right_bottom);
			printf("location_bounds_get_rect_coords(left_top: %lf, %lf - right_bottom: %lf, %lf) \n",
			       left_top.latitude, left_top.longitude, right_bottom.latitude, right_bottom.longitude);
		} else if (type == LOCATION_BOUNDS_POLYGON) {
			location_bounds_foreach_polygon_coords(bounds, __poly_coords_cb, NULL);
		}
	}
	return TRUE;
}

void location_bounds_test()
{
	int ret;
	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;
	location_bounds_h bounds_circle;
	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	if (ret != LOCATION_BOUNDS_ERROR_NONE) {
		printf("location_bounds_create_circle() failed\n");
	} else
		printf("Bounds(circle) has been created successfully.\n");

	ret = location_manager_add_boundary(manager, bounds_circle);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf("Setting boundary failed\n");
	} else
		printf("Boundary set\n");

	location_coords_s center2;
	double radius2;
	ret = location_bounds_get_circle_coords(bounds_circle, &center2, &radius2);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf("location_bounds_get_circle_coords() failed\n");
	} else
		printf("location_bounds_get_circle_coords(center: %lf, %lf, radius: %lf) \n", center2.latitude,
		       center2.longitude, radius2);

	/*Add the rect bounds */
	location_coords_s left_top;
	left_top.latitude = 30;
	left_top.longitude = 30;

	location_coords_s right_bottom;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	location_bounds_h bounds_rect;
	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	if (ret != LOCATION_BOUNDS_ERROR_NONE) {
		printf("location_bounds_create_rect() failed\n");
	} else
		printf("Bounds(rect) has been created successfully.\n");

	ret = location_manager_add_boundary(manager, bounds_rect);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf("Setting boundary failed\n");
	} else
		printf("Boundary set\n");

	location_coords_s left_top2;
	location_coords_s right_bottom2;

	ret = location_bounds_get_rect_coords(bounds_rect, &left_top2, &right_bottom2);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf("location_bounds_get_rect_coords() failed\n");
	} else
		printf("location_bounds_get_rect_coords(left_top: %lf, %lf - right_bottom: %lf, %lf) \n", left_top2.latitude,
		       left_top2.longitude, right_bottom2.latitude, right_bottom2.longitude);

	/*Add the polygon bounds */

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
	if (ret != LOCATION_BOUNDS_ERROR_NONE) {
		printf("location_bounds_create_polygon() failed\n");
	} else
		printf("Bounds(polygon) has been created successfully.\n");

	ret = location_manager_add_boundary(manager, bounds_poly);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf("Setting boundary failed\n");
	} else
		printf("Boundary set\n");

	ret = location_bounds_foreach_polygon_coords(bounds_poly, __poly_coords_cb, NULL);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf("location_bounds_get_rect_coords() failed\n");
	}

	location_coords_s test_coords;
	test_coords.latitude = 12;
	test_coords.longitude = 12;

	if (location_bounds_contains_coordinates(bounds_poly, test_coords))
		printf("location_bounds_contains_coordinates() retrun TRUE \n");
	else
		printf("location_bounds_contains_coordinates() retrun FALSE \n");

	/*print current bounds */
	ret = location_manager_foreach_boundary(manager, __location_bounds_cb, (void *)manager);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf("location_manager_foreach_boundary() failed\n");
	}

}

void location_get_last_information_test()
{
	int ret;
	double altitude, latitude, longitude;
	double climb, direction, speed;
	double horizontal, vertical;
	location_accuracy_level_e level;
	time_t timestamp;
	int num_of_inview, num_of_active;

	ret = location_manager_get_last_position(manager, &altitude, &latitude, &longitude, &timestamp);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf(" Fail: location_manager_get_last_position ---> %d \n", ret);
	} else {
		printf("[%ld] alt: %g, lat: %g, long: %g\n", timestamp, altitude, latitude, longitude);
	}

	ret = location_manager_get_last_velocity(manager, &climb, &direction, &speed, &timestamp);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf(" Fail: location_manager_get_last_velocity ---> %d \n", ret);
	} else {
		printf("climb: %f, direction: %f, speed: %f\n", climb, direction, speed);
	}

	ret = location_manager_get_last_accuracy(manager, &level, &horizontal, &vertical);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf(" Fail: location_manager_get_last_accuracy ---> %d \n", ret);
	} else {
		printf("Level: %d, horizontal: %g, vertical: %g\n", level, horizontal, vertical);
	}

	ret = gps_status_get_last_satellite(manager, &num_of_active, &num_of_inview, &timestamp);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf(" Fail: gps_status_get_last_satellite_count_in_view ---> %d \n", ret);
	} else {
		printf("[%ld] Satellite number of active: %d, in view: %d\n", timestamp, num_of_active, num_of_inview);
	}

	ret = gps_status_foreach_last_satellites_in_view(manager, last_satellites_foreach_cb, NULL);
	if (ret != LOCATIONS_ERROR_NONE) {
		printf(" Fail: gps_status_foreach_last_satellites_in_view ---> %d \n", ret);
	}
}
#endif

void location_cb(int error, double latitude, double longitude, double altitude, time_t timestamp, double speed, double climb, double direction, void *user_data)
{
	printf("error[%d]\n", error);
	printf("location_cb: lat[%f] lon[%f] alt[%f]\n", latitude, longitude, altitude);
	printf("speed[%f] climb[%f] direction[%f]\n", speed, climb, direction);

	g_timeout_add_seconds(1, wait_test, NULL);
}

static void __setting_cb(location_method_e method, bool enable, void *user_data)
{
	printf("method[%d], enable[%d]\n", method, enable);
}

static void select_menu()
{
	char buf[256];
	int len = 0;
	char *str = NULL;

	str = fgets(buf, 255, stdin);
	if (NULL == str) {
		printf("fgets return NULL. \n");
	}
	len = g_utf8_strlen(buf, -1);
	buf[len - 1] = '\0';

	g_free(menu);
	menu = g_strdup(buf);
}

static void print_menu()
{
	printf("==== LOCATION TEST ======\n");
	printf("[1] LOCATIONS_METHOD_HYBRID: Get location\n");
	printf("[2] LOCATIONS_METHOD_GPS: Get location\n");
	printf("[3] LOCATIONS_METHOD_WPS: Get location\n");
	printf("[4] LOCATIONS_METHOD_HYBRID: Single location\n");
	printf("[5] LOCATIONS_METHOD_GPS: Single location\n");
	printf("[x] Exit!!!\n\n");
	printf("Select menu: ");
}

static int location_test()
{
	int ret = LOCATIONS_ERROR_NONE;

	printf("==== LOCATION STATUS ======\n");
	bool is_enabled = FALSE;
	location_manager_is_enabled_method(LOCATIONS_METHOD_HYBRID, &is_enabled);
	printf("hybrid: %d, ", is_enabled);

	location_manager_is_enabled_method(LOCATIONS_METHOD_GPS, &is_enabled);
	printf("gps: %d, ", is_enabled);

	location_manager_is_enabled_method(LOCATIONS_METHOD_WPS, &is_enabled);
	printf("wps: %d\n", is_enabled);

	location_manager_set_setting_changed_cb(LOCATIONS_METHOD_GPS, __setting_cb, NULL);
	location_manager_set_setting_changed_cb(LOCATIONS_METHOD_WPS, __setting_cb, NULL);

	print_menu();
	select_menu();

	if (strcmp(menu, "1") == 0) {
		ret = location_manager_create(LOCATIONS_METHOD_HYBRID, &manager);
		printf("LOCATIONS_METHOD_HYBRID create: %d\n", ret);
		ret = location_manager_start(manager);
		printf("start: 	%d\n", ret);
	} else if (strcmp(menu, "2") == 0) {
		ret = location_manager_create(LOCATIONS_METHOD_GPS, &manager);
		printf("LOCATIONS_METHOD_GPS create: %d\n", ret);
		ret = location_manager_start(manager);
		printf("start: 	%d\n", ret);
	} else if (strcmp(menu, "3") == 0) {
		ret = location_manager_create(LOCATIONS_METHOD_WPS, &manager);
		printf("LOCATIONS_METHOD_WPS create: %d\n", ret);
	} else if (strcmp(menu, "4") == 0) {
		ret = location_manager_create(LOCATIONS_METHOD_HYBRID, &manager);
		printf("LOCATIONS_METHOD_HYBRID create: %d\n", ret);
		ret = location_manager_request_single_location(manager, 60, location_cb, manager);
		printf("single_location create: %d\n", ret);
	} else if (strcmp(menu, "5") == 0) {
		ret = location_manager_create(LOCATIONS_METHOD_GPS, &manager);
		printf("LOCATIONS_METHOD_HYBRID create: %d\n", ret);
		ret = location_manager_request_single_location(manager, 60, location_cb, manager);
		printf("single_location create: %d\n", ret);
	} else if (strcmp(menu, "x") == 0) {
		g_timeout_add_seconds(0.1, exit_program, NULL);
		return 0;
	} else {
		printf("Exit!!! Input: %s\n", menu);
		g_timeout_add_seconds(0.1, exit_program, NULL);
		return 0;
	}

	if (ret != LOCATIONS_ERROR_NONE) {
		printf("Test Failed!!! [%d]\n", ret);
		g_timeout_add_seconds(0.1, exit_program, NULL);
		return 0;
	}
	ret = location_manager_set_service_state_changed_cb(manager, _state_change_cb, (void *)manager);
	printf("set state callback: %d\n", ret);

	/* location_bounds_test(); */
	/* set zone changed callback */
	/*
	ret = location_manager_set_zone_changed_cb(manager, zone_event_cb, (void *)manager);
	printf("set zone callback: %d\n", ret);
	*/
	return 0;
}

static void location_cleanup()
{
	if (manager != NULL) {
		int ret = location_manager_stop(manager);
		printf("stop: %d\n", ret);
		ret = location_manager_destroy(manager);
		printf("destroy: %d\n", ret);
		manager = NULL;
	}
	location_manager_unset_setting_changed_cb(LOCATIONS_METHOD_GPS);
	location_manager_unset_setting_changed_cb(LOCATIONS_METHOD_WPS);
}

int main(int argc, char **argv)
{
	g_mainloop = g_main_loop_new(NULL, 0);
	location_test();
	g_main_loop_run(g_mainloop);
	location_cleanup();
	return 0;
}
