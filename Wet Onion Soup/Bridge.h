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

private:
	uintptr_t m_PlayerPointer;
	NetworkManager *m_Net;
	ProcessManager *m_Game;
	char* m_CurrentCharacter;

private:
	unsigned int getSoulID();
};