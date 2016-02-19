#ifndef SFU_SETTINGS_HPP
#define SFU_SETTINGS_HPP

#include <iostream> //only for testing
#include <string>
#include <cstdlib>

namespace sfu
{
	class settings
	{
	public:
		settings() : m_main_mode(mode::error), m_sub_mode(mode::error), m_force(mode::error), m_hours(0), m_path("") { };
		settings(int argc, char ** argv);

		const std::string error_string() const;

		bool is_error() const { return m_main_mode == mode::error; }
		bool is_force() const { return m_force == mode::force; }
		bool dupe_active() const { return m_main_mode == mode::duplicate; }
		bool old_active() const { return m_main_mode == mode::old; }

		bool is_write_method() const { return m_sub_mode == mode::write; }
		bool is_access_method() const { return m_sub_mode == mode::access; }

		int get_hour_limit() const { return m_hours; }
		std::string get_path() const { return m_path; }

	private:
		enum mode  { error = 0, duplicate, old, access, write, force };

		mode m_main_mode;
		mode m_sub_mode;
		mode m_force; //set to mode::force if the user doesn't want a confirmation for deleting files, set to mode::error otherwise
		int m_hours;
		std::string m_path;

		const std::string kVersion = "0.2";

	}; //class settings


} //namespace sfu

#endif //SFU_SETTINGS_HPP
