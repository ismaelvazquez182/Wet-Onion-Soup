#include "Bridge.h"
#include "GuildData.h"
#include "ProcessManager.h"
#include "NetworkManager.h"
#include "Souls.h"

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

	// action to perform
	// soul id
	// character name
	// /fetch&3472&BobbyHill
	ss << L"/" << L"fetch&" << std::to_wstring(getSoulID()) << L"&" << m_CurrentCharacter;
	std::string response = m_Net->SendGetRequest(ss.str());

	if (response == "") return true;

	return false;
}