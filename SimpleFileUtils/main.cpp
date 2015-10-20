#include "SimpleFileUtils.hpp"
#include "Settings.hpp"

int main(int argc, char **argv)
{
	const sfu::settings settings(argc, argv);
	
	if (settings.is_error()) { std::cout << settings.error_string(); return EXIT_FAILURE; }

	std::string dir = settings.get_path();
	if (!sfu::fs::exists(settings.get_path()) || !sfu::fs::is_directory(settings.get_path())) { std::cout << settings.error_string(); return EXIT_FAILURE; }

	std::vector<sfu::fs::path> files;
	sfu::get_files(files, settings.get_path());

	if (settings.dupe_active()) 
	{
		if (!sfu::file_times(files)) { return EXIT_FAILURE; }
	}
	else if (settings.old_active())
	{
		if (!sfu::remove_duplicate_files(files)) { return EXIT_FAILURE; }
	}

	return EXIT_SUCCESS;
}
