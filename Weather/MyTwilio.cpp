#include "MyTwilio.h"


MyTwilio::MyTwilio()
{
}


MyTwilio::~MyTwilio()
{
}

int MyTwilio::send_message(std::string const& to, std::string const& from, 
	std::string const& body, std::string const& picture_url, std::string& response)
{

	std::string url_string = "https://api.twilio.com/2010-04-01/Accounts/" + _account_sid +
		"/Messages";
	
	char *body_encoded_special_char = curl_easy_escape(client.get_handle(), body.c_str(), 0);
	std::string parameter_string = "To=" + to + "&From=" + from + "&Body=" + body_encoded_special_char;

	client.set_url(url_string);
	client.set_parameters(parameter_string);
	client.set_credentials(_account_sid, _auth_token);
	client.POST_request();
	client.check_error_codes();
	response = client.get_response();
	client.finish();

	return 0;
}

int MyTwilio::display_details()
{
	client.set_detailed_flag(true);

	return 0;
}