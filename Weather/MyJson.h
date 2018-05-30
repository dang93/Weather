#pragma once
#include <json\json.h>
#include <string>
#include <memory>

class MyJson
{
public:
	MyJson();
	~MyJson();

	int parse(std::unique_ptr<std::string> );
	Json::Value get_field(const std::string&, const std::string& = "");
private:
	Json::Value json_data;
	Json::Reader json_reader;
};

