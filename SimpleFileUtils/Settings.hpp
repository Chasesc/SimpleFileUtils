#ifndef SFU_SETTINGS_HPP
#define SFU_SETTINGS_HPP

#include <iostream> //only for testing, should be removed
#include <string>
#include <cstdlib>

namespace sfu
{
class settings
{
public:
	settings() : _main_mode(mode::error), _sub_mode(mode::error), _force(mode::error), _hours(0), _path("") { };
	settings(int argc, char ** argv);

	const std::string error_string() const;

	//all of these are public functions are implicitly inline
	bool is_error() const { return _main_mode == mode::error; }
	bool is_force() const { return _force == mode::force; }
	bool dupe_active() const { return _main_mode == mode::duplicate; }
	bool old_active() const { return _main_mode == mode::old; }

	bool is_write_method() const { return _sub_mode == mode::write; }
	bool is_access_method() const { return _sub_mode == mode::access; }

	int get_hour_limit() const { return _hours; }
	std::string get_path() const { return _path; }
	//mode get_mode() const { return _main_mode; }
	//mode get_sub_mode() const { return _sub_mode; }

private:
	enum mode  { error = 0, duplicate, old, access, write, force };

	const std::string check_given_dir(const char * cstr);

	mode _main_mode;
	mode _sub_mode;
	mode _force; //set to mode::force if the user doesn't want a confirmation for deleting files, set to mode::error otherwise
	int _hours;
	std::string _path;
}; //class settings


//The directory path shouldn't end in a / or \ so we remove these if it's there.  This also converts the path from a cstr to a std::string
inline const std::string check_given_dir(const char * cstr)
{
	std::string temp(cstr);
	if (temp.back() == '\\' || temp.back() == '/') { temp.pop_back(); }
	if (temp.back() == '"') { temp.pop_back(); }
	return temp;
}

} //namespace sfu
#endif
//SFU_SETTINGS_HPP