#include "MyWeather.h"
#include "details.h"
#include "MyJson.h"

#include <iostream>
#include <iomanip>

MyWeather::~MyWeather()
{
}

int MyWeather::current_weather()
{
	get_json_data();

	return 0;
}

int MyWeather::get_json_data()
{
	std::string parameters = "";
	Details details;
	std::string url = "https://api.openweathermap.org/data/2.5/weather?";
	if (!_city_name.empty())
	{
		parameters.append("q=");
		parameters.append(_city_name);
		parameters.append(",USA");
	}
	else if (_zipcode > 9999 && _zipcode < 100000)
	{
		parameters.append("zip=");
		parameters.append(std::to_string(_zipcode));
		parameters.append(",USA");
	}

	parameters.append("&APPID=");
	parameters.append(details.get_appID());

	url.append(parameters);
	
	client.set_url(url);
	client.set_detailed_flag(true);
	client.POST_request();
	client.check_error_codes();
	client.finish();

	parse_json();

	return 0;
}

int MyWeather::parse_json()
{
	MyJson json;

	json.parse(std::move(client.get_http_data()));
	
	_temperature = kelvin_to_fahrenheit(json.get_field("main", "temp").asDouble());
	_pressure = json.get_field("main", "pressure").asDouble();
	_humidty_percentage = json.get_field("main", "humidity").asDouble();
	_minumum_temperature = kelvin_to_fahrenheit(json.get_field("main", "temp_min").asDouble());
	_maximum_temperature = kelvin_to_fahrenheit(json.get_field("main", "temp_max").asDouble());
	_wind_speed = json.get_field("wind", "speed").asDouble();
	_wind_direction = json.get_field("wind", "deg").asDouble();

	return 0;
}

void MyWeather::print_all()
{
	std::cout << std::fixed << std::setprecision(2) <<
		"Temperature: " << kelvin_to_fahrenheit(_temperature) << "\n"
		"Humidty: " << _humidty_percentage << "%\n"
		"Pressure: " << _pressure << "\n"
		"Maximum temperature: " << kelvin_to_fahrenheit(_maximum_temperature) << "\n"
		"Minumum temperature: " << kelvin_to_fahrenheit(_minumum_temperature) << "\n"
		"Wind Speed: " << _wind_speed << "\n"
		"Wind Direction: " << _wind_direction << std::endl;
}

double MyWeather::kelvin_to_fahrenheit(double k)
{
	return (9.0/5.0) * k - 459.67;
}

int MyWeather::display_details(bool flag)
{
	client.set_detailed_flag(flag);

	return 0;
}