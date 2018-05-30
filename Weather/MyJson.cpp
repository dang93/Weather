#include "MyJson.h"



MyJson::MyJson()
{
}


MyJson::~MyJson()
{
}


int MyJson::parse(std::unique_ptr<std::string> http_data)
{
	if (json_reader.parse(*http_data, json_data))
		return 0;
	return 1;
}


Json::Value MyJson::get_field(const std::string& field, const std::string& subfield)
{
	if (subfield != "")
	{
		return json_data[field][subfield];
	}
	return json_data[field];
}