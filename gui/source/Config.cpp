/*
 * Config.cpp
 *
 *
 *  Class for user configurations
 */

#include <string>

#include "Config/Config.hpp"
#include "IO/IO.hpp"

namespace Config
{

	//---------------------------------------------------------------------------
	// Load config
	//---------------------------------------------------------------------------
	Config::Config(const char * filePath)
	{
		// Construct full file path
		const char * fullPath = (ARTEMIS_PATH + std::string(filePath)).c_str();

		buildConfig();

		if (IO::FileExists(fullPath))
		{
			if (config_read_file(&_config, fullPath) != CONFIG_TRUE)
				printf("config error: %s\n", config_error_text(&_config));
		}
		else
		{
			config_write_file(&_config, fullPath);
		}
	}

	//---------------------------------------------------------------------------
	//
	//---------------------------------------------------------------------------
	Config::~Config()
	{

	}

	//---------------------------------------------------------------------------
	// Get Methods
	//---------------------------------------------------------------------------
	int Config::GetInt(const char * path)
	{
		return config_setting_get_int(config_lookup(&_config, path));
	}

	bool Config::GetBool(const char * path)
	{
		return config_setting_get_bool(config_lookup(&_config, path));
	}

	const char * Config::GetCString(const char * path)
	{
		return config_setting_get_string(config_lookup(&_config, path));
	}

	//---------------------------------------------------------------------------
	// Private Methods
	//---------------------------------------------------------------------------
	void Config::buildConfig()
	{
		config_setting_t *root, *group, *set;

		config_init(&_config);
		root = config_root_setting(&_config);

		// Root level
		set = config_setting_add(root, "translation", CONFIG_TYPE_STRING);
		config_setting_set_string(set, "american-english.txt");

		//
	}

}
