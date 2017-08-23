/*
 * IO.hpp
 *
 *
 *  Class for basic IO operations
 */

#ifndef IO_HPP_
#define IO_HPP_

namespace IO {

	/*
	 * FileExists:
	 *		Check if the file exists
	 *
	 * path:
	 *		Path to variable in config (eg: "group0.group1.var0")
	 */
	bool FileExists(const char * filePath);

}

#endif /* IO_HPP_ */
