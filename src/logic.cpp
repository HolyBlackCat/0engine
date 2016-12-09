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

    r = new Renderer2D({{"1.png", 0}}, {/*{"f.ttf", Utils::Encodings::cp1251(), Graphics::Font::fancy, 0, {0,0}, {256,256}, 12}*/});
    r->InitializeState();
    r->SetScale(2);
    r->SetMouseMapping();

    while (1)
    {
        Sys::BeginFrame();
        Sys::Tick();
        constexpr int period = 200;
        float f = std::cos(Sys::FrameCounter() % period / float(period) * pi<float>() * 2) * 0.5 + 0.5;
        glClearColor(0, f/2, f, 1);

        r->Rect(Input::MousePos(), {128,64}, {{0,0},{64,32}}, {8,4}, std::atan2(Input::MousePos().y, Input::MousePos().x));
        r->Flush();

        Sys::EndFrame();
    }

    Sys::Exit();
}