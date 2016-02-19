/*
see what-is.txt for more info
*/

#include <cstdlib>

#include "SimpleFileUtils.hpp"

int main(int argc, char **argv)
{
	const sfu::settings settings(argc, argv); 
	std::string dir = settings.get_path();

	if (settings.is_error() || !sfu::fs::exists(dir) || !sfu::fs::is_directory(dir))
	{ 
		std::cerr << settings.error_string();
		return EXIT_FAILURE; 
	}

	std::vector<sfu::fs::path> files = sfu::util::get_files_in_dir(dir);

	if (settings.old_active()) 
	{
		if (!sfu::remove_old_files(files, settings)) { return EXIT_FAILURE; }
	}
	else if (settings.dupe_active())
	{
		if (!sfu::remove_duplicate_files(files, settings)) { return EXIT_FAILURE; }
	}

	return EXIT_SUCCESS;
}
