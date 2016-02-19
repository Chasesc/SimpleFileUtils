#include "DuplicateRemover.hpp"

namespace sfu
{
	//returns true if the function deletes any files, false otherwise
	bool remove_duplicate_files(const std::vector<fs::path> &files, const sfu::settings &settings)
	{
		if (files.size() <= 0)
		{
			std::cout << "That directory is empty!\n";
			return false;
		}

		std::vector<fs::path> dupe_files = get_dupes_from_files(files);

		if (dupe_files.size() <= 0)
		{
			std::cout << "There are no duplicate files in that directory!\n";
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
			util::delete_files(dupe_files);
		}

		return true;
	}

	//TODO: make this function use file hashes instead
	std::vector<fs::path> get_dupes_from_files(const std::vector<fs::path> &files)
	{
		std::vector<fs::path> dupes;
		uintmax_t prev = 0, curr = 0;
		std::string file_exten_prev, file_exten_curr;

		for (auto it = files.crbegin(); it != files.crend(); ++it) //loops in reverse alphabetical order
		{
			file_exten_curr = it->extension().string();
			curr = fs::file_size(*it);

			//we assume a file is a duplicate if the file is next to a file alphabetically with the same file size
			if (file_exten_curr == file_exten_prev && prev == curr && prev != 0)
			{
				std::cout << it->filename().string() << std::endl;
				dupes.push_back(*it);
			}

			prev = curr;
			file_exten_prev = file_exten_curr;
		}

		return dupes;
	}	

} //namespace sfu