#pragma once

#include <cstdint>
#include <vector>

class ProcessManager;
class NetworkManager;
struct GuildData;

class Bridge 
{
public:
	Bridge();
	~Bridge();
	bool PutOnUniform(const char* uniform);
	char* GetCharacterName();
	bool GetGuilds(std::vector<GuildData> &guildList);
	bool CreateGuild(std::vector<GuildData>& guildList, const char* uniform, const char* guildName, bool isExclusive);
	bool ChangeServer(const char* newHost, const char* newPort);
	bool QuitGuild(std::vector<GuildData>& guildList, const char* guildToQuit);

private:
	uintptr_t m_PlayerPointer;
	NetworkManager *m_Net;
	ProcessManager *m_Game;
	char* m_CurrentCharacter;

private:
	unsigned int getSoulID();
};