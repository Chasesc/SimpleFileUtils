/*
Functions for removing old files in a directory.
Old files are defined in the in the settings class via command line arguments.
*/

#ifndef SFU_OLDREMOVER_HPP
#define SFU_OLDREMOVER_HPP

#include "BoostCore.hpp"
#include "Settings.hpp"
#include "Util.hpp"

#include <vector>
#include <string>


namespace sfu
{
	//returns true if the function deletes any files, false otherwise
	bool remove_old_files(const std::vector<fs::path> &files, const sfu::settings &settings);

	std::vector<fs::path> get_old_files(const std::vector<fs::path> &files, const sfu::settings &settings);

} //namespace sfu

#endif //SFU_OLDREMOVER_HPP