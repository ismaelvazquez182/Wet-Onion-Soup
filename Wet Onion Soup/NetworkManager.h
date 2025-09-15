#pragma once

#include <string>

class NetworkManager
{
public:
	NetworkManager(std::wstring host, int portNumber=80);
	~NetworkManager();

	// sends a get request and returns the response
	// request is the "resource", ex google.com/fishandchips -> request = "/fishandchips"
	std::string SendGetRequest(std::wstring request);
private:
	std::wstring m_Host;
	int m_PortNumber;
};