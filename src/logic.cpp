#include "master.h"

void Boot();

static constexpr ivec2 screen_size = {480,270};

void PreInit()
{
    Window::Init::Size(screen_size*2);
    Window::Init::MinimalSize(screen_size);
    Window::Init::Resizable(1);
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
}
