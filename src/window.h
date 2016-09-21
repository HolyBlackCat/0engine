#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include "lib_sdl.h"
#include "input.h"
#include "math.h"

namespace Window
{
    #ifdef LXINTERNAL_WINDOW_H_SPECIAL_ACCESS
    void Initialize();
    void Cleanup();
    void Tick();
    void Update();
    bool GotExitRequestAtThisTick();
    #endif
    SDL_Window *Handle();
    SDL_GLContext ContextHandle();
    ivec2 Size();
    bool Maximized();
    void Fullscreen(bool on);
    void SetTitle(const char *txt);
    void Resize(ivec2 new_size);
    ivec2 DisplaySize(int num);
    ivec2 CurrentDisplaySize();
    SDL_DisplayMode DisplayMode(int num);
    SDL_DisplayMode CurrentDisplayMode();
    int CurrentDisplayNum();

    enum class ContextProfile       {dont_care, core, compatibility, embedded};
    enum class ContextAcceleration  {dont_care, hard, soft};
    enum class ContextCompatibility {dont_care, forward};
    enum class ContextSwapMode      {dont_care = -2, no_vsync = 0, vsync = 1, late_swap_tearing = -1};

    namespace Init
    {
        void Name(const char *name);
        void Size(ivec2 sz);
        void MinimalSize(ivec2 sz); // Has no effect on mobile. Set to [0,0] to disable.
        void Resizable(bool r);
        void Fullscreen(bool f);
        void Maximize(bool m);

        namespace OpenGL
        {
            void Version(int major, int minor);
            void Profile(ContextProfile p);
            void Acceleration(ContextAcceleration a);
            void MSAA(int aa);
            void Compatibility(ContextCompatibility c);
            void ColorBits(ivec4 bits);
            void Vsync(ContextSwapMode s);
            void DepthBits(int bits);
            void StencilBits(int bits);
        }
    }

    namespace Config
    {
        void FullscreenSwitchKey(Input::KeyID id); // 0 to disable.
    }

    ContextSwapMode SwapMode();

    namespace OpenGL
    {
        int Major();
        int Minor();
        bool ES();
    }
}

#endif