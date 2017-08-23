/*
 * Locale.hpp
 *
 *
 *  Class for language translations
 */

#ifndef LOCALE_HPP_
#define LOCALE_HPP_

#include <map>
#include <string>

#include <Mini2D/Font.hpp>

namespace Config {

	class Locale {
	public:

		/*
		 * Locale Constructor
		 *
		 * filePath:
		 *		Path to translation file
		 */
		Locale(const char * filePath);
		~Locale();

		/*
		 * GetValue:
		 *		Grabs the value of a key value pair
		 *
		 * key:
		 *		The key of the key value pair
		 *
		 * Return:
		 *		The value
		 */
		const std::wstring& GetValue(const std::wstring& key);

		/*
		 * FilePath:
		 *		Grabs the filepath
		 *
		 * Return:
		 *		The key of the key value pair
		 */
		const char * FilePath();
	private:
		// Key value pair container
		std::map<std::wstring, std::wstring> _map;

		// Locale file
		const char * _filePath;


		// Get the translation data from the file
		void processFile(const char * filePath);
	};
}

#endif /* LOCALE_HPP_ */
