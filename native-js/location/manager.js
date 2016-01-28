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
 * See the [Location.Manager](../classes/Location.Manager.html) class description.
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
locationService.createLocationManager('hybrid')
   .then(function (manager) {
     console.log("Got the location manager...");
     return manager.start();
   })
   .then(function (manager) {
     return manager.getLocation();
   })
   .then(function (location) {
     console.log("Current location is " + location.latitude + " " + location.longitude);
   });
```
 * @class Location
 * @public
 */

/**
 * Returns true if given location method is supported, else returns false.
 * @method isMethodSupported
 * @param {String} method
 * @value 'none' undefined method.
 * @value 'hybrid' this method selects the best method available at the moment.
 * @value 'gps' this method uses global positioning system.
 * @value 'wps' this method uses wifi positioning system.
 * @value 'mock' this method uses mock location.
 * @return {Boolean}
 * @throws
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation.
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text.
 * @since 3.0
 */

/**
 * Returns true if the given methods is currently enabled, else returns false.
 * @method isMethodEnabled
 * @param {String} method
 * @value 'none' undefined method
 * @value 'hybrid' this method selects the best method available at the moment
 * @value 'gps' this method uses global positioning system
 * @value 'wps' this method uses wifi positioning system
 * @value 'mock' this method uses mock location.
 *
 * @return {Boolean}
 * @throws
 *  * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation.
 *  * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text.
 * @since 3.0
 */


/**
 * Returns asynchronously the [Location.Manager](Location.Manager.html) object for the selected method
 *
 * factory function is used to prevent creating two separate instances for a single method.
 *
 * @method createLocationManager
 * @param {String} method
 * @value 'none' undefined method.
 * @value 'hybrid' this method selects the best method available at the moment.
 * @value 'gps' this method uses global positioning system.
 * @value 'wps' this method uses wifi positioning system and cell.
 * @value 'mock' this method uses mock location.
 *
 * @return {Promise|Location.Manager}
 * @throws
 * * OutOfMemoryError - not enough operational memory to perform the operation.
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text.
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error.
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation.
 * @since 3.0
 */

/**
 * Manager object is returned by [Location.createLocationManager](../classes/Location.html#method_createLocationManager)
 * @class Manager
 * @namespace Location
 * @extends Node.EventEmitter
 */
/**
 * A flag indicating whether the service is started.
 * @attribute started
 * @type Boolean
 * @readOnly
 */

/**
 * Requests enabling the location service
 * @method start
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Manager} The promise is resolved to this manager object itself (for easier chaining).
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error
 * * NetworkError - network related issues, e.g. timeout, connection is rejected
 * * InvalidStateError - operation cannot be performed in current state, e.g. preconditions are not met, file is locked or busy
 * * NotPermittedError - operation is not permitted
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation
 *
 * @since 3.0
 */

/**
 * Requests disabling the location service
 * @method stop
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error
 * * NetworkError - network related issues, e.g. timeout, connection is rejected
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation
 * 
 * @since 3.0
 */

/**
 * Enables mock location.
 * @method enableMockLocation
 * @param {Boolean} enable or disable
 * @value 'true' enable
 * @value 'false' disable

 * @return {Promise|Location.Manager}
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text.
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error.
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation.
 * @since 3.0
 */

/**
 * Sets mock location.
 * @method setMockLocation
 * @param {Location.Location} location

 * @return {Promise|Location.Manager}
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text.
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error.
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation.
 * @since 3.0
 */

/**
 * Clear mock location.
 * @method clearMockLocation

 * @return {Promise|Location.Manager}
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text.
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error.
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation.
 * @since 3.0
 */

/**
 * Adds listener.
 * @method addListener
 * @extends Node.EventEmitter
 * @param {String} eventName
 * @param {Function} listener

 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text.
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error.
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation.
 * @since 3.0
 */

/**
 * Removes listener.
 * @method  removeListener
 * @extends Node.EventEmitter
 * @param {String} eventName
 * @param {Function} listener

 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text.
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error.
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation.
 * @since 3.0
 */

/**
 * Removes all listeners.
 * @method  removeAllListener
 * @extends Node.EventEmitter
 * @param {String} eventName

 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text.
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error.
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation.
 * @since 3.0
 */

/**
 * Addes GPS status listener.
 * @method AddGpsStusListener
 * @privilege http://tizen.org/privilege/location

 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text.
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error.
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation.
 * @since 3.0
 */

/**
 *  GPS status listener.
 * @method AddGpsStusListener
 * @privilege http://tizen.org/privilege/location

 * @return {Promise|Location.GpsStatus}
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text.
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error.
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation.
 * @since 3.0
 */

/**
 * @method getGpsStatus
 * @privilege http://tizen.org/privilege/location

 * @return {Promise|Location.GpsStatus} The promise is resolved to this manager object itself (for easier chaining).
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error
 * * NetworkError - network related issues, e.g. timeout, connection is rejected
 * * InvalidStateError - operation cannot be performed in current state, e.g. preconditions are not met, file is locked or busy
 * * NotPermittedError - operation is not permitted
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation
 *
 * @since 3.0
 */




 * @return {Promise|Location.GpsStatus} The promise is resolved to this manager object itself (for easier chaining).
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error
 * * NetworkError - network related issues, e.g. timeout, connection is rejected
 * * InvalidStateError - operation cannot be performed in current state, e.g. preconditions are not met, file is locked or busy
 * * NotPermittedError - operation is not permitted
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation
 *
 * @since 3.0
 */

/**
 * Location boundaries attached to the manager
 * @attribute boundaries
 * @readOnly
 * @type {Location.Boundary[]}
 */

/**
 * Adds item to the boundaries array
 * @method addBoundary
 * @param {Location.Boundary} boundary
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text
 * * OutOfMemoryError - not enough operational memory to perform the operation
 * * NotPermittedError - operation is not permitted
 *
 * @since 3.0
 */

/**
 * Removes item from the boundaries array
 * @method removeBoundary
 * @param {Location.Boundary} boundary
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text
 * * OutOfMemoryError - not enough operational memory to perform the operation
 * * NotPermittedError - operation is not permitted
 *
 * @since 3.0
 */

/**
 * Retrieves the current location [Location.Location](Location.Location.html)
 * @method getLocation
 * @privilege http://tizen.org/privilege/location
 * @return {Promise|Location.Location}
 * @since 3.0
 */

/**
 * Returns the last recorded location
 * @method getLastLocation
 * @privilege http://tizen.org/privilege/location
 * @return {Location.Location}
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error
 * * InvalidStateError - operation cannot be performed in current state, e.g. preconditions are not met, file is locked or busy
 * * NotPermittedError - operation is not permitted
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation
 *
 * @since 3.0
 */

/**
 * Fired when location service has enabled or disabled by user(Settings)
 * @event setting
 * @param {setting} location
 *  * 'disabled' - service is disabled
 *  * 'enabled' - service is enabled
 */

/**
 * Fired when service status has changed
 * @event status
 * @param {short} status
 */

/**
 * Fired when location has changed
 * @event location
 * @param {Location.Location} location
 */

/**
 * Fired when any of the set boundaries is entered or left.
 * @event zone
 * @param {Object} event
 * @param {state} state
 *  * 'in' - the currnet location is inside of boundaries
 *  * 'out' - the current location is outside of boundaries
 * @param {Location.Boundary} event.boundary
 */

/**
 * Location.Boundary is a base class for {{#crossLink "Location.RectangleBoundary}}{{/crossLink}}, {{#crossLink "Location.CircleBoundary}}{{/crossLink}}, {{#crossLink "Location.PolygonBoundary}}{{/crossLink}}. 
 * Based on [location_bounds_h](https://developer.tizen.org/dev-guide/2.4/org.tizen.native.mobile.apireference/group__CAPI__LOCATION__BOUNDS__MODULE.html)
 * @class Boundary
 * @namespace Location
 * @extends Node.EventEmitter
 */

/**
 * @method contains
 * @param {Location.Coordinates} location
 * @return {Boolean} true if points lays inside of the boundary
 */

/**
 * @event state
 * @param {Boolean} if the location is inside of boundary.
 */

/**
 * Constructor is available as {{#crossLink "Location.Manager/RectangleBoundary:attribute"}}{{/crossLink}}.
 * @class RectangleBoundary
 * @extends Location.Boundary
 * @namespace Location
 * @constructor
 * @param {Location.Coordinates} topLeft
 * @param {Location.Coordinates} bottomRight
 */
/**
 * @attribute topLeft
 * @type Location.Coordinates
 * @readOnly
 */
/**
 * @attribute bottomRight
 * @type Location.Coordinates
 * @readOnly
 */

/**
 * Constructor is available as {{#crossLink "Location.Manager/CircleBoundary:attribute"}}{{/crossLink}}.
 * @class CircleBoundary
 * @extends Location.Boundary
 * @namespace Location
 * @constructor
 * @param {Location.Coordinates} center The center of the circle
 * @param {Number} radius The radius of the circle (meters)
 */
/**
 * @attribute center
 * @type Location.Coordinates
 * @readOnly
 */
/**
 * @attribute radius
 * @type Number
 * @readOnly
 */

/**
 * Constructor is available as {{#crossLink "Location.Manager/PolygonBoundary:attribute"}}{{/crossLink}}.
 * @class PolygonBoundary
 * @extends Location.Boundary
 * @namespace Location
 * @constructor
 * @param {Location.Coordinates[]} points Polygon verexes, at least 3
 * @throws
 */
/**
 * @attribute points
 * @type Location.Coordinates
 * @readOnly
 */

/**
 * Location object is returned by [Location.Manager.getLocation](../classes/Location.Manager.html#method_getLocation)
 * or [Location.Manager.getLastLocation](../classes/Location.Manager.html#method_getLastLocation) method.
 * @class Location
 * @namespace Location
 * @extends Location.Coordinates
 */
/**
 * The received time of the notification message.
 * @attribute timestamp
 * @type Date
 * @readOnly
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
 * Current speed (km/hour).
 *
 * @attribute speed
 * @type Number
 * @readOnly
 */

/**
 * Holds the difference between current direction and north (0*) represented in degrees.
 *
 * @attribute direction
 * @type Number
 * @readOnly
 */

/**
 * A horizontal accuracy represented in meters.
 *
 * @attribute horizontal
 * @type Number
 * @readOnly
 */

/**
 * A vertical accuracy represented in meters.
 *
 * @attribute vertical
 * @type Number
 * @readOnly
 */

/**
 * Location.Coordinates constructor is available in [Location.Coordinates](../classes/Location.Coordinates.html).
 * @class Coordinates
 * @namespace Location
 * @constructor
 * @param {Number} latitude
 * @param {Number} longitude
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
 * Calculates distance to the other coordinates
 * @method distance
 * @param {Location.Coordinates} destination
 * @return {Number} The calculated distance from this coordinates to the destination
 *
 * @since 3.0
 */


/**
 * Location.GpsSatellite is a base class for {{#crossLink "Location.GpsSatellite}}{{/crossLink}}, {{#crossLink "Location.GpsSatellite}}{{/crossLink}}, {{#crossLink "Location.GpsSatellite}}{{/crossLink}}. 
 * @class Satellite
 * @namespace Location
 * @extends Node.EventEmitter
 */

/**
 * @method getGpsSatelliteInView
 * @privilege http://tizen.org/privilege/location

 * @return {Promise|Location.GpsSatellite[]} The promise is resolved to this manager object itself (for easier chaining).
 * @throws
 * * InvalidValueError - given value is not acceptable, e.g. number out of range, wrong format of the string, forbidden character in the text
 * * ServiceError - system service related errors, e.g. D-Bus communication issue, database access error, remote service replied with an error
 * * NetworkError - network related issues, e.g. timeout, connection is rejected
 * * InvalidStateError - operation cannot be performed in current state, e.g. preconditions are not met, file is locked or busy
 * * NotPermittedError - operation is not permitted
 * * MissingFeatureError - the operation cannot be performed due to lack of feature support, remote device does not support requested operation
 *
 * @since 3.0
 */

/**
 * Location.GpsSatellite constructor is available in [Location.GpsStatus](../classes/Location.Coordinates.html).
 * @class GpsSatellite
 * @namespace Location
 * @constructor
 * @param {Number} azimuth
 * @param {Number} elevation
 * @param {Number} prn
 * @param {Number} snr
 * @param {Number} snr
 * @param {Number} usedInFix
 */
/**
 * @attribute azimuth
 * @type Number
 * @readOnly
 */
/**
 * @attribute elevation
 * @type Number
 * @readOnly
 */
/**
 * @attribute prn
 * @type Number
 * @readOnly
 */
/**
 * @attribute snr
 * @type Number
 * @readOnly
 */
/**
 * @attribute usedInFix
 * @type Boolean
 * @readOnly
 */


/**
 * Location.GpsStatus constructor is available in [Location.GpsStatus](../classes/Location.Coordinates.html).
 * @class GpsStatus
 * @namespace Location
 * @constructor
 * @param {Number} timestamp
 * @param {Number} numer_of_active
 * @param {Number} number_of_in_view
 */
/**
 * @attribute timestamp
 * @type Number
 * @readOnly
 */
/**
 * @attribute number_of_active
 * @type Number
 * @readOnly
 */
/**
 * @attribute number_of_in_view
 * @type Number
 * @readOnly
 */
