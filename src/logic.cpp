#include "master.h"

void Boot();

void PreInit()
{
    Sys::SetCurrentFunction(Boot);
}

void Resize()
{
    Graphics::ViewportFullscreen();
}

void Boot()
{
    MarkLocation("Boot");

    #error use new exceptions!

    while (1)
    {
        Sys::BeginFrame();
        Sys::Tick();
        float f = std::min(Sys::FrameCounter() % 121, 120 - Sys::FrameCounter() % 121) / 60.f;
        glClearColor(0, f/2, f, 1);
        Sys::EndFrame();
    }

    Sys::Exit();
}