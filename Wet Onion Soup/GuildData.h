#pragma once

#include <string>

struct GuildData {
	std::string uniform;
	std::string guildName;
	std::string rank;
	unsigned int id;
	bool exclusive;
	bool selected;
};