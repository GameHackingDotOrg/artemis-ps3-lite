/*
 * Config.hpp
 *
 *
 *  Class for user configurations
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <libconfig.h>

namespace Config {

	class Config {
	public:

		/*
		 * Config Constructor
		 *
		 * filePath:
		 *		Path to config
		 */
		Config(const char * filePath);
		~Config();

		/*
		 * GetInt:
		 *		Grabs the int at the specified path within the config
		 *
		 * path:
		 *		Path to variable in config (eg: "group0.group1.var0")
		 */
		int GetInt(const char * path);

		/*
		 * GetBool:
		 *		Grabs the bool at the specified path within the config
		 *
		 * path:
		 *		Path to variable in config (eg: "group0.group1.var0")
		 */
		bool GetBool(const char * path);

		/*
		 * GetCString:
		 *		Grabs the  char array at the specified path within the config
		 *
		 * path:
		 *		Path to variable in config (eg: "group0.group1.var0")
		 */
		const char * GetCString(const char * path);

	private:
		// libconfig config
		config_t _config;

		// Contruct the config
		void buildConfig();
	};
}

#endif /* CONFIG_HPP_ */
