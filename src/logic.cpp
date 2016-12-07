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

    Renderer2D r({{"1.png", 1}}, {{"f.ttf", Utils::Encodings::cp1251(), Graphics::Font::fancy, 0, {0,0}, {256,256}, 12}});
    r.InitializeState();

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