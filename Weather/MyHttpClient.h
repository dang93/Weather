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
	//std::size_t callback(const char*, std::size_t, std::size_t, std::string*);
	//std::size_t null_write(const char *, std::size_t, std::size_t, void*);
	int set_parameters(const std::string&);
	int set_credentials(const std::string&, const std::string&);
	int set_detailed_flag(bool);
	int set_url(const std::string&);
	int POST_request();
	int check_error_codes();
	int finish();

	CURL* get_handle() const { return _curl; }
	std::string get_response() const { return _response; }
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

