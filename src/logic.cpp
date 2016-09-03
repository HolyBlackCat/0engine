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
    Graphics::FontData fd;
    Graphics::ImageData img({512,512});
    img.Fill({127,0,63,255});
    uint16_t arr[255];
    for (int i = 0; i < 255; i++)
    {
        arr[i] = i;
    }
    //fnt.RenderGlyphs(fd, img, {1,1}, {509,509}, 'A', Graphics::Font::Quality::fancy, {255,255,255,255});
    fnt.RenderGlyphs(fd, img, {64,32}, {293,256}, arr, Graphics::Font::Quality::fancy, {255,255,255,255});
    std::cout << "Pos: " << fd.Pos('A') << '\n'
              << "Size: " << fd.Size('A') << '\n'
              << "Offset: " << fd.Offset('A') << '\n'
              << "Advance: " << fd.Advance('A') << '\n'
              << "Line skip: " << fd.LineSkip() << '\n'
              << "Height: " << fd.Height() << '\n';
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