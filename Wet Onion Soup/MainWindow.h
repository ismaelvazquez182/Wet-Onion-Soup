#pragma once

#include "Globals.h"

#include <string>
#include <vector>

struct SDL_Window;
typedef struct SDL_GLContextState* SDL_GLContext;
struct ImGuiIO;
class Bridge;
struct GuildData;

class MainWindow
{
public:
	MainWindow();
	~MainWindow();
	void Show();
private:
	SDL_Window* m_Window;
	SDL_GLContext m_GLContext;
	ImGuiIO* m_IO;
	std::vector<GuildData> m_GuildList;
	Bridge *bridge;

	char m_Uniform[MAX_UNIFORM_LENGTH]{};
	char m_GuildName[MAX_GUILD_NAME_LENGTH]{};
	char m_TempGuild[MAX_UNIFORM_LENGTH] = "";
	bool m_IsCreateNewGuild{ false };
	bool m_IsExclusive{ false };

	bool m_IsChangeServer{ false };
	char m_PortNumber[MAX_PORT_DIGITS] = "";
	char m_Host[MAX_DOMAIN_LENGTH]{};
	char m_TempServer[6] = "";

private:
	void createNewGuild();
	void changeServer();
};