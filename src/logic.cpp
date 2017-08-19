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
    struct B
    {
        struct C
        {
            Reflectable(C)

            Reflect
            (
                (int)(meh),
            )
        };

        Reflectable(B)

        Reflect
        (
            (C)(c),
            (int)(foo,bar),
        )
    };

    Reflectable(A)

    Reflect
    (
        (B)(b),
        (int)(meow),
        (float)(test),
    )
};

void Boot()
{
    MarkLocation("Boot");


    A a{};

    std::cout << Reflection(&a).to_string();

    while (1)
    {
        Sys::BeginFrame();

        Sys::Tick();

        Sys::EndFrame();
    }
}
