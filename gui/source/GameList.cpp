/*
 * GameList.cpp
 *
 *
 *  Class for loading and processing game lists
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
	GameList::GameList(const char ** directories, int count) :
	_directories(directories),
	_count(count)
	{

	}

	GameList::~GameList()
	{

	}

	//---------------------------------------------------------------------------
	// Reading
	//---------------------------------------------------------------------------
	unsigned long GameList::ReadTotalEntries()
	{
		if (_files.size() > 0)
			std::vector<std::string>().swap(_files);

		for (int x = 0; x < _count; x++)
		{
			printf("reading from %s ... ", _directories[x]);
			std::vector<std::string> newFiles = IO::GetFiles(_directories[x], ".ncl");
			if (newFiles.size() > 0)
			{
				printf("%d\n", (int)newFiles.size());
				_files.reserve(_files.size() + newFiles.size());
				_files.insert(_files.end(), newFiles.begin(), newFiles.end());
			}
			else
				printf("error\n");
		}

		return _files.size();
	}

	bool GameList::ReadIncrement(void * userData, unsigned long count, unsigned long index)
	{
		GameList * gameList = (GameList*)userData;
		if (gameList == NULL)
			return false;

		if (index > gameList->_files.size())
			return false;

		std::string filePath = gameList->_files.at(index);
		if (!IO::FileExists(filePath.c_str()))
			return false;

		std::map<std::string, GameEntry*>::iterator it = gameList->GameEntries.find(filePath);
		if (it != gameList->GameEntries.end())
		{
			// Update existing entry
			if (!it->second->Update(filePath.c_str()))
				return false;
		}
		else
		{
			// Add new entry
			GameEntry *entry = new GameEntry();
			if (!entry->Update(filePath.c_str()))
			{
				delete entry;
				return false;
			}

			gameList->GameEntries.insert(std::make_pair (filePath, entry));
		}

		return true;
	}
}
