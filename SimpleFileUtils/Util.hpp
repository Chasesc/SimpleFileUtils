/*
Useful utility functions
*/

#ifndef SFU_UTIL_HPP
#define SFU_UTIL_HPP

#include "BoostCore.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>

namespace sfu
{
	namespace util
	{

		std::string time_t_to_string(const std::time_t t);

		void delete_files(const std::vector<fs::path> &paths);

		std::vector<fs::path> get_files_in_dir(const std::string &dir);

	} //namespace util

} //namespace sfu

#endif //SFU_UTIL_HPP