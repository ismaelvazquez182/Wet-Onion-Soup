#pragma once

#include <string>

class NetworkManager
{
public:
	NetworkManager(std::wstring host, unsigned int portNumber=80);
	~NetworkManager();

	// sends a get request and returns the response
	// request is the "resource", ex google.com/fishandchips -> request = "/fishandchips"
	std::string SendGetRequest(std::wstring request);
	void SetHost(std::wstring newHost, unsigned int newPort);
private:
	std::wstring m_Host;
	unsigned int m_PortNumber;
};