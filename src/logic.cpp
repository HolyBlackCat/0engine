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
        (float)(y)(=12.3),
        (fvec3)(v1)(={1,2,3}),
        (fmat3)(v2)(=fmat3::rotate({1,1,1},1)),
    )
};

void Boot()
{
    MarkLocation("Boot");


    A a;

    std::cout << Reflection::to_string_tree(a) << '\n';

    while (1)
    {
        Sys::BeginFrame();

        Sys::Tick();

        Sys::EndFrame();
    }
}
