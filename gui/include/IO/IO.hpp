/*
 * IO.hpp
 *
 *
 *  Class for basic IO operations
 */

#ifndef IO_HPP_
#define IO_HPP_

#include <vector>

namespace IO
{

	/*
	 * FileExists:
	 *		Check if the file exists
	 *
	 * filePath:
	 *		File Path
	 */
	bool FileExists(const char * filePath);

	/*
 	 * GetFiles:
 	 *		Grabs all the files in a directory
 	 *
 	 * directoryPath:
 	 *		Path to directory
	 * extension:
	 *		Extension of files (set to NULL to ignore)
 	 */
	std::vector<std::string> GetFiles(const char * directoryPath, std::string extension);
}

#endif /* IO_HPP_ */
