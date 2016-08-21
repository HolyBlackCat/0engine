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

    while (1)
    {
        Sys::BeginFrame();
        Sys::Tick();
        Sys::EndFrame();
    }

    Sys::Exit();
}