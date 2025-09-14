#include "Bridge.h"
#include "ProcessManager.h"
#include "Souls.h"

Bridge::~Bridge() { delete m_Game; }

Bridge::Bridge()
{
	m_Game = new ProcessManager(L"Souls.exe");
	m_Game->Read(reinterpret_cast<LPCVOID>(PLAYER_BASE), &m_GuildUniformPointer, sizeof(m_GuildUniformPointer));
	m_GuildUniformPointer += GUILD_UNIFORM_OFFSET;
}

bool Bridge::PutOnUniform(const char* uniform)
{
	return m_Game->Write(reinterpret_cast<LPVOID>(m_GuildUniformPointer), uniform, GUILD_UNIFORM_LENGTH - 1);
}

void Bridge::Execute()
{

}