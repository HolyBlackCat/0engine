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
        (int)(a,b),
        (int)(c,d)(=42),
        (private:),
        (int)(e)(=9001),
        (public:),
        (float)(f,g,h),
    )
};

void Boot()
{
    MarkLocation("Boot");


    S s;
    s.a = s.b = 1;
    s.f = s.g = s.h = 2;

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
