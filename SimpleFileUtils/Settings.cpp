#include "settings.hpp"

namespace sfu
{

	const std::string settings::error_string() const
	{
		return "Error: Incorrect or Incomplete arguments supplied.\n"
			   "Please read \"what - is.txt\" for more information.\n";
	}

	//TODO: clean up this constructor
	settings::settings(int argc, char ** argv) : settings::settings()
	{
		//print statements are only for debugging
		std::cout << "Version: " << kVersion << std::endl;
		
		std::cout << "argc: " << argc << std::endl;
		for (int i = 0; i != argc; ++i)
		{
			std::cout << "argv[" << i << "] = \"" << argv[i] << "\"" << std::endl;
		}

		if (argc > 2 && std::string(argv[1]) == "-d") 
		{ 
			std::cout << "\nin -d\n";
			m_main_mode = mode::duplicate;
			m_path = std::string(argv[2]);
			m_force = (argc > 3 && std::string(argv[3]) == "-f") ? mode::force : mode::error;
		}
		else if (argc >= 5 && std::string(argv[1]) == "-o")
		{		
			std::cout << "\nin -0\n";
			m_main_mode = mode::old;
			m_sub_mode = (std::string(argv[2]) == "-a" ? mode::access :
						 (std::string(argv[2]) == "-w" ? mode::write : mode::error));

			m_hours = std::atoi(argv[3]); //return of 0 indicates failure
			m_path = std::string(argv[4]);

			if (m_sub_mode == mode::error || m_hours <= 0) { m_main_mode = mode::error; }
			m_force = (argc >= 6 && std::string(argv[5]) == "-f" ? mode::force : mode::error);
		}
	}

}//namespace sfu