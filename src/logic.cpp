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

struct A
{
    Reflectable(A)

    Reflect
    (
        (fmat3)(m),
        (int)(a)(=1),
        (float)(b)(=2),
    )
};

void Boot()
{
    MarkLocation("Boot");


    A a;
    a.m = fmat3::rotate({1,1,1},1);

    std::cout << Reflection(&a).to_string_pretty();

    while (1)
    {
        Sys::BeginFrame();

        Sys::Tick();

        Sys::EndFrame();
    }
}
