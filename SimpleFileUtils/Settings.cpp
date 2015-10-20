#include "settings.hpp"

namespace sfu
{

const std::string settings::error_string() const
{
	return "Error: Incorrect or Incomplete arguments supplied.\n"
		   "d";
}

settings::settings(int argc, char ** argv) : settings::settings()
{
	std::cout << "argc: " << argc << std::endl;
	for (int i = 0; i != argc; ++i)
	{
		std::cout << "argv[" << i << "] = \"" << argv[i] << "\"" << std::endl;
	}

	if (argc > 2 && std::string(argv[1]) == "-d") 
	{ 
		std::cout << "\nin -d\n";
		_main_mode = mode::duplicate;
		_sub_mode = mode::error; //there is currently no sub mode for settings::mode::duplicate
		_path = sfu::check_given_dir(argv[2]);
		_force = (argc > 3 && std::string(argv[3]) == "-f" ? mode::force : mode::error);
		_hours = 0; //hours doesn't mean anything on this mode
	}
	else if (argc >= 5 && std::string(argv[1]) == "-o")
	{		
		std::cout << "\nin -0\n";
		_main_mode = settings::mode::old;
		_sub_mode = (std::string(argv[2]) == "-a" ? mode::access : (std::string(argv[2]) == "-w" ? mode::write : mode::error));

		_hours = std::atoi(argv[3]); //return of 0 indicates failure
		_path = sfu::check_given_dir(argv[4]);

		if (_sub_mode == mode::error || _hours <= 0) { _main_mode = mode::error; }
		_force = (argc >= 6 && std::string(argv[5]) == "-f" ? mode::force : mode::error);
	}
}
}//namespace sfu