#include "NetworkManager.h"
#include <windows.h>
#include <winhttp.h>
#include <sstream>
#include <stdexcept>

#pragma comment(lib, "winhttp.lib")

NetworkManager::~NetworkManager() {}
NetworkManager::NetworkManager(std::wstring host, unsigned int portNumber): m_Host{host}, m_PortNumber{portNumber} {}

std::string NetworkManager::SendGetRequest(std::wstring request)
{
    // Open a WinHTTP session
    HINTERNET hSession = WinHttpOpen(L"Bobby Hill's Wet Onion Soup/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

    if (!hSession) {
        MessageBoxA(0, "Failed to create session.", "SendGetRequest", MB_OK);
        return "";
    }

    // Connect to the server
    HINTERNET hConnect = WinHttpConnect(hSession, m_Host.c_str(), m_PortNumber, 0);

    if (!hConnect) {
        MessageBoxA(0, "Failed to connect.", "SendGetRequest", MB_OK);
        WinHttpCloseHandle(hSession);
        return "";
    }

    // Create an HTTP request handle
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", request.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);

    if (!hRequest) {
        MessageBoxA(0, "Failed to create HTTP request handle.", "SendGetRequest", MB_OK);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return "";
    }

    // Send the request
    BOOL bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

    std::stringstream response;

    if (!bResults) {
        MessageBoxA(0, "Failed to send the request.", "SendGetRequest", MB_OK);
        return "";
    } else {
        // Receive the response
        bResults = WinHttpReceiveResponse(hRequest, NULL);

        if (bResults) {
            DWORD dwSize = 0;
            do {
                // Check how much data is available
                if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
                    MessageBoxA(0, "Failed to check how much data is available", "SendGetRequest", MB_OK);
                    break;
                }
                if (dwSize == 0) break;

                // Allocate space for the buffer
                char* buffer = new char[dwSize + 1];
                ZeroMemory(buffer, dwSize + 1);

                DWORD dwDownloaded = 0;
                if (WinHttpReadData(hRequest, (LPVOID)buffer, dwSize, &dwDownloaded)) 
                    response.write(buffer, dwDownloaded);

                delete[] buffer;

            } while (dwSize > 0);
        }
        else {
            MessageBoxA(0, "Failed to receive a request.", "SendGetRequest", MB_OK);
        }
    }

    // Cleanup
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    return response.str();
}

void NetworkManager::SetHost(std::wstring newHost, unsigned int newPort) { 
    m_Host = newHost; 
    m_PortNumber = newPort;
}