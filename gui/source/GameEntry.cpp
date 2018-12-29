/*
 * GameEntry.cpp
 *
 *
 *  Class containing game information and cheats
 */

#include <vector>
#include <map>
#include <iterator>

#include "Cheats/GameList.hpp"
#include "Globals.hpp"
#include "IO/UTF8.hpp"
#include "IO/IO.hpp"

using namespace Mini2D;

namespace Cheats
{
	//---------------------------------------------------------------------------
	// Setup
	//---------------------------------------------------------------------------
	GameEntry::GameEntry()
	{
	}

	GameEntry::~GameEntry()
	{
	}

	//---------------------------------------------------------------------------
	// Getters and Setters
	//---------------------------------------------------------------------------
	const std::string& GameEntry::Name() const
	{
		return _name;
	}

	//---------------------------------------------------------------------------
	// Process
	//---------------------------------------------------------------------------
	bool GameEntry::Update(const char * path)
	{
		return processFile(path);
	}

	bool GameEntry::processFile(const char * path)
	{
		if (!path || !IO::FileExists(path))
			return false;

		return true;
	}
}
