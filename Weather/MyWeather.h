#pragma once
#include <string>
#include "MyHttpClient.h"

class MyWeather
{
public:
	MyWeather(int zipcode) : _zipcode(zipcode), json_string_response("") {}
	MyWeather(const std::string& city) : _city_name(city), json_string_response("") {}
	~MyWeather();

	int current_weather();
	int display_details(bool);

	double get_temperature() const { return _temperature; }
	double get_pressure() const { return _pressure; }
	double get_humidity_percentage() const { return _humidty_percentage; }
	double get_minumum_temperature() const { return _minumum_temperature; }
	double get_maximum_temperature() const { return _maximum_temperature; }
	double get_wind_speed() const { return _wind_speed; }
	double get_wind_direction() const { return _wind_direction; }
	std::string get_response() { return json_string_response; }

	void print_all();
private:
	double _temperature;
	double _pressure;
	double _humidty_percentage;
	double _minumum_temperature;
	double _maximum_temperature;
	double _wind_speed;
	double _wind_direction;

	int get_json_data();
	int parse_json();
	double kelvin_to_fahrenheit(double);

	int _zipcode;
	std::string _city_name;
	std::string _country_code;
	std::string json_string_response;
	MyHttpClient client;
};

