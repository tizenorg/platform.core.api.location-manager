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

#ifndef __TIZEN_LOCATION_LOCATIONS_H__
#define __TIZEN_LOCATION_LOCATIONS_H__

#include <tizen_type.h>
#include <tizen_error.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CAPI_LOCATION_MANAGER_MODULE
 * @{
 */

/**
 * @brief Enumerations of error code for Location manager.
 */
typedef enum
{
    LOCATIONS_ERROR_NONE = TIZEN_ERROR_NONE,                                        /**< Successful */
    LOCATIONS_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY,                    /**< Out of memory */
    LOCATIONS_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER,            /**< Invalid parameter */
    LOCATIONS_ERROR_INCORRECT_METHOD = TIZEN_ERROR_LOCATION_CLASS | 0x01,         /**< Location manager contains incorrect method for a given call */
    LOCATIONS_ERROR_NETWORK_FAILED = TIZEN_ERROR_LOCATION_CLASS | 0x02,           /**< Network unavailable */
    LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE = TIZEN_ERROR_LOCATION_CLASS | 0x03,    /**< Service unavailable */
    LOCATIONS_ERROR_GPS_SETTING_OFF = TIZEN_ERROR_LOCATION_CLASS | 0x04,    /**< GPS is not enabled  */
} location_error_e;



/**
 * @brief Location method type.
 */
typedef enum
{
    LOCATIONS_METHOD_NONE=-1,    /**< Undefined method. */
    LOCATIONS_METHOD_HYBRID,    /**< This method selects the best method available at the moment. */
    LOCATIONS_METHOD_GPS,       /**< This method uses Global Positioning System. */
    LOCATIONS_METHOD_WPS,       /**< This method uses Wifi Positioning System. */
    LOCATIONS_METHOD_SPS        /**< This method uses sensor. */
} location_method_e;

/**
 * @brief Approximate accuracy level of given information.
 */
typedef enum
{
    LOCATIONS_ACCURACY_NONE=0,      /**< Invalid data. */
    LOCATIONS_ACCURACY_COUNTRY,     /**< Country accuracy level. */
    LOCATIONS_ACCURACY_REGION,      /**< Regional accuracy level. */
    LOCATIONS_ACCURACY_LOCALITY,    /**< Local accuracy level. */
    LOCATIONS_ACCURACY_POSTALCODE,  /**< Postal accuracy level. */
    LOCATIONS_ACCURACY_STREET,      /**< Street accuracy level. */
    LOCATIONS_ACCURACY_DETAILED,    /**< Detailed accuracy level. */
} location_accuracy_level_e;

/**
 * @brief Enumerations of the state of the location service.
 */
typedef enum
{
    LOCATIONS_SERVICE_DISABLED, /**< Service is disabled */
    LOCATIONS_SERVICE_ENABLED  /**< Service is enabled */
} location_service_state_e;

/**
 * @brief Enumerations of the boundary state.
 */
typedef enum
{
    LOCATIONS_BOUNDARY_IN,  /**< Boundary In (Zone In) */
    LOCATIONS_BOUNDARY_OUT  /**< Boundary Out (Zone Out) */
} location_boundary_state_e;

/**
 * @brief The location manager handle.
 */
 typedef struct location_manager_s *location_manager_h;

/**
 * @}
 */
/*
 * Location Manager
*/
/**
 * @addtogroup CAPI_LOCATION_MANAGER_MODULE
 * @{
 */
/**
 * @brief Called every 1 second with updated position information.
 * @param[in] latitude  The updated latitude [-90.0 ~ 90.0] (degrees)
 * @param[in] longitude The updated longitude [-180.0 ~ 180.0] (degrees)
 * @param[in] altitude  The updated altitude (meters)
 * @param[in] timestamp  The timestamp (time when measurement took place)
 * @param[in] user_data  The user data passed from the call registration function
 * @pre location_manager_start() will invoke this callback if you register this callback using location_manager_set_position_updated_cb()
 * @see location_manager_start()
 * @see location_manager_set_position_updated_cb()
 */
typedef void(*location_position_updated_cb )(double latitude, double longitude, double altitude, time_t timestamp, void *user_data);

/**
 * @brief Called every 1 second with updated velocity information.
 * @param[in] speed  The updated speed (km/h)
 * @param[in] direction The updated direction (in degrees from the north)
 * @param[in] climb  The updated climb (km/h)
 * @param[in] timestamp  The timestamp (time when measurement took place)
 * @param[in] user_data  The user data passed from the callback registration function
 * @pre location_manager_start() will invoke this callback if you register this callback using location_manager_set_velocity_updated_cb()
 * @see location_manager_start()
 * @see location_manager_set_velocity_updated_cb()
 */
typedef void(*location_velocity_updated_cb )(double speed, double direction, double climb, time_t timestamp, void *user_data);

/**
 * @brief Called when the state of location service is changed from enabled to disabled or vice versa.
 * @param[in] state The service state
 * @param[in] user_data  The user data passed from the callback registration function
 * @pre Either location_manager_start() or location_manager_stop() will invoke this callback if you register this callback using location_manager_set_service_state_changed_cb()
 * @see location_manager_start()
 * @see location_manager_stop()
 * @see location_manager_set_service_state_changed_cb()
 * @see #location_service_state_e
 */
typedef void(*location_service_state_changed_cb )(location_service_state_e state, void *user_data);

/**
 * @brief Called when the user defined zones are entered or exited.
 * @param[in] state  The boundary state
 * @param[in] latitude  The updated latitude [-90.0 ~ 90.0] (degrees)
 * @param[in] longitude The updated longitude [-180.0 ~ 180.0] (degrees)
 * @param[in] altitude  The updated altitude (meters)
 * @param[in] timestamp  The timestamp (time when measurement took place)
 * @param[in] user_data  The user data passed from the callback registration function
 * @pre location_manager_start() will invoke this callback if you register this callback using location_manager_set_zone_changed_cb()
 * @see #location_boundary_state_e
 * @see location_manager_start()
 * @see location_manager_set_zone_changed_cb()
 */
typedef void(*location_zone_changed_cb )(location_boundary_state_e state, double latitude, double longitude, double altitude, time_t timestamp, void *user_data);

/**
 * @brief Checks whether the given location method is avaliable or not.
 * @param[in] method The location method to be checked
 * @return @c true if the specified location method is supported, \n else @c false
 * @see	location_manager_create()
 * @see location_manager_get_method()
 */
bool location_manager_is_supported_method(location_method_e method);


/**
 * @brief Creates a new location manager.
 * @remarks @a manager must be released location_manager_destroy() by you.
 * @param[in] method The location method
 * @param[out] manager  A location manager handle to be newly created on success
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval #LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE Service not available
 * @see location_manager_destroy()
 */
int location_manager_create(location_method_e method, location_manager_h* manager);

/**
 * @brief Releases the location manager.
 * @param[in] manager The location manager handle
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER	Invalid parameter
 * @see location_manager_create()
*/
int location_manager_destroy(location_manager_h manager);

/**
 * @brief Starts the location service. 
 *
 * @remarks There is no limit on number of location managers for which this function was called.
 *
 * Calling this function invokes a location service event. When the location service is enabled, the service state change callback 
 * (set using #location_manager_set_service_state_changed_cb()) notifies the user with #LOCATIONS_SERVICE_ENABLED as 
 * the first argument, and the service starts. \n

 * Started service is a requirement for calling these functions:
 *
 * location_manager_get_position(), location_manager_get_velocity(), location_manager_get_accuracy(),
 * #gps_status_get_nmea(), gps_status_get_satellite_count_in_view(), gps_status_foreach_satellites_in_view(), gps_status_get_active_satellite_count().
 *
 * Once you stop the service, using #location_manager_stop(), you can no longer call the functions listed above.
 *
 * Starting and stopping the service is in the scope of the given location manager only (if there's more than one manager,
 * starting and stopping should be executed for each of them separately).
 *
 * @param[in]   manager The location manager handle
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE Service not available
 * @retval #LOCATIONS_ERROR_NETWORK_FAILED Network failed
 * @retval #LOCATIONS_ERROR_GPS_SETTING_OFF GPS is not enabled
 * @post It invokes location_position_updated_cb(), location_velocity_updated_cb(), location_zone_changed_cb(), and location_service_state_changed_cb().
 * @see location_manager_stop()
 * @see location_manager_get_position()
 * @see location_manager_get_velocity()
 * @see location_manager_get_accuracy()
 * @see location_manager_set_service_state_changed_cb()
 * @see location_manager_set_position_updated_cb()
 * @see location_position_updated_cb()
 * @see location_manager_set_velocity_updated_cb()
 * @see location_velocity_updated_cb()
 * @see location_manager_set_zone_changed_cb()
 * @see location_zone_changed_cb()
 */
int location_manager_start(location_manager_h manager);

/**
 * @brief Stops the location service.
 * @remarks This function initiates the process of stopping the service. When the process is finished, callback set using
 * #location_manager_set_service_state_changed_cb() will be called, with #LOCATIONS_SERVICE_DISABLED as first argument.
 * When that happens, the service is stopped and the user is notified.
 *
 * You can stop and start the location manager as needed.
 *
 * @param[in]   manager The location manager handle
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE Service not available
 * @retval #LOCATIONS_ERROR_NETWORK_FAILED Network failed
 * @see location_manager_start()
 * @see	location_manager_set_service_state_changed_cb()
 * @see	location_service_state_changed_cb()
 */
int location_manager_stop(location_manager_h manager);

/**
 * @brief Sets a rectangular boundary for a given location manager.
 * @param[in]   manager                 The location manager handle
 * @param[in]   top_left_latitude       The latitude of area's top left corner [-90.0 ~ 90.0] (degrees)
 * @param[in]   top_left_longitude      The longitude of area's top left corner [-180.0 ~ 180.0] (degrees)
 * @param[in]   bottom_right_latitude   The latitude of area's bottom right corner [-90.0 ~ 90.0] (degrees)
 * @param[in]   bottom_right_longitude  The longitude of area's bottom right corner [-180.0 ~ 180.0] (degrees)
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #LOCATIONS_ERROR_OUT_OF_MEMORY Out of memory
 * @post It invokes location_manager_set_zone_changed_cb() when a boundary is entered or exited, if you set a callback with location_manager_set_zone_changed_cb().
 * @see location_manager_set_boundary_circle()
 * @see location_manager_set_zone_changed_cb()
 * @see location_manager_is_boundary_contains_coordinate()
 */
int location_manager_set_boundary_rect(location_manager_h manager, double top_left_latitude, double top_left_longitude, double bottom_right_latitude, double bottom_right_longitude);

/**
 * @brief Sets a circular boundary for a given location manager.
 * @param[in]   manager             The location manager handle
 * @param[in]   center_latitude     The latitude of circle's center [-90.0 ~ 90.0] (degrees)
 * @param[in]   center_longitude    The longitude of circle's center [-180.0 ~ 180.0] (degrees)
 * @param[in]   radius              The radius of a circle (meters)
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #LOCATIONS_ERROR_OUT_OF_MEMORY Out of memory
 * @post It invokes location_manager_set_zone_changed_cb() when a boundary is entered or exited, if you set a callback with location_manager_set_zone_changed_cb().
 * @see location_manager_set_boundary_rect()
 * @see location_manager_set_zone_changed_cb()
 * @see location_manager_is_boundary_contains_coordinate()
 */
int location_manager_set_boundary_circle(location_manager_h manager, double center_latitude, double center_longitude, double radius);

/**
 * @brief Check if the boundary contains the specified latitude and longitude.
 * @param[in]   manager  The location manager handle
 * @param[in]   latitude    The latitude to test against boundary [-90.0 ~ 90.0] (degrees)
 * @param[in]   longitude  The longitude to test against boundary [-180.0 ~ 180.0] (degrees)
 * @param[out]   contained  The result indicating whether the boundary contains the specified coordinate (@c true = contained, @c false = not contained )
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #LOCATIONS_ERROR_OUT_OF_MEMORY Out of memory
 * @see location_manager_set_boundary_rect()
 * @see location_manager_set_boundary_circle()
 */
int location_manager_is_boundary_contains_coordinate(location_manager_h manager, double latitude, double longitude, bool *contained);

/**
 * @brief Gets the given location manager's method.
 *
 * @param[in]   manager The location manager handle
 * @param[out]  method  The location method
 * @return 0 on success, otherwise a negative error value.
 * @retval  #LOCATIONS_ERROR_NONE                Successful
 * @retval  #LOCATIONS_ERROR_INVALID_PARAMETER   Invalid parameter
 * @see location_manager_create()
 */
int location_manager_get_method(location_manager_h manager, location_method_e *method);

/**
 * @brief Gets the current position information.
 * @details
 * The result is current altitude, latitude, and longitude, with a measurement timestamp.
 *
 * If @a altitude is negative, only altitude and latitude are available (fix status is 2D).
 * If @a altitude is positive, fix status is 3D and returned altitude value is the result of measurement.
 *
 * @param[in]   manager     The location manager handle
 * @param[out]  altitude    The current altitude (meters)
 * @param[out]  latitude    The current latitude [-90.0 ~ 90.0] (degrees)
 * @param[out]  longitude   The current longitude [-180.0 ~ 180.0] (degrees)
 * @param[out]  timestamp   The timestamp (time when measurement took place)
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid argument
 * @retval #LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE Service not available
 * @retval #LOCATIONS_ERROR_GPS_SETTING_OFF GPS is not enabled
 * @pre The location service state must be #LOCATIONS_SERVICE_ENABLED with location_manager_start() 
 */
int location_manager_get_position(location_manager_h manager, double *altitude, double *latitude, double *longitude, time_t *timestamp);

/**
 * @brief Gets the current velocity information.
 * @details
 * The result is current climb, direction, and speed, with a measurement timestamp.
 *
 * @param[in]   manager     The location manager handle
 * @param[out]  climb       The climb (km/h)
 * @param[out]  direction   The direction, degrees from the north
 * @param[out]  speed       The speed (km/h)
 * @param[out]  timestamp   The timestamp (time when measurement took place)
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid argument
 * @retval #LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE Service not available
 * @retval #LOCATIONS_ERROR_GPS_SETTING_OFF GPS is not enabled
 * @pre The location service state must be #LOCATIONS_SERVICE_ENABLED with location_manager_start() 
 */
int location_manager_get_velocity(location_manager_h manager, int *climb, int *direction, int *speed, time_t *timestamp);

/**
 * @brief Gets the current accuracy information.
 * @param[in]   manager The location manager handle
 * @param[out]  level The accuracy level
 * @param[out]  horizontal The horizontal accuracy (meters)
 * @param[out]  vertical The vertical accuracy (meters)
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid argument
 * @retval #LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE Service not available
 * @retval #LOCATIONS_ERROR_GPS_SETTING_OFF GPS is not enabled
 * @pre The location service state must be #LOCATIONS_SERVICE_ENABLED with location_manager_start() 
 */
int location_manager_get_accuracy(location_manager_h manager, location_accuracy_level_e *level, double *horizontal, double *vertical);

/**
 * @brief Gets the last known position information which is recorded.
 * @details
 * The @altitude, @latitude, @longitude, and @timestamp values should be 0, if there is no record of any previous position information.
 * @param[in]   manager     The location manager handle
 * @param[out]  altitude    The last known altitude (meters)
 * @param[out]  latitude    The last known latitude [-90.0 ~ 90.0] (degrees)
 * @param[out]  longitude   The last known longitude [-180.0 ~ 180.0] (degrees)
 * @param[out]  timestamp   The timestamp (time when measurement took place)
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid argument
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid argument
 * @pre The location manager handle must be created by location_manager_create() 
 */
int location_manager_get_last_known_position(location_manager_h manager, double *altitude, double *latitude, double *longitude, time_t *timestamp);

/**
 * @brief Registers a callback function to be invoked every 1 second with updated position information.
 *
 * @param[in]   manager     The location manager handle
 * @param[in]   callback    The callback function to register
 * @param[in]   interval   The interval [1 ~ 120] (seconds)
 * @param[in]   user_data   The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval  #LOCATIONS_ERROR_NONE               Successful
 * @retval  #LOCATIONS_ERROR_INVALID_PARAMETER  Invalid parameter
 * @post  location_position_updated_cb() will be invoked
 * @see location_manager_unset_position_updated_cb()
 * @see location_position_updated_cb()
 */
int location_manager_set_position_updated_cb(location_manager_h manager, location_position_updated_cb callback,  int interval, void *user_data);

/**
 * @brief	Unregisters the callback function.
 *
 * @param[in]   manager The location manager handle
 * @return  0 on success, otherwise a negative error value.
 * @retval  #LOCATIONS_ERROR_NONE               Successful
 * @retval  #LOCATIONS_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see location_manager_set_position_updated_cb()
 */
int location_manager_unset_position_updated_cb(location_manager_h manager);

/**
 * @brief Registers a callback function to be invoked every 1 second with updated velocity information.
 *
 * @param[in]   manager     The location manager handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval  #LOCATIONS_ERROR_NONE               Successful
 * @retval  #LOCATIONS_ERROR_INVALID_PARAMETER  Invalid parameter
 * @post  location_velocity_updated_cb() will be invoked
 * @see location_manager_unset_velocity_updated_cb()
 * @see location_velocity_updated_cb()
 */
int location_manager_set_velocity_updated_cb(location_manager_h manager, location_velocity_updated_cb callback, void *user_data);

/**
 * @brief	Unregisters the callback function.
 *
 * @param[in]   manager The location manager handle
 * @return  0 on success, otherwise a negative error value.
 * @retval  #LOCATIONS_ERROR_NONE               Successful
 * @retval  #LOCATIONS_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see location_manager_set_velocity_updated_cb()
 */
int location_manager_unset_velocity_updated_cb(location_manager_h manager);

/**
 * @brief Registers a callback function to be invoked when the  location service state is changed.
 *
 * @param[in]   manager     The location manager handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #LOCATIONS_ERROR_NONE               Successful
 * @retval  #LOCATIONS_ERROR_INVALID_PARAMETER  Invalid parameter
 * @post  location_service_state_changed_cb() will be invoked
 * @see location_manager_unset_service_state_changed_cb()
 * @see location_service_state_changed_cb()
 * @see location_manager_start()
 * @see location_manager_stop()
 * @see #location_service_state_e
*/
int location_manager_set_service_state_changed_cb(location_manager_h manager, location_service_state_changed_cb callback, void *user_data);

/**
 * @brief	Unregisters the callback function.
 * @param[in]	manager The location manager handle
 * @return  0 on success, otherwise a negative error value.
 * @retval  #LOCATIONS_ERROR_NONE               Successful
 * @retval  #LOCATIONS_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see location_manager_set_service_state_changed_cb()
 */
int location_manager_unset_service_state_changed_cb(location_manager_h manager);

/**
 * @brief Registers a callback function to be invoked when the previously set boundary area is entered or left.
 *
 * @param[in]   manager     The location manager handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #LOCATIONS_ERROR_NONE               Successful
 * @retval  #LOCATIONS_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre Either location_manager_set_boundary_rect() or location_manager_set_boundary_circle() is called before.
 * @post  location_zone_changed_cb() will be invoked
 * @see location_manager_unset_zone_changed_cb()
 * @see location_zone_changed_cb()
 */
int location_manager_set_zone_changed_cb(location_manager_h manager, location_zone_changed_cb callback, void *user_data);

/**
 * @brief	Unregisters the callback function.
 * @param[in]	manager	The location manager handle
 * @return 0 on success, otherwise a negative error value.
 * @retval  #LOCATIONS_ERROR_NONE	Successful
 * @retval  #LOCATIONS_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see location_manager_set_zone_changed_cb()
 */
int location_manager_unset_zone_changed_cb(location_manager_h manager);
/**
 * @}
 */

/*
 * GPS Status & Satellites
 */

/**
 * @addtogroup CAPI_LOCATION_GPS_STATUS_MODULE
 * @{
 */

/**
 * @brief  Called once for each satellite in range.
 * @param[in] azimuth	The azimuth of the satellite (degrees)
 * @param[in] elevation The elevation of the satellite (meters)
 * @param[in] prn	The PRN of the satellite
 * @param[in] snr	The SNR of the satellite [dB]
 * @param[in] is_active The flag signaling if satellite is in use
 * @param[in] user_data  The user data passed from the foreach function
 * @return @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @pre gps_status_foreach_satellites_in_view() will invoke this callback.
 * @see gps_status_foreach_satellites_in_view()
 */
typedef bool(*gps_status_get_satellites_cb)(unsigned int azimuth, unsigned int elevation, unsigned int prn, int snr, bool is_active, void *user_data);

/**
 * @brief Gets the GPS NMEA data.
 *
 * @remarks
 * This call is valid only for location managers with #LOCATIONS_METHOD_GPS method.\n
 * @a nmea must be released with @c free() by you.
 *
 * @param[in]	manager The location manager handle
 * @param[out]	nmea	The NMEA data
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid argument
 * @retval #LOCATIONS_ERROR_INCORRECT_METHOD Incorrect method
 * @retval #LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE Service not available
 * @retval #LOCATIONS_ERROR_OUT_OF_MEMORY Out of memory
 * @pre The location service state must be #LOCATIONS_SERVICE_ENABLED with location_manager_start() 
 * @see location_manager_start()
 */
int gps_status_get_nmea(location_manager_h manager, char **nmea);

/**
 * @brief Gets the number of satellites in view.
 *
 * @remarks
 * This call is valid only for location managers with #LOCATIONS_METHOD_GPS method.
 *
 * @param[in]   manager The location manager handle
 * @param[out]  count   The number of satellites in view
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid argument
 * @retval #LOCATIONS_ERROR_INCORRECT_METHOD Incorrect method
 * @retval #LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE Service not available
 * @pre The location service state must be #LOCATIONS_SERVICE_ENABLED with location_manager_start() 
 * @see   gps_status_foreach_satellites_in_view()
 */
int  gps_status_get_satellite_count_in_view(location_manager_h manager, int *count);

/**
 * @brief Invokes the callback function for each satellite.
 *
 * @remarks
 * This function is valid only for location managers with the #LOCATIONS_METHOD_GPS method.
 *
 * @param[in]   manager     The location manager handle
 * @param[in]   callback    The iteration callback function
 * @param[in]   user_data   The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid argument
 * @retval #LOCATIONS_ERROR_INCORRECT_METHOD Incorrect method
 * @retval #LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE Service not available
 * @pre The location service state must be #LOCATIONS_SERVICE_ENABLED with location_manager_start() 
 * @post  It invokes gps_status_get_satellites_cb().
 * @see   gps_status_get_satellite_count_in_view()
 * @see   gps_status_get_satellites_cb()
 */
int  gps_status_foreach_satellites_in_view (location_manager_h manager, gps_status_get_satellites_cb callback, void *user_data);

/**
 * @brief Gets the number of satellites available to be used.
 *
 * @remarks
 * This call is valid only for location managers with #LOCATIONS_METHOD_GPS method.
 *
 * @param[in]   manager The location manager handle
 * @param[out]  count   The number of active satellites
 * @return 0 on success, otherwise a negative error value.
 * @retval #LOCATIONS_ERROR_NONE Successful
 * @retval #LOCATIONS_ERROR_INVALID_PARAMETER Invalid argument
 * @retval #LOCATIONS_ERROR_INCORRECT_METHOD Incorrect method
 * @retval #LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE Service not available
 * @pre The location service state must be #LOCATIONS_SERVICE_ENABLED with location_manager_start() 
 * @see   gps_status_get_satellite_count_in_view()
 */
int  gps_status_get_active_satellite_count(location_manager_h manager, int *count);
/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_LOCATION_LOCATIONS_H__ */
