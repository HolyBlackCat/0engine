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

    fmat3 a1(1,2,3,4,5,6,7,8,9);
    fmat3 a2(9,8,7,6,5,4,3,2,1);

    //std::cout << max(a1,a2) << '\n';
    //std::cout << min(a1,a2) << '\n';
    typename larger_type_t_impl<float, float>::type a;
    static_assert(sizeof a, "");

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