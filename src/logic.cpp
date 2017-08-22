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

struct C
{
    Reflectable(C)
    (
        (int)(foo,bar)(=42),
    )
};

struct B
{
    Reflectable(B)
    (
        (int)(w,h)(=1),
        (C)(c),
    )
};

struct A
{
    Reflectable(A)
    (
        (B)(b),
        (int)(x)(=1),
        (float)(y)(=2),
    )
};

void Boot()
{
    MarkLocation("Boot");


    A a;

    std::cout << "a\n";
    std::cout << Reflection(a).to_string_tree() << '\n' << '\n';
    //std::cout << Reflection((const A &)a).to_string_tree() << '\n';

    while (1)
    {
        Sys::BeginFrame();

        Sys::Tick();

        Sys::EndFrame();
    }
}
