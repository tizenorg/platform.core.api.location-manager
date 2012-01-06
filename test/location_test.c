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
#include <glib.h>
#include <locations.h>

location_manager_h manager;

void zone_event_cb(location_boundary_state_e state, double latitude, double longitude, double altitude, time_t timestamp, void *user_data)
{
    if (state == LOCATIONS_BOUNDARY_IN)
    {
        printf("Entering zone\n");
    }
    else // state == LOCATIONS_BOUNDARY_OUT
    {
        printf("Leaving zone\n");
    }

    printf("Latitude: %lf, longitude: %lf, altitude: %lf\n", latitude, longitude, altitude);

    printf("Time: %s\n", ctime(&timestamp));
}


static bool  satellites_foreach_cb(unsigned int azimuth, unsigned int elevation, unsigned int prn, int snr, bool is_in_use, void *user_data)
{
	printf("[Satellite information]  azimuth  : %d, elevation : %d, prn :%d, snr : %d, used: %d\n",azimuth, elevation, prn, snr, is_in_use);
	return true;
}

static void _state_change_cb(location_service_state_e state, void *user_data)
{
 	fprintf(stderr, "--------------------------state change %d---------\n", state);
	location_manager_h lm = (location_manager_h)user_data;
	if(state == LOCATIONS_SERVICE_ENABLED)
	{
		int ret;
		double altitude;
		double latitude;
		double longitude;
		time_t timestamp;
		ret = location_manager_get_position(lm, &altitude,&latitude,&longitude, &timestamp);
		if (ret != LOCATIONS_ERROR_NONE)
	    {
			printf(" Fail : location_manager_get_position ---> %d \n",ret);
		}
		else
		{
			printf("alt: %g, lat %g, long %g\n", altitude,latitude, longitude);
		}

		location_accuracy_level_e level;
		double horizontal;
		double vertical;
		ret = location_manager_get_accuracy(lm, &level, &horizontal, &vertical );
		if (ret != LOCATIONS_ERROR_NONE)
	    {
			printf(" Fail : location_manager_get_accuracy ---> %d \n",ret);
		}
		else
		{
			printf("Level : %d, horizontal: %g, vertical %g\n", level, horizontal,vertical);
		}

		char *nmea;
		ret = gps_status_get_nmea(lm,&nmea);
		if (ret != LOCATIONS_ERROR_NONE)
	    {
			printf(" Fail : gps_status_get_nmea ---> %d \n",ret);
		}
		else
		{
			printf("NMEA : %s\n",nmea);
			free(nmea);
		}

		int count_in_view, count_in_used;
		ret = gps_status_get_satellite_count_in_view	(lm,&count_in_view);
		if (ret != LOCATIONS_ERROR_NONE)
	    {
			printf(" Fail : gps_status_get_satellite_count_in_view ---> %d \n",ret);
		}
		else
		{
			printf("Satellite count in view : %d\n",count_in_view);
		}
	
		ret = gps_status_get_active_satellite_count(lm,&count_in_used);
		if (ret != LOCATIONS_ERROR_NONE)
	    {
				printf(" Fail : gps_status_get_active_satellite_count ---> %d \n",ret);
		}
		else
		{
			printf("Satellite count in used : %d\n",count_in_used);
		}

		ret = gps_status_foreach_satellites_in_view(lm,satellites_foreach_cb ,user_data);		
		if (ret != LOCATIONS_ERROR_NONE)
	    {
			printf(" Fail : gps_status_foreach_satellites_in_view ---> %d \n",ret);
		}
		
	}
}

int location_test()
{
	int ret ;
	ret=  location_manager_create(LOCATIONS_METHOD_GPS,&manager);
	printf("create : %d\n",ret);


	double center_latitude = 37.258;
    double center_longitude = 127.056;
    double radius = 30;

    ret = location_manager_set_boundary_circle(manager, center_latitude, center_longitude, radius);
    if (ret != LOCATIONS_ERROR_NONE)
    {
        // Setting boundary failed, handle the error
        // ...
        printf("Setting boundary failed\n");
    } else printf("Boundary set\n");

	ret = location_manager_set_zone_changed_cb(manager, zone_event_cb, (void*)manager);
	printf("set zone callback : %d\n",ret);		
	

	ret = location_manager_set_service_state_changed_cb(manager, _state_change_cb, (void*)manager);
	printf("set state callback : %d\n",ret);	

	ret = location_manager_start(manager);
	printf("start :  %d\n",ret);	
	return 1;
}

static GMainLoop *g_mainloop = NULL;

static gboolean exit_program (gpointer data)
{
	if(manager==NULL)
	{
		printf("manager == NULL \n");	
	}
	else
	{	
		int ret =location_manager_stop(manager);
		printf("stop :  %d\n",ret);	
		ret =location_manager_destroy(manager);
		printf("destroy :  %d\n",ret);	
	}
	g_main_loop_quit (g_mainloop);
	printf("Quit g_main_loop\n");
	return FALSE;
}


int main(int argc, char ** argv)
{
	g_setenv("PKG_NAME", "com.samsung.location-test", 1);
	g_mainloop = g_main_loop_new (NULL, 0);
	location_test();	
	g_timeout_add_seconds(90, exit_program, NULL);
	g_main_loop_run (g_mainloop);
	return 0;
}

