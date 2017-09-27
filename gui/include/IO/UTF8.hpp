/*
 * UTF8.hpp
 *
 *
 *  Class for UTF8 IO operations
 */

#ifndef UTF8_HPP_
#define UTF8_HPP_

#include <string>

namespace IO
{
	class UTF8
	{
	public:

		/*
		 * ReadFile:
		 *		Reads the file
		 *
		 * filePath:
		 *		File path
		 *
		 * Return:
		 *		File contents
		 */
		static std::string ReadFile(const char * filePath);

		/*
		 * WriteFile:
		 *		Writes to the file
		 *
		 * filePath:
		 *		File path
		 * string:
		 *		String to write
		 */
		static void WriteFile(const char * filePath, const std::string& string);

		/*
		 * ToUTF32:
		 *		Converts the std::string to std::wstring
		 *
		 * string:
		 *		UTF8 string
		 *
		 * Return:
		 *		UTF32 string
		 */
		static std::wstring ToUTF32(const std::string& string);

		/*
		 * FromUTF32:
		 *		Converts the std::wstring to std::string
		 *
		 * string:
		 *		UTF32 string
		 *
		 * Return:
		 *		UTF8 string
		 */
		static std::string FromUTF32(const std::wstring& string);

	private:
	};
}

#endif /* UTF8_HPP_ */
