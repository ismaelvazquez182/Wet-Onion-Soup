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
	char* GetCharacterName();

private:
	uintptr_t m_PlayerPointer;
	ProcessManager *m_Game;
};
