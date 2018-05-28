#include "MyHttpClient.h"

std::size_t null_write(const char* input, std::size_t size, std::size_t num, void* output)
{
	return size * num;
}

std::size_t callback(const char* input, std::size_t size, std::size_t num, std::string* output)
{
	std::size_t total_bytes = size * num;
	output->append(input, total_bytes);
	return total_bytes;
}

MyHttpClient::MyHttpClient()
{
	init();
}

MyHttpClient::MyHttpClient(const std::string& url)
{
	_url = url;
}

MyHttpClient::~MyHttpClient()
{

}

int MyHttpClient::init()
{
	curl_global_init(CURL_GLOBAL_ALL);
	_curl = curl_easy_init();
	_http_data = std::unique_ptr<std::string> (new std::string());
	_detailed_flag = false;

	curl_easy_setopt(_curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
	curl_easy_setopt(_curl, CURLOPT_TIMEOUT, 10);
	curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, callback);
	return 0;
}

int MyHttpClient::set_parameters(const std::string& parameter)
{
	_parameters.append(parameter);

	return 0;
}

int MyHttpClient::set_credentials(const std::string& username, const std::string& password)
{
	curl_easy_setopt(_curl, CURLOPT_USERNAME, username.c_str());
	curl_easy_setopt(_curl, CURLOPT_PASSWORD, password.c_str());

	return 0;
}

int MyHttpClient::set_detailed_flag(bool flag)
{
	_detailed_flag = flag;

	return 0;
}

int MyHttpClient::set_url(const std::string& url)
{
	_url = url;

	return 0;
}
int MyHttpClient::POST_request()
{
	curl_easy_setopt(_curl, CURLOPT_POST, 1);
	curl_easy_setopt(_curl, CURLOPT_URL, _url.c_str());
	curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, _parameters.c_str());

	if (!_detailed_flag)
	{
		curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, null_write);
	}
	else
	{
		curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, callback);
		curl_easy_setopt(_curl, CURLOPT_WRITEDATA, _http_data.get());
	}

	_res = curl_easy_perform(_curl);
	curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &_http_code);

	return 0;
}

int MyHttpClient::check_error_codes()
{
	if (_res != CURLE_OK)
	{
		_response = curl_easy_strerror(_res);
		return 1;
	}
	if (_http_code != 200 && _http_code != 201)
	{
		_response = *_http_data.get();
		return 1;
	}

	_response = *_http_data.get();
	return 0;
}

int MyHttpClient::finish()
{
	curl_easy_cleanup(_curl);

	return 0;
}
