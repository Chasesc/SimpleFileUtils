/*
Functions for removing duplicate files in a directory.
*/

#ifndef SFU_DUPLICATEREMOVER_HPP
#define SFU_DUPLICATEREMOVER_HPP

#include "BoostCore.hpp"
#include "Util.hpp"
#include "Settings.hpp"

#include <vector>

namespace sfu
{

	//returns true if the function deletes any files, false otherwise
	bool remove_duplicate_files(const std::vector<fs::path> &files, const sfu::settings &settings);

	std::vector<fs::path> get_dupes_from_files(const std::vector<fs::path> &files);

} //namespace sfu

#endif //SFU_DUPLICATEREMOVER_HPP