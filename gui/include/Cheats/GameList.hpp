/*
 * GameList.hpp
 *
 *
 *  Class for loading and processing game lists
 */

#ifndef GAMELIST_HPP_
#define GAMELIST_HPP_

#include <map>
#include <vector>

#include "GameEntry.hpp"

namespace Cheats
{
	class GameList
	{
	public:

		std::map<std::string, GameEntry*> GameEntries;

		/*
		 * GameList Constructor
		 *
		 * directories:
		 *		Directories to load cheats from
		 * count:
		 *		Number of directories in 'directories'
		 */
		GameList(const char ** directories, int count);
		~GameList();

		/*
		 * ReadTotalEntries:
		 *		Grabs all the cheat files from given directories
		 *
		 * Return:
		 *		Number of entries
		 */
		unsigned long ReadTotalEntries();

		/*
		 * ReadIncrement:
		 *		ProgressWheel callback for reading cheats in steps
		 *
		 * userData:
		 *		Instance of GameList
		 * count:
		 *		Number of files to read
		 * index:
		 *		Which file to read
		 *
		 * Return:
		 *		False if failed
		 */
		static bool ReadIncrement(void * userData, unsigned long count, unsigned long index);

	private:
		// Directories to parse cheats from
		const char ** _directories;

		// Number of entries in '_directories'
		int _count;

		// Specific files to read cheats from
		std::vector<std::string> _files;
	};
}

#endif /* GAMELIST_HPP_ */
