#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#include "lib_sdlnet.h"

namespace Network
{
    #ifdef LXINTERNAL_NETWORK_H_SPECIAL_ACCESS
    void Initialize();
    void Cleanup();
    #endif
}

#endif