#include "master.h"

void Boot();

void PreInit()
{
    Sys::SetCurrentFunction(Boot);
    Window::Init::Resizable(1);
}

Renderer2D *r = 0;

void Resize()
{
    Graphics::ViewportFullscreen();
    if (r) r->UpdateViewport();
}

void Boot()
{
    MarkLocation("Boot");

    r = new Renderer2D({{"1.png", 1}}, {{"f.ttf", Utils::Encodings::cp1251(), Graphics::Font::fancy, 0, {0,0}, {256,256}, 12}});
    r->InitializeState();
    r->SetMouseMapping();

    while (1)
    {
        Sys::BeginFrame();
        Sys::Tick();
        constexpr int period = 200;
        float f = std::cos(Sys::FrameCounter() % period / float(period) * pi<float>() * 2) * 0.5 + 0.5;
        glClearColor(0, f/2, f, 1);

        r->Rect(Input::MousePos(), {128,64}, {{300,200},{128,64}});
        r->Flush();

        Sys::EndFrame();
    }

    Sys::Exit();
}