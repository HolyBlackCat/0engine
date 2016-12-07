#ifndef RENDERER2D_H_INCLUDED
#define RENDERER2D_H_INCLUDED

#include "graphics.h"
#include "math.h"

class Renderer2D
{
    Utils::Array<Graphics::Texture>  textures;
    Utils::Array<Graphics::Font>     fonts;
    Utils::Array<Graphics::FontData> fonts_data;
    Utils::Object<Graphics::Shader>  primary_shader;

  public:
    //                                          pos    color  texpos factors (color: fixed..texture, alpha: fixed..texture, luminosity)
    using VertexFormat = Graphics::VertexFormat<fvec2, fvec4, fvec2, fvec3>;

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
 {"u_matrix","u_texture"},
ForWindows("#version 330 compatibility")
ForMac("#version 150")
ForMobile("#version 100") R"(
uniform mat4 u_matrix;
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
    v_texpos = a_texpos;
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
})"});
        primary_shader->SetUniform<fmat4>(0, fmat4::identity());
        if (textures.size())
            primary_shader->SetUniform<Graphics::Texture>(1, textures[0]);
    }

    void InitializeState() const
    {
        Graphics::Blend::Enable();
        Graphics::Blend::Presets::FuncNormal_Pre();
    }

    ~Renderer2D()
    {

    }
};

#endif