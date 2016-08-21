#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include "lib_sdl.h"
#include "math.h"

namespace Window
{
    #ifdef LXINTERNAL_WINDOW_H_SPECIAL_ACCESS
    void Init();
    void Cleanup();
    void Tick();
    void Update();
    #endif
    SDL_Window *Handle();
    SDL_GLContext ContextHandle();
    ivec2 Size();
    bool Maximized();
    void Fullscreen(bool on);
    void SetTitle(const char *txt);
    void Resize(ivec2 new_size);
    ivec2 DisplaySize(unsigned int num = 0);
    ivec2 CurrentDisplaySize();
    SDL_DisplayMode DisplayMode(unsigned int num = 0);
    SDL_DisplayMode CurrentDisplayMode();
    unsigned int CurrentDisplayNum();

    enum class SwapModes
    {
        no_vsync = 0,           // This is also returned if swap mode is unknown.
        vsync = 1,
        late_swap_tearing = -1, // Usually same as vsync, but when a swap is missed the frame will be sent without any delay.
    };
    SwapModes SwapMode();

    namespace OpenGL
    {
        int Major();
        int Minor();
        bool ES();
    }
}

#endif