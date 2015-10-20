#include "SimpleFileUtils.hpp"

namespace sfu
{

//returns true if successful, false otherwise
bool file_times(const std::vector<fs::path> &files, const sfu::settings &settings)
{

	std::vector<fs::path> old_files;

	greg::date today(greg::day_clock::local_day());

	for (const fs::path &f : files)
	{
		std::time_t t;
		if (settings.is_write_method())
		{
			t = fs::last_write_time(f);
		}
		else if (settings.is_access_method())
		{
			//HANDLE hand_file = ::CreateFile(f.filename.c_str(), GENERIC_READ, ) win version, non boost
			//TODO: Implement access method
			std::cout << "Getting file times by last access is currently not implemented.\nTry using -w to"
				      << " determine age using last write time." << std::endl;
			return false;
		}

		greg::date file_date(greg::from_string(time_t_to_string(t)));
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

	if (old_files.size() <= 0)	{ std::cout << "No old files in that directory!" << std::endl; return true; }

	//TODO: Add option to remove select files
	if (!settings.is_force())
	{
		char c;
		std::cout << "These files are going to be removed.  Continue? [Y/N]\n";
		std::cin >> c;
		if (c == 'n' || c == 'N') { return true; }
	}

	delete_files(old_files);	

	return true;
}

//returns a std::string from a time_t in the format "year/month/day"
inline std::string time_t_to_string(const std::time_t t)
{
	std::tm * tm = std::localtime(&t);
	std::stringstream date;
	date << 1900 + tm->tm_year << "/" << 1 + tm->tm_mon << "/" << tm->tm_mday;
	return date.str();
}

//returns true if successful, false otherwise
bool remove_duplicate_files(const std::vector<fs::path> &files, const sfu::settings &settings)
{
	std::vector<fs::path> dupe_files;

	if (files.size() <= 0) { std::cout << "That directory is empty!\n"; return true; }

	get_dupes_from_files(files, dupe_files);

	if (dupe_files.size() <= 0) { std::cout << "There are no duplicate files in that directory!\n"; return true; }

	//TODO: Add option to remove select files
	if (!settings.is_force())
	{
		char c;
		std::cout << "These files are going to be removed.  Continue? [Y/N]\n";
		std::cin >> c;
		if (c == 'n' || c == 'N') { return true; }
	}	

	delete_files(dupe_files);

	return true;
}

void get_files(std::vector<fs::path> &files, const std::string &dir)
{
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
}

void get_dupes_from_files(const std::vector<fs::path> &files, std::vector<fs::path> &dupes)
{
	//possible? TODO: Currently, this determines if a file is duplicate if it's next to another file alphabetically with the same file size.
	//This method obviously has a few drawbacks.  Create sub_method of mode::duplicate to calculate the files hash and check if any are the same.

	uintmax_t prev = 0, curr = 0;
	std::string file_exten_prev, file_exten_curr;
	std::vector<fs::path>::const_reverse_iterator end = files.rend();
	for (std::vector<fs::path>::const_reverse_iterator it = files.rbegin(); it != end; ++it) //loops in reverse alphabetical order
	{
		file_exten_curr = it->extension().string();
		curr = fs::file_size(*it);
		//we assume a file is a duplicate if the file is next to a file alphabetically with the same file size
		if (file_exten_curr == file_exten_prev && prev == curr && prev != 0)
		{
			std::cout << it->filename() << std::endl;
			dupes.push_back(*it);
		}
		prev = curr;
		file_exten_prev = file_exten_curr;
	}
}

void delete_files(const std::vector<fs::path> &paths)
{
	for (const fs::path &i : paths)
	{
		try
		{
			fs::remove(i);
			std::cout << "Removed: " << i.filename().string() << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error removing " << i.filename().string() << ".  Is the file open?" << std::endl;
		}
	}
}

}//namespace sfu