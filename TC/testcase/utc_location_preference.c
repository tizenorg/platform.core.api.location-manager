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
#include <location_preference.h>
#include <geocoder.h>

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

static void startup(void);
static void cleanup(void);

void (*tet_startup) (void) = startup;
void (*tet_cleanup) (void) = cleanup;

static void utc_location_location_preference_foreach_available_property_keys_p(void);
static void utc_location_location_preference_foreach_available_property_keys_n(void);
static void utc_location_location_preference_foreach_available_property_values_p(void);
static void utc_location_location_preference_foreach_available_property_values_n(void);
static void utc_location_location_preference_foreach_available_languages_p(void);
static void utc_location_location_preference_foreach_available_languages_n(void);
static void utc_location_location_preference_foreach_properties_p(void);
static void utc_location_location_preference_foreach_properties_n(void);
static void utc_location_location_preference_set_p(void);
static void utc_location_location_preference_set_n(void);
static void utc_location_location_preference_get_p(void);
static void utc_location_location_preference_get_n(void);
static void utc_location_location_preference_get_provider_name_p(void);
static void utc_location_location_preference_get_provider_name_n(void);
static void utc_location_location_preference_get_distance_unit_p(void);
static void utc_location_location_preference_get_distance_unit_n(void);
static void utc_location_location_preference_set_distance_unit_p(void);
static void utc_location_location_preference_set_distance_unit_n(void);
static void utc_location_location_preference_get_language_p(void);
static void utc_location_location_preference_get_language_n(void);
static void utc_location_location_preference_set_language_p(void);
static void utc_location_location_preference_set_language_n(void);

struct tet_testlist tet_testlist[] = {
//    { utc_location_location_preference_foreach_available_property_keys_p, POSITIVE_TC_IDX },
	{utc_location_location_preference_foreach_available_property_keys_n, NEGATIVE_TC_IDX},
//    { utc_location_location_preference_foreach_available_property_values_p, POSITIVE_TC_IDX },
	{utc_location_location_preference_foreach_available_property_values_n, NEGATIVE_TC_IDX},
	{utc_location_location_preference_foreach_available_languages_p, POSITIVE_TC_IDX},
	{utc_location_location_preference_foreach_available_languages_n, NEGATIVE_TC_IDX},
	{utc_location_location_preference_set_p, POSITIVE_TC_IDX},
	{utc_location_location_preference_set_n, NEGATIVE_TC_IDX},
	{utc_location_location_preference_foreach_properties_p, POSITIVE_TC_IDX},
	{utc_location_location_preference_foreach_properties_n, NEGATIVE_TC_IDX},
	{utc_location_location_preference_get_p, POSITIVE_TC_IDX},
	{utc_location_location_preference_get_n, NEGATIVE_TC_IDX},
	{utc_location_location_preference_get_provider_name_p, POSITIVE_TC_IDX},
	{utc_location_location_preference_get_provider_name_n, NEGATIVE_TC_IDX},
	{utc_location_location_preference_set_distance_unit_p, POSITIVE_TC_IDX},
	{utc_location_location_preference_set_distance_unit_n, NEGATIVE_TC_IDX},
	{utc_location_location_preference_get_distance_unit_p, POSITIVE_TC_IDX},
	{utc_location_location_preference_get_distance_unit_n, NEGATIVE_TC_IDX},
	{utc_location_location_preference_set_language_p, POSITIVE_TC_IDX},
	{utc_location_location_preference_set_language_n, NEGATIVE_TC_IDX},
	{utc_location_location_preference_get_language_p, POSITIVE_TC_IDX},
	{utc_location_location_preference_get_language_n, NEGATIVE_TC_IDX},
	{NULL, 0},
};

static geocoder_h geocoder;
static char *available_language;
static char *available_key;
static char *available_value;

static void startup(void)
{
	g_setenv("PKG_NAME", "com.samsung.capi-location-preference", 1);
	g_setenv("LOCATION_TEST_ENABLE", "1", 1);

	tet_printf("TC start");

	int ret = geocoder_create(&geocoder);
	available_language = NULL;
	available_key = NULL;
	available_value = NULL;
	if (ret != GEOCODER_ERROR_NONE) {
		tet_printf("Creating the handle of geocoder failed");
		return;
	} else {
		tet_printf("Creating the handle of geocoder succeeded");
	}
}

static void cleanup(void)
{
	geocoder_destroy(geocoder);
}

bool location_preference_available_property_key_cb_impl(const char *key, void *user_data)
{
	tet_printf("key : %s", key);
	available_key = strdup(key);
	return false;
}

bool location_preference_available_property_value_cb_impl(const char *value, void *user_data)
{
	tet_printf("value : %s", value);
	available_value = strdup(value);
	return false;
}

bool location_preference_available_language_cb_impl(const char *language, void *user_data)
{
	available_language = strdup(language);
	tet_printf("available language : %s", available_language);
	return false;
}

bool location_preference_property_cb_impl(const char *key, const char *value, void *user_data)
{
	tet_printf("key : %s", key);
	tet_printf("value : %s", value);
	return false;
}

static void utc_location_location_preference_foreach_available_property_keys_p(void)
{
	int ret = location_preference_foreach_available_property_keys(GET_LOCATION_SERVICE(geocoder),
								      location_preference_available_property_key_cb_impl, NULL);
	if (ret == LOCATION_PREFERENCE_ERROR_NONE) {
		dts_pass(__func__, "location_preference_foreach_available_property_keys passed");
	} else {
		dts_fail(__func__, "location_preference_foreach_available_property_keys failed");
	}
}

static void utc_location_location_preference_foreach_available_property_keys_n(void)
{
	int ret = location_preference_foreach_available_property_keys(GET_LOCATION_SERVICE(geocoder), NULL, NULL);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER,
		     "LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER was not returned.");
}

static void utc_location_location_preference_foreach_available_property_values_p(void)
{
	int ret = location_preference_foreach_available_property_values(GET_LOCATION_SERVICE(geocoder), available_key,
									location_preference_available_property_value_cb_impl,
									NULL);
	if (ret == LOCATION_PREFERENCE_ERROR_NONE) {
		dts_pass(__func__, "location_preference_foreach_available_property_values passed");
	} else {
		dts_fail(__func__, "location_preference_foreach_available_property_values failed");
	}
}

static void utc_location_location_preference_foreach_available_property_values_n(void)
{
	int ret = location_preference_foreach_available_property_values(GET_LOCATION_SERVICE(geocoder), NULL, NULL, NULL);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER,
		     "LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER was not returned.");
}

static void utc_location_location_preference_foreach_available_languages_p(void)
{
	int ret = location_preference_foreach_available_languages(GET_LOCATION_SERVICE(geocoder),
								  location_preference_available_language_cb_impl, NULL);
	if (ret == LOCATION_PREFERENCE_ERROR_NONE) {
		dts_pass(__func__, "location_preference_foreach_available_languages passed");
	} else {
		dts_fail(__func__, "location_preference_foreach_available_languages failed");
	}
}

static void utc_location_location_preference_foreach_available_languages_n(void)
{
	int ret = location_preference_foreach_available_languages(GET_LOCATION_SERVICE(geocoder), NULL, NULL);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER,
		     "LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER was not returned.");
}

static void utc_location_location_preference_foreach_properties_p(void)
{
	int ret =
	    location_preference_foreach_properties(GET_LOCATION_SERVICE(geocoder), location_preference_property_cb_impl, NULL);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_NONE, "location_preference_foreach_properties failed.");
}

static void utc_location_location_preference_foreach_properties_n(void)
{
	int ret = location_preference_foreach_properties(GET_LOCATION_SERVICE(geocoder), NULL, NULL);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER,
		     "LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER was not returned.");
}

static void utc_location_location_preference_set_p(void)
{
	if (available_key == NULL) {
		available_key = strdup("test_key");
		available_value = strdup("test_value");
	}
	int ret = location_preference_set(GET_LOCATION_SERVICE(geocoder), available_key, available_value);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_NONE, "location_preference_set failed.");
}

static void utc_location_location_preference_set_n(void)
{
	int ret = location_preference_set(GET_LOCATION_SERVICE(geocoder), NULL, NULL);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER,
		     "LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER was not returned.");
}

static void utc_location_location_preference_get_p(void)
{
	int ret = 0;
	char *value = NULL;

	ret = location_preference_get(GET_LOCATION_SERVICE(geocoder), available_key, &value);
	if (value != NULL) {
		tet_printf("value: %s", value);
	}

	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_NONE, "location_preference_get failed.");
}

static void utc_location_location_preference_get_n(void)
{
	int ret = location_preference_get(GET_LOCATION_SERVICE(geocoder), NULL, NULL);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER,
		     "LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER was not returned.");
}

static void utc_location_location_preference_get_provider_name_p(void)
{
	int ret = 0;
	char *name = NULL;

	ret = location_preference_get_provider_name(GET_LOCATION_SERVICE(geocoder), &name);

	if (ret == LOCATION_PREFERENCE_ERROR_NONE) {
		if (name != NULL) {
			tet_printf("provider name: %s", name);
		}
		dts_pass(__func__, "location_preference_get_provider_name passed");
	} else
		dts_fail(__func__, "location_preference_get_provider_name failed");
}

static void utc_location_location_preference_get_provider_name_n(void)
{
	int ret = location_preference_get_provider_name(GET_LOCATION_SERVICE(geocoder), NULL);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER,
		     "LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER was not returned.");
}

static void utc_location_location_preference_set_distance_unit_p(void)
{
	int ret = location_preference_set_distance_unit(GET_LOCATION_SERVICE(geocoder), LOCATION_PREFERENCE_DISTANCE_UNIT_FT);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_NONE, "location_preference_set_distance_unit failed.");
}

static void utc_location_location_preference_set_distance_unit_n(void)
{
	int ret = location_preference_set_distance_unit(GET_LOCATION_SERVICE(geocoder), -1);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER,
		     "LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER was not returned.");
}

static void utc_location_location_preference_get_distance_unit_p(void)
{
	int ret = 0;
	location_preference_distance_unit_e unit = LOCATION_PREFERENCE_DISTANCE_UNIT_FT;

	ret = location_preference_get_distance_unit(GET_LOCATION_SERVICE(geocoder), &unit);
	if (ret == LOCATION_PREFERENCE_ERROR_NONE) {
		dts_pass(__func__, "location_preference_get_distance_unit passed");
	} else {
		dts_fail(__func__, "location_preference_get_distance_unit failed");
	}
}

static void utc_location_location_preference_get_distance_unit_n(void)
{
	int ret = location_preference_get_distance_unit(GET_LOCATION_SERVICE(geocoder), NULL);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER,
		     "LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER was not returned.");
}

static void utc_location_location_preference_set_language_p(void)
{
	if (available_language == NULL) {
		available_language = strdup("KR");
	}
	int ret = location_preference_set_language(GET_LOCATION_SERVICE(geocoder), available_language);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_NONE, "location_preference_set_language_unit failed.");
}

static void utc_location_location_preference_set_language_n(void)
{
	int ret = location_preference_set_language(GET_LOCATION_SERVICE(geocoder), NULL);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER,
		     "LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER was not returned.");
}

static void utc_location_location_preference_get_language_p(void)
{
	int ret = 0;
	char *language = NULL;

	ret = location_preference_get_language(GET_LOCATION_SERVICE(geocoder), &language);
	if (ret == LOCATION_PREFERENCE_ERROR_NONE) {
		dts_pass(__func__, "location_preference_get_distance_unit passed");
	} else {
		dts_fail(__func__, "location_preference_get_distance_unit failed");
	}
}

static void utc_location_location_preference_get_language_n(void)
{
	int ret = location_preference_get_language(GET_LOCATION_SERVICE(geocoder), NULL);
	dts_check_eq(__func__, ret, LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER,
		     "LOCATION_PREFERENCE_ERROR_INVALID_PARAMETER was not returned.");
}
