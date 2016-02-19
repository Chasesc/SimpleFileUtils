/*
Contains all of the required includes for boost.  Also creates namespace aliases to save on typing.
*/

#ifndef SFU_BOOSTCORE_HPP
#define SFU_BOOSTCORE_HPP

#include <boost/filesystem.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

namespace sfu
{

	namespace fs = boost::filesystem;
	namespace greg = boost::gregorian;

} //namespace sfu

#endif //SFU_BOOSTCORE_HPP