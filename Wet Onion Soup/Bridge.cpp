#include "Bridge.h"
#include "ProcessManager.h"
#include "Souls.h"

Bridge::~Bridge() { delete m_Game; }

Bridge::Bridge()
{
	m_Game = new ProcessManager(L"Souls.exe");
	m_Game->Read(reinterpret_cast<LPCVOID>(PLAYER_BASE), &m_PlayerPointer, sizeof(m_PlayerPointer));
}

bool Bridge::PutOnUniform(const char* uniform)
{
	return m_Game->Write(reinterpret_cast<LPVOID>(m_PlayerPointer + GUILD_UNIFORM_OFFSET), uniform, GUILD_UNIFORM_LENGTH - 1);
}

char* Bridge::GetCharacterName()
{
	char* name = new char[CHARACTER_NAME_LENGTH] {0};
	m_Game->Read(reinterpret_cast<LPCVOID>(m_PlayerPointer + CHARACTER_NAME_OFFSET), name, CHARACTER_NAME_LENGTH - 1);
	return name;
}

void Bridge::Execute()
{

}