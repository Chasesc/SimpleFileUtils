#ifndef SFU_SFU_HPP
#define SFU_SFU_HPP

#include <boost/filesystem.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <exception>

namespace sfu
{

namespace fs = boost::filesystem;
namespace greg = boost::gregorian;

inline std::string time_t_to_string(const std::time_t t);

void get_files(std::vector<fs::path> &files, const std::string &dir); //gets all the files in a directory and stores them into a vector

void get_dupes_from_files(const std::vector<fs::path> &files, std::vector<fs::path> &dupes);

void delete_files(const std::vector<fs::path> &paths);

bool remove_duplicate_files(const std::vector<fs::path> &files); //returns true if successful, false otherwise

bool file_times(const std::vector<fs::path> &files); //returns true if successful, false otherwise

} //namespace sfu
#endif 
//SFU_SFU_HPP