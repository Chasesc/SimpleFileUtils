#include "Util.hpp"

namespace sfu
{

	namespace util
	{

		//returns a std::string from a std::time_t in the format "year/month/day"
		std::string time_t_to_string(const std::time_t t)
		{
			const std::tm * tm = std::localtime(&t);
			std::stringstream date;
			date << 1900 + tm->tm_year << "/" << 1 + tm->tm_mon << "/" << tm->tm_mday;
			return date.str();
		}

		//attempts to delete all of the files in the path vector
		void delete_files(const std::vector<fs::path> &paths)
		{
			for (const fs::path &i : paths)
			{
				try
				{
					fs::remove(i);
					std::cout << "Removed: " << i.filename().string() << std::endl;
				}
				catch (...)
				{
					std::cerr << "Error removing " << i.filename().string() << ".  Is the file open?" << std::endl;
				}
			}
		}

		std::vector<fs::path> get_files_in_dir(const std::string &dir)
		{
			std::vector<fs::path> files;

			fs::directory_iterator end;
			for (fs::directory_iterator begin(dir); begin != end; ++begin)
			{
				try
				{
					if (fs::is_regular_file(begin->status()))
					{
						files.push_back(begin->path());
					}
				}
				catch (const std::exception &e)
				{
					std::cerr << "error: " << e.what() << " at " << begin->path().filename().string() << std::endl;
				}
			}

			return files;
		}

	} //namespace util

} //namespace sfu