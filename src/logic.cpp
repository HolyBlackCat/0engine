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

struct S
{
    Reflectable(S)

    Reflect
    (
        (int , x)
        (private:)
        (float , y , =1.23)
    )
};

void Boot()
{
    MarkLocation("Boot");

    S s;
    s.x = 42;

    Reflection(s).for_each(
        [](auto ref)
        {
            std::cout << ref.type_name << " " << ref.name << " = " << ref.value << '\n';
        }
    );

    while (1)
    {
        Sys::BeginFrame();

        Sys::Tick();

        Sys::EndFrame();
    }
}
