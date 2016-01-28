/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd All Rights Reserved
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

#ifndef LOCATION_LOCATION_MANAGER_H_
#define LOCATION_LOCATION_MANAGER_H_

namespace location {

enum LocationProvider {
	PROVIDER_HYBRID = 0,
	PROVIDER_GPS,
	PROVIDER_WPS,
	PROVIDER_MOCK
};

class LocationManager {
	public:
		void setLocationProvider(LocationProvider provider);
		void addLocationListener(int interval); // xx_set_updated_cb
		void addDistanceListener(int interval, double distance);
		void addSatelliteListener(int interval);
		void removeLocationListener();
		void removeDistanceListener();
		void removeGpsListener(GpsListener type);

		Location requestSingleUpdate();
		Location requestLocationUpdates();
		void removeLocationUpdates();

		Location getLocation();
		Location getLastKnownLocation();
		LocationProvider getLocationProvider();

		bool isMethodSupported(LocationProvider provider);
		bool isMethodEnabled(LocationProvider provider);

	private:
		LocationManager();
		virtual ~LocationManager();

		location_manager_h handle;
		Location location;
};

class Location
{
	public:
		double getLatitude();
		double getLongitude();
		double getAltitude();
		double getSpeed();
		double getDirection();
		double getAccuracy();
		double getTimestamp();

	private :
		double altitude, latitude, longitude;
		double speed, direction, accuracy;
		double timestamp;
};

class Gps {
	public:
		int getActiveSize();
		int getInviewSize();
		std::list<Satellite> getSatellitesList();
	private:
		int active, inview;
}

class Satellite {
	public :
		int getAzimuth();
		int getElevation();
		int getPrn();
		int getSnr();
		bool getIsActive();
	private :
		int azimuth, elevation, prn, snr;
		bool is_active;
}

}  // namespace

#endif  // LOCATION_LOCATION_MANAGER_H_

