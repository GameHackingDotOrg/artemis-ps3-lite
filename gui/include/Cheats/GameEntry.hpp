/*
 * GameEntry.hpp
 *
 *
 *  Class containing game information and cheats
 */

#ifndef GAMEENTRY_HPP_
#define GAMEENTRY_HPP_

#include <string>

namespace Cheats
{
	class GameEntry
	{
	public:

		/*
		 * GameEntry Constructor
		 *
		 * path:
		 *		Path to game entry
		 */
		GameEntry();
		~GameEntry();

		/*
		 * Update:
		 *		Updates the cheats from the given file
		 *
		 * path:
		 *		Font to use for printing the top label
		 *
		 * Return:
		 *		False if failed
		 */
		bool Update(const char * path);

		// Getters and setters
		const std::string& Name() const;

	private:
		// The name of the Game
		std::string _name;

		// Processes the file's cheats
		bool processFile(const char * path);
	};
}

#endif /* GAMEENTRY_HPP_ */
