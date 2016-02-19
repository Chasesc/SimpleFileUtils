#include "OldRemover.hpp"

namespace sfu
{
	//returns true if the function deletes any files, false otherwise
	bool remove_old_files(const std::vector<fs::path> &files, const sfu::settings &settings)
	{
		std::vector<fs::path> old_files = get_old_files(files, settings);		

		if (old_files.size() <= 0)	
		{ 
			std::cout << "No old files in that directory!" << std::endl;
			return false;
		}

		char c;

		//TODO: Add option to remove select files
		if (!settings.is_force())
		{
			std::cout << "These files are going to be removed.  Continue? [Y/N]\n";
			std::cin >> c;
		}

		if (c == 'y' || c == 'Y')
		{
			util::delete_files(old_files);
		}

		return true;
	}

	std::vector<fs::path> get_old_files(const std::vector<fs::path> &files, const sfu::settings &settings)
	{
		greg::date today(greg::day_clock::local_day());
		std::vector<fs::path> old_files;

		for (const fs::path &f : files)
		{
			std::time_t t;
			if (settings.is_write_method())
			{
				t = fs::last_write_time(f);
			}
			else if (settings.is_access_method())
			{
				//TODO: Implement access method
				std::cout << "Getting file times by last access is currently not implemented.\nTry using -w to"
						  << " determine age using last write time." << std::endl;

				break;
			}

			greg::date file_date(greg::from_string(util::time_t_to_string(t)));
			greg::date_duration file_age = today - file_date;

			if (file_age.is_negative() || file_age.is_special())
			{
				std::cout << "DEBUG: is neg or is special: " << f.filename().string() << std::endl;
				continue;
			}

			if (file_age.days() > settings.get_hour_limit())
			{
				std::cout << f.filename().string() << ": " << file_age.days() << std::endl;
				old_files.push_back(f);
			}
		}

		return old_files;
	}

} //namespace sfu