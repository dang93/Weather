#pragma once
#include <curl\curl.h>
#include <cstdint>
#include <memory>
#include <string>

class MyHttpClient
{
public:
	MyHttpClient();
	MyHttpClient(const std::string&);
	~MyHttpClient();

	int init();
	int set_post_parameters(const std::string&);
	int set_credentials(const std::string&, const std::string&);
	int set_detailed_flag(bool);
	int set_url(const std::string&);
	int POST_request();
	int GET_request();
	int check_error_codes();
	int finish();

	CURL* get_handle() const { return _curl; }
	std::string get_response() const { return _response; }
	std::unique_ptr<std::string> get_http_data() { return std::move(_http_data); }
private:
	CURL *_curl;
	CURLcode _res;
	std::string _url;
	std::string _parameters;
	std::unique_ptr<std::string> _http_data;
	std::string _response;
	int _http_code;
	bool _detailed_flag;
};

