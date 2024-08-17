#include "../header/HttpClient.h"

HttpClient::~HttpClient()
{
	if (hConnect) InternetCloseHandle(hConnect);
	if (hSession) InternetCloseHandle(hSession);
}

bool HttpClient::init()
{
	hSession = InternetOpenA("ClientApp", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hSession) return false;

	hConnect = InternetConnectA(hSession, server.c_str(), port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	return hConnect != NULL;
}

bool HttpClient::sendData(const std::string& endpoint, const std::string& postData, const std::string& header)
{
	HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", endpoint.c_str(), NULL, NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, 0);
	if (!hRequest) return false;

	bool result = HttpSendRequestA(hRequest, header.c_str(), header.length(), (LPVOID)postData.c_str(), postData.length());
	if (!result) {
		std::cerr << "HttpSendRequestA failed with error: " << GetLastError() << std::endl;
	}
	InternetCloseHandle(hRequest);
	return result;
}
