#ifndef RENDERER2D_H_INCLUDED
#define RENDERER2D_H_INCLUDED

#include "graphics.h"
#include "math.h"

class Renderer2D
{
  public:
    //                                          pos    color  texpos factors (color: fixed..texture, alpha: fixed..texture, luminosity)
    using VertexFormat = Graphics::VertexFormat<fvec2, fvec4, fvec2, fvec3>;

  private:
    float scale = 1;
    ivec2 min_pos, max_pos;
    Utils::Array<Graphics::Texture>  textures;
    Utils::Array<Graphics::Font>     fonts;
    Utils::Array<Graphics::FontData> fonts_data;
    Utils::Object<Graphics::Shader>  primary_shader;
    Utils::Object<Graphics::RenderQueue<VertexFormat,3>> render_queue;

  public:
    Renderer2D(const Renderer2D &) = delete;
    Renderer2D(Renderer2D &&) = delete;
    Renderer2D &operator=(const Renderer2D &) = delete;
    Renderer2D &operator=(Renderer2D &&) = delete;

    struct TextureInfo
    {
        Utils::BinaryInput file;
        bool linear;
    };

    struct FontInfo
    {
        Utils::BinaryInput file;
        Utils::ArrayView<uint16_t> glyphs;
        Graphics::Font::Quality quality;
        int texture;
        ivec2 dst, dstsz;
        int ptsize;
        int index = 0;
        u8vec4 color = {255,255,255,255};
    };

    Renderer2D(Utils::ArrayView<TextureInfo> textures_info, Utils::ArrayView<FontInfo> fonts_info)
    {
        fonts.alloc(fonts_info.size());
        for (std::size_t i = 0; i < fonts_info.size(); i++)
        {
            fonts[i].Open((Utils::BinaryInput &&) fonts_info[i].file, fonts_info[i].ptsize, fonts_info[i].index);
        }

        textures.alloc(textures_info.size());
        fonts_data.alloc(fonts_info.size());
        for (std::size_t i = 0; i < textures_info.size(); i++)
        {
            Graphics::ImageData img = Graphics::ImageData::FromPNG((Utils::BinaryInput &&) textures_info[i].file, Graphics::Mirror::y);
            for (std::size_t j = 0; j < fonts_info.size(); j++)
            {
                if (fonts_info[j].texture != int(i))
                    continue;
                fonts[j].RenderGlyphs(fonts_data[j], img, fonts_info[j].dst, fonts_info[j].dstsz, fonts_info[j].glyphs, fonts_info[j].quality, fonts_info[j].color);
            }
            textures[i].SetData(img);
            textures[i].LinearInterpolation(textures_info[i].linear);
        }

        primary_shader.alloc("Renderer2D primary shader", Graphics::ShaderSource
{{"a_pos","a_color","a_texpos","a_factors"},
 {"u_matrix","u_texture","u_texsize"},
ForWindows("#version 330 compatibility")
ForMac("#version 150")
ForMobile("#version 100") R"(
uniform mat4 u_matrix;
uniform vec2 u_texsize;
attribute vec2 a_pos;
attribute vec4 a_color;
attribute vec2 a_texpos;
attribute vec3 a_factors;
varying vec4 v_color;
varying vec2 v_texpos;
varying vec3 v_factors;
void main()
{
    gl_Position = u_matrix * vec4(a_pos,0,1);
    v_color = a_color;
    v_texpos = a_texpos / u_texsize;
    v_factors = a_factors;

})",
ForWindows("#version 330 compatibility")
ForMac("#version 150")
ForMobile("#version 100\nprecision mediump float;") R"(
uniform sampler2D u_texture;
varying vec4 v_color;
varying vec2 v_texpos;
varying vec3 v_factors;
void main()
{
    vec4 tex_color = texture2D(u_texture, v_texpos);
    gl_FragColor = vec4(mix(v_color.rgb, tex_color.rgb, v_factors.x), mix(v_color.a, tex_color.a, v_factors.y));
    gl_FragColor.rgb *= gl_FragColor.a;
    gl_FragColor.a *= (1 - v_factors.z);
    gl_FragColor = vec4(1,0,0,1);
})"});
        UpdateViewport();
        if (textures.size())
            UseTexture(0);

        render_queue.alloc(0x10000);
    }

    ~Renderer2D() {}

    auto &RenderQueue()
    {
        return *render_queue;
    }
    const auto &RenderQueue() const
    {
        return *render_queue;
    }

    static void InitializeState()
    {
        Graphics::Blend::Enable();
        Graphics::Blend::Presets::FuncNormal_Pre();
    }

    void SetScale(float s)
    {
        scale = s;
    }

    void UpdateViewport()
    {
        min_pos = -(Window::Size() + 1) / 2;
        max_pos = Window::Size() / 2;
        primary_shader->SetUniform<fmat4>(0, fmat4::ortho({min_pos.x * scale, max_pos.y * scale}, {max_pos.x * scale, min_pos.y * scale}, -1, 1));
        min_pos.x = std::lround(std::ceil(min_pos.x * scale));
        min_pos.y = std::lround(std::ceil(min_pos.y * scale));
        max_pos.x = std::lround(std::ceil(max_pos.x * scale));
        max_pos.y = std::lround(std::ceil(max_pos.y * scale));
    }

    void SetMouseMapping() const
    {
        Input::SetMouseMapping(-(Window::Size() + 1) / 2, scale);
    }

    ivec2 MinPos() const
    {
        return min_pos;
    }

    ivec2 MaxPos() const
    {
        return max_pos;
    }

    void UseTexture(int number)
    {
        primary_shader->SetUniform<Graphics::Texture>(1, textures[number]);
        primary_shader->SetUniform<fvec2>(2, textures[number].Size());
    }

    void Flush()
    {
        render_queue->Flush();
    }

    void BindShader()
    {
        primary_shader->Use();
    }

    struct Source
    {
        ivec2 tex_a, tex_b;
        fvec4 color00, color01, color10, color11;
        fvec3 factors00, factors01, factors10, factors11;

        void set_all_colors(fvec4 c)
        {
            color00 = color01 = color10 = color11 = c;
        }
        void set_all_factors(fvec3 f)
        {
            factors00 = factors01 = factors10 = factors11 = f;
        }

        Source()
        {
            tex_a = tex_b = {0,0};
            set_all_colors({0,0,0,1});
            set_all_factors({0,0,0});
        }
        Source(ivec2 src, ivec2 srcsz, float alpha = 1, float luminance = 0)
        {
            tex_a = src;
            tex_b = src+srcsz;
            set_all_colors({0,0,0,0});
            set_all_factors({0, alpha, luminance});
        }
        Source(fvec4 fill_color, float luminance = 1)
        {
            tex_a = tex_b = {0,0};
            set_all_colors(fill_color);
            set_all_factors({0,0,luminance});
        }
        Source(fvec4 c00, fvec4 c10, fvec4 c01, fvec4 c11, float luminance = 0)
        {
            tex_a = tex_b = {0,0};
            color00 = c00;
            color01 = c01;
            color10 = c10;
            color11 = c11;
            factors00 = factors01 = factors10 = factors11 = {0,0,luminance};
        }
        Source(fvec3 mix_color, ivec2 src, ivec2 srcsz, float mix, float alpha = 1, float luminance = 0)
        {
            tex_a = src;
            tex_b = src+srcsz;
            set_all_colors(mix_color.to_vec4().change_a(0));
            set_all_factors({mix, alpha, luminance});
        }
    };

    void Rect(ivec2 dst, ivec2 dstsz, Source src)
    {
        dstsz += dst;
        render_queue->Insert({fvec2(dst.x  , dst.y  ), src.color00, fvec2(src.tex_a.x, src.tex_a.y), src.factors00},
                             {fvec2(dstsz.x, dst.y  ), src.color10, fvec2(src.tex_b.x, src.tex_a.y), src.factors10},
                             {fvec2(dstsz.x, dstsz.y), src.color11, fvec2(src.tex_b.x, src.tex_b.y), src.factors11},
                             {fvec2(dst.x  , dstsz.y), src.color01, fvec2(src.tex_a.x, src.tex_b.y), src.factors01});
    }
};

#endif