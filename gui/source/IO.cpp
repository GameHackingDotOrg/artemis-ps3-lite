
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

#include "IO/IO.hpp"
#include "IO/UTF8.hpp"

#include "utf.h"

namespace IO {

	//---------------------------------------------------------------------------
	// IO
	//---------------------------------------------------------------------------
	bool FileExists(const char * filePath) {
		std::ifstream fin(filePath);
		if (fin.good())
			return true;

		return false;
	}

	//---------------------------------------------------------------------------
	// UTF8
	//---------------------------------------------------------------------------
	std::string UTF8::ReadFile(const char * filePath) {
		std::stringstream ss;
		std::string ws;
	    std::ifstream fin(filePath);
	    ss << fin.rdbuf(); // dump file contents into a stringstream
	    return ss.str();
	}

	void UTF8::WriteFile(const char * filePath, const std::string& string) {
	    std::ofstream out(filePath);
	    out << string;
	}

	std::wstring UTF8::ToUTF32(const std::string& string) {
		return (std::wstring)utf::to_utf32((utf::string8)string);
	}

	std::string UTF8::FromUTF32(const std::wstring& string) {
		return (std::string)utf::to_utf8((utf::string32)string);
	}

}
