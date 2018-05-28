#include "MyHttpClient.h"
#include "MyTwilio.h"
#include "details.h"

#include <iostream>
#include <string>
int main()
{
	MyTwilio twilio(details::get_account_sid(), details::get_auth_token());
	std::string response;
	int result;
	
	//twilio.display_details();
	result = twilio.send_message("+17608183606", "+17606915120", "test: hiding details", "", response);
	
	if (result != 0)
	{
		std::cout << "Message send failed." << std::endl;
		if (!response.empty())
		{
			std::cout << "Response: " << std::endl << response << std::endl;
		}
	}
	else
	{
		std::cout << "Message sent successfully" << std::endl;
		std::cout << "Response: " << std::endl << response << std::endl;
	}
	return 0;
}