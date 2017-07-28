#include "master.h"

#include <random>

void Boot();
void Menu();

static constexpr ivec2 screen_size = {480,270};

void PreInit()
{
    Window::Init::Size(screen_size*2);
    Window::Init::MinimalSize(screen_size);
    Window::Init::Resizable(1);
    Sys::SetCurrentFunction(Boot);
}

namespace Fonts
{
    Graphics::Font main_font;
    Graphics::FontData main;
}

namespace Draw
{
    Renderer2D *renderer;
    Graphics::Texture *texture;
    Graphics::Framebuffer *framebuffer;
    Graphics::Texture *framebuffer_tex;

    Utils::TickStabilizer ts(60);

    float scale;
    int scale_floor;

    namespace Shaders
    {
        namespace Src
        {
            Graphics::ShaderSource post
{
    {"a_pos"},
    {"u_texture"},
R"(#version 330 compatibility
attribute vec2 a_pos;
varying vec2 v_tex_coord;
void main()
{
    gl_Position = vec4(a_pos, 0, 1);
    v_tex_coord = a_pos * 0.5 + 0.5;
})",
R"(#version 330 compatibility
uniform sampler2D u_texture;
varying vec2 v_tex_coord;
void main()
{
    gl_FragColor = texture2D(u_texture, v_tex_coord);
})"
};
        }

        Graphics::Shader *post;
    }

    void FullscreenTriangle()
    {
        static Graphics::SizedVertexArray<Graphics::VertexFormat<fvec2>> buffer({{{-3,-2}},{{0,3}},{{3,-2}}});
        buffer.Draw();
    }
}


void Resize()
{
    Draw::scale = (Window::Size() / fvec2(screen_size)).min();
    Draw::scale_floor = iround(floor(Draw::scale));
    Draw::framebuffer_tex->SetData(screen_size * Draw::scale_floor);
    Draw::renderer->UpdateMouseMapping(Draw::scale);
}

void Boot()
{
    MarkLocation("Boot");

    auto image = Graphics::ImageData::FromPNG("tex.png");

    Fonts::main_font.Open("assets/font.ttf", 15);
    Fonts::main_font.SetHinting(Graphics::Font::Hinting::light);
    Fonts::main_font.ExportGlyphs(image, Fonts::main, {0,0}, {512,256}, Utils::Encodings::cp1251());

    Draw::texture = new Graphics::Texture(image);
    Draw::texture->LinearInterpolation(0);

    Draw::renderer = new Renderer2D(screen_size);
    Draw::renderer->SetTexture(*Draw::texture);
    Draw::renderer->SetDefaultFont(Fonts::main);
    Graphics::Blend::Enable();
    Draw::renderer->SetBlendingMode();

    Draw::framebuffer_tex = new Graphics::Texture;
    Draw::framebuffer_tex->LinearInterpolation(1);
    Draw::framebuffer = new Graphics::Framebuffer;
    Draw::framebuffer->BindDrawAndAttach(*Draw::framebuffer_tex);

    Draw::Shaders::post = new Graphics::Shader("Postprocessing", Draw::Shaders::Src::post);
    Draw::Shaders::post->SetUniform<Graphics::Texture>(0, *Draw::framebuffer_tex);

    Sys::SetCurrentFunction(Menu);
}

void Menu()
{
    auto &r = *Draw::renderer;

    auto Tick = [&]
    {

    };

    auto Render = [&]
    {
        r.Text(Input::MousePos(), "Hello!").color({0,1,0});
    };

    while (1)
    {
        Sys::BeginFrame();

        while (Draw::ts.Tick())
        {
            Sys::Tick();
            Tick();
        }

        Draw::framebuffer->BindDraw();
        Draw::renderer->EnableShader();
        Graphics::ViewportObj(*Draw::framebuffer_tex);
        Graphics::Clear();
        Render();
        r.Flush();
        Graphics::Framebuffer::UnbindDraw();
        Draw::Shaders::post->Use();
        Graphics::Viewport(iround(Window::Size() / 2.f - screen_size * Draw::scale / 2.f), screen_size * Draw::scale);
        Graphics::Clear();
        Draw::FullscreenTriangle();

        Sys::EndFrame();
    }
}
