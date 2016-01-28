/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 * The Tizen Native JS Location Manager Module.
 *
 * See the [Location.LocationManager](../classes/Location.LocationManager.html) class description.
 *
``` javascript
var location = require('tizen-location');
```
 *
 * Module tizen-location exports an instance of [Location](../classes/Location.html) class.
 * @module tizen-location
 */

/**
 * The Location object is returned by [tizen-location](../modules/tizen-location.html) module.
 *
 * Using example:
``` javascript
var locationService = require('tizen-location');
locationService.addLocationListener(1)
   .then(function (manager) {
     console.log("Got the location manager...");
     return manager.requestLocationUpdates('hybrid');
   })
   .then(function (location) {
     console.log("Current latitude is " + location.getLatitude());
   });
```
 * @class LocationManager
 * @public
 * @namespace Location
 * @extends Node.EventEmitter
 */

// ---------------------------------------------------------------------
/**
 * @method setLocationProvider
 * @param {String} method
 * @value 'hybrid' this method selects the best method available at the moment.
 * @value 'gps' this method uses global positioning system.
 * @value 'wps' this method uses wifi positioning system.
 * @return {Boolean}
 * @since 3.0
 */

/**
 * @method addLocationListener
 * @param {Number} interval
 * @since 3.0
 */

/**
 * @method addDistanceListener
 * @param {Number} interval
 * @param {Number} distance
 * @since 3.0
 */

/**
 * @method addSatelliteListener
 * @param {Number} interval
 * @since 3.0
 */

/**
 * @method removeLocationListener
 * @since 3.0
 */

/**
 * @method removeDistanceListener
 * @since 3.0
 */

/**
 * @method removeGpsListener
 * @since 3.0
 */

/**
 * @method requestSingleUpdate
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location} The promise is resolved to this manager object itself (for easier chaining).
 * @since 3.0
 */

/**
 * @method requestLocationUpdates
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location} The promise is resolved to this manager object itself (for easier chaining).
 * @since 3.0
 */

/**
 * @method getLocation
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location}
 * @since 3.0
 */

/**
 * @method getLastKnownLocation
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location}
 * @since 3.0
 */

/**
 * @method getLocationProvider
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location} The promise is resolved to this manager object itself (for easier chaining).
 * @since 3.0
 */

/**
 * Returns true if given location method is supported, else returns false.
 * @method isMethodSupported
 * @param {String} method
 * @value 'hybrid' this method selects the best method available at the moment.
 * @value 'gps' this method uses global positioning system.
 * @value 'wps' this method uses wifi positioning system.
 * @value 'mock'
 * @return {Boolean}
 * @since 3.0
 */

/**
 * Returns true if the given methods is currently enabled, else returns false.
 * @method isMethodEnabled
 * @param {String} method
 * @value 'hybrid' this method selects the best method available at the moment
 * @value 'gps' this method uses global positioning system
 * @value 'wps' this method uses wifi positioning system
 * @value 'mock'
 * @return {Boolean}
 * @since 3.0
 */

// ----------------------------------------------------------------
/**
 * Location object is returned by [Location.LocationManager.getLocation](../classes/Location.LoationManager.html#method_getLocation)
 *  or [Location.LocationManager.getLocation](../classes/Location.LocationManager.html#method_getLocation) method.
 * @class Location
 * @namespace Location
 */

/**
 * @attribute latitude
 * @type Number
 * @readOnly
 */

/**
 * @attribute longitude
 * @type Number
 * @readOnly
 */

/**
 * @attribute altitude
 * @type Number
 * @readOnly
 */

/**
 * @attribute speed
 * @type Number
 * @readOnly
 */

/**
 * @attribute direction
 * @type Number
 * @readOnly
 */

/**
 * @attribute accuracy
 * @type Number
 * @readOnly
 */

/**
 * The received time of the notification message.
 * @attribute timestamp
 * @type Date
 * @readOnly
 */

/**
 * Retrieves location [Location.Location](Location.Location.html)
 * @method getLatitude
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location}
 * @since 3.0
 */

/**
 * Retrieves location [Location.Location](Location.Location.html)
 * @method getLongitude
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location}
 * @since 3.0
 */

/**
 * Retrieves location [Location.Location](Location.Location.html)
 * @method getAltitude
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location}
 * @since 3.0
 */

/**
 * Retrieves location [Location.Location](Location.Location.html)
 * @method getSpeed
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location}
 * @since 3.0
 */

/**
 * Retrieves location [Location.Location](Location.Location.html)
 * @method getDirection
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location}
 * @since 3.0
 */

/**
 * Retrieves location [Location.Location](Location.Location.html)
 * @method getAccuracy
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location}
 * @since 3.0
 */

/**
 * Retrieves location [Location.Location](Location.Location.html)
 * @method getTimestamp
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location}
 * @since 3.0
 */

