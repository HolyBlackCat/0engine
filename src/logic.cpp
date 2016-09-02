#include "master.h"

void Boot();

void PreInit()
{
    Sys::SetCurrentFunction(Boot);
}

void Resize()
{
    Graphics::ViewportFullscreen();
}

void Boot()
{
    MarkLocation("Boot");

    Graphics::Font fnt("CatClearGothic.ttf", 42);
    Graphics::ImageData img({512,512});
    img.Fill({0,0,0,0});
    uint16_t arr[255];
    for (int i = 0; i < 255; i++)
    {
        arr[i] = i;
    }
    fnt.RenderGlyphs(img, {1,1}, {509,509}, arr, Graphics::Font::Quality::fancy, {0,0,0,255});
    img.SavePNG("1.png");


    while (1)
    {
        Sys::BeginFrame();
        Sys::Tick();
        float f = std::min(Sys::FrameCounter() % 121, 120 - Sys::FrameCounter() % 121) / 60.f;
        glClearColor(0, f/2, f, 1);
        Sys::EndFrame();
    }

    Sys::Exit();
}