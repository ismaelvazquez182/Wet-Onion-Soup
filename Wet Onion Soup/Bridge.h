#pragma once

#include <cstdint>

class ProcessManager;

class Bridge 
{
public:
	Bridge();
	~Bridge();
	bool PutOnUniform(const char* uniform);
	void Execute();

private:
	uintptr_t m_GuildUniformPointer;
	ProcessManager *m_Game;
};
