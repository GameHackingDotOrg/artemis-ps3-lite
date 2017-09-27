/*
 * Locale.cpp
 *
 *
 *  Class for language translations
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

#include "Config/Locale.hpp"
#include "IO/UTF8.hpp"

namespace Config
{
	static const std::wstring wstringEmpty = L"";

	//---------------------------------------------------------------------------
	// Process locale at filePath
	//---------------------------------------------------------------------------
	Locale::Locale(const char * filePath) :
	_filePath(filePath)
	{
		// Process file
		processFile((ARTEMIS_PATH "Locales/" + std::string(filePath)).c_str());
	}

	//---------------------------------------------------------------------------
	// Clean up
	//---------------------------------------------------------------------------
	Locale::~Locale()
	{
		_map.clear();
	}

	//---------------------------------------------------------------------------
	// Returns the value of the given key
	//---------------------------------------------------------------------------
	const std::wstring& Locale::GetValue(const std::wstring& key)
	{
		if (_map.count(key))
			return _map[key];

		return wstringEmpty;
	}

	//---------------------------------------------------------------------------
	// Gets the file path
	//---------------------------------------------------------------------------
	const char * Locale::FilePath()
	{
		return _filePath;
	}

	//---------------------------------------------------------------------------
	// Process the locale character by character
	//---------------------------------------------------------------------------
	void Locale::processFile(const char * filePath)
	{
		bool ignoreLine = false, isKey = false, isValue = false;
		std::wstring key, value;

		// Read UTF8 file into wstring
		std::wstring contents = IO::UTF8::ToUTF32(IO::UTF8::ReadFile(filePath));

		// Iterate each character
		for (std::wstring::iterator i = contents.begin(); i != contents.end(); i++)
		{
			// If we hit a comment, ignore the rest of the line
			if (*i == '#')
				ignoreLine = true;

			// Check if we hit a new line
			// If we do let's add a key value pair if we can
			if (*i == '\n' || *i == '\r')
			{
				ignoreLine = false;

				// Confirm we've got a key and a value
				if (isValue && key.size() > 0 && value.size() > 0)
				{
					_map[key] = value;

					isValue = false;
					isKey = false;
				}

				// Reset
				key.clear();
				value.clear();

				continue;
			}

			// If we're in a comment or we've hit the whitespaces before the value, skip
			if (ignoreLine || ((*i == ' ' || *i == '\t') && !isValue))
			{
				// We set this to false to indicate we're done with the key definition
				// If the key hasn't been defined yet this has no effect
				// Otherwise, down below, the next definition will fill the value
				isKey = false;
				continue;
			}

			// If this is the start of a definition, indicate whether to append to key or value
			if (!isKey && !isValue)
			{
				if (key.size() == 0)
				{
					isKey = true;
					isValue = false;
				}
				else if (value.size() == 0)
				{
					isKey = false;
					isValue = true;
				}
			}

			// Append definition to key or value
			if (isKey)
				key += *i;
			else if (isValue)
				value += *i;
		}
	}

}
