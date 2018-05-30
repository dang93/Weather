#pragma once
#include "MyHttpClient.h"
#include <string>

class MyTwilio
{
public:
	MyTwilio();
	MyTwilio(std::string const& account_sid, std::string const& auth_token) :
		_account_sid(account_sid), _auth_token(auth_token) {}
	~MyTwilio();

	int send_message(std::string const& to, std::string const& from, 
		std::string const& body, std::string const& picture_url, 
		std::string& response);
	int display_details(bool);
private:
	MyHttpClient client;
	std::string _account_sid;
	std::string _auth_token;
};

