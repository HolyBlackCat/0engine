#include "utils.h"

namespace Utils
{
    namespace Strings
    {
        namespace Internal
        {
            std::stringstream ss;
            const std::stringstream::fmtflags stdfmt = ss.flags();
        }
    }
}