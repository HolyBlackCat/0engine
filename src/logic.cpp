#include "master.h"

void Boot();

void PreInit()
{
    Sys::SetCurrentFunction(Boot);
    Window::Init::Resizable(1);
}

void Resize()
{
    Graphics::ViewportFullscreen();
}

void Boot()
{
    MarkLocation("Boot");

    imat2 a1(1,2,3,4);
    fmat2 a2(9,8.5,7,6);

    std::cout << max(a1,a2) << '\n';
    std::cout << min(a1,a2) << '\n';

    while (1)
    {
        Sys::BeginFrame();
        Sys::Tick();
        constexpr int period = 200;
        float f = std::cos(Sys::FrameCounter() % period / float(period) * pi<float>() * 2) * 0.5 + 0.5;
        glClearColor(0, f/2, f, 1);
        Sys::EndFrame();
    }

    Sys::Exit();
}