#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#ifdef UNICODE
#undef UNICODE
#endif

#ifdef _UNICODE
#undef _UNICODE
#endif

/* STD includes. **************************************************************/
#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <assert.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#ifdef __unix
#include <tr1/memory>
#endif

namespace fby
{
/** @enum RetFlag
 *
 * @brief List of general-purpose return flags.
 *
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
enum RetFlag {
    RET_SUCCESS = 0,    /**< Generic success. */
    RET_ERROR,          /**< Generic error. */
    RET_WARNING         /**< Generic warning. */
}; // end enum RetFlag.

} // end namespace fby.

#endif // CORE_TYPES_H
