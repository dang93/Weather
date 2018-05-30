#include "MyHttpClient.h"
#include "MyTwilio.h"
#include "MyWeather.h"
#include "details.h"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

void print_response(int, const std::string&);

int main()
{
	Details details;

	MyTwilio twilio(details.get_account_sid(), details.get_auth_token());
	std::string response, message;
	std::stringstream message_stream;
	int result;
	
	MyWeather weather("Escondido");
	weather.display_details(true);
	result = weather.current_weather();
	response = weather.get_response();
	print_response(result, response);


	message_stream << std::fixed << std::setprecision(2) <<
		"Current weather for Escondido: " << weather.get_temperature() << "F";
	message = message_stream.str();

	twilio.display_details(true);
	result = twilio.send_message(details.get_to_number(), details.get_from_number(), 
		message , "", response);
	print_response(result, response);
	

	return 0;
}


void print_response(int result, const std::string& response)
{
	if (result != 0)
	{
		std::cout << "http request failed." << std::endl;
	}
	else
	{
		std::cout << "http request successful." << std::endl;
	}

	if (!response.empty())
	{
		std::cout << "Response: " << std::endl << response << std::endl;
	}
}