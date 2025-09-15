#include "Bridge.h"
#include "Globals.h"
#include "GuildData.h"
#include "ProcessManager.h"
#include "NetworkManager.h"
#include "Souls.h"

#include <cstdlib>
#include <cstring>
#include <sstream>

Bridge::~Bridge() { 
	delete m_Game; 
	delete m_Net;
}

Bridge::Bridge() : m_CurrentCharacter{nullptr}
{
	m_Game = new ProcessManager(L"Souls.exe");
	m_Game->Read(reinterpret_cast<LPCVOID>(PLAYER_BASE), &m_PlayerPointer, sizeof(m_PlayerPointer));
	m_Net = new NetworkManager(L"192.168.111.135");
}

bool Bridge::PutOnUniform(const char* uniform)
{
	return m_Game->Write(reinterpret_cast<LPVOID>(m_PlayerPointer + GUILD_UNIFORM_OFFSET), uniform, GUILD_UNIFORM_LENGTH - 1);
}

char* Bridge::GetCharacterName()
{
	char* name = new char[CHARACTER_NAME_LENGTH] {0};
	m_Game->Read(reinterpret_cast<LPCVOID>(m_PlayerPointer + CHARACTER_NAME_OFFSET), name, CHARACTER_NAME_LENGTH - 1);
	m_CurrentCharacter = name;
	return name;
}

unsigned int Bridge::getSoulID()
{
	unsigned int soulID;
	m_Game->Read(reinterpret_cast<LPCVOID>(m_PlayerPointer + SOULID_OFFSET), &soulID, sizeof(soulID));
	return soulID;
}

bool Bridge::GetGuilds(std::vector<GuildData> &guildList)
{
	std::wstringstream ss;

	ss << L"/" << L"fetch&" << std::to_wstring(getSoulID()) << L"&" << m_CurrentCharacter;
	std::string response = m_Net->SendGetRequest(ss.str());

	if (response == "") return true;

	if (guildList.empty()) {
		guildList.push_back({ "WoS", "We owe Samsyn (ten bucks)", "Member", 1, false });
		guildList.push_back({ "MWGA", "Make WoS Great Again", "President of the HOA", 2, false });
		guildList.push_back({ "KoE", "Kings (and queens) of Evergreen", "Propane Master", 0, true });
	}

	return false;
}

bool Bridge::CreateGuild(std::vector<GuildData>& guildList, const char* uniform, const char* guildName, bool isExclusive)
{
	if (std::strcmp(uniform, "") == 0 || std::strcmp(guildName, "") == 0) {
		return true;
	}

	std::wstringstream ss;

	ss << L"/" << L"create&" << std::to_wstring(getSoulID()) << L"&" << m_CurrentCharacter << L"&" << uniform << L"&" << guildName << L"&" << isExclusive;
	std::string response = m_Net->SendGetRequest(ss.str());

	if (response == "") return true;
	guildList.push_back({ uniform, guildName, "Leader", 0, isExclusive});
	GetGuilds(guildList);
	return false;
}

bool Bridge::ChangeServer(const char* newHost, const char* newPort)
{
	if (std::strcmp(newHost, "") == 0 || std::strcmp(newPort, "") == 0) {
		return true;
	}

	unsigned int port = std::atoi(newPort);
	if (port < MIN_PORT || port > MAX_PORT) {
		return true;
	}
	wchar_t host[MAX_DOMAIN_LENGTH];
	mbstowcs_s(0, host, MAX_DOMAIN_LENGTH, newHost, MAX_DOMAIN_LENGTH);
	m_Net->SetHost(host, port);
	return false;
}