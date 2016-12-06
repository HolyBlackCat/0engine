#ifndef RENDERER2D_H_INCLUDED
#define RENDERER2D_H_INCLUDED

#include "graphics.h"
#include "math.h"

class Renderer2D
{
    Utils::Array<Graphics::Texture>  textures;
    Utils::Array<Graphics::Font>     fonts;
    Utils::Array<Graphics::FontData> fonts_data;

  public:
    //                                          pos    color  texpos factors (color: fixed..texture, alpha: fixed..texture, luminosity)
    using VertexFormat = Graphics::VertexFormat<fvec2, fvec4, fvec2, fvec3>;

    Renderer2D(const Renderer2D &) = delete;
    Renderer2D(Renderer2D &&) = delete;
    Renderer2D &operator=(const Renderer2D &) = delete;
    Renderer2D &operator=(Renderer2D &&) = delete;

    struct FontInfo
    {
        Utils::BinaryInput fname;
        Graphics::Font::Quality quality;
        int texture;
        ivec2 dst, dstsz;
        int ptsize;
        int index = 0;
    };

    Renderer2D(Utils::ArrayView<Utils::BinaryInput> textures_io, Utils::ArrayView<FontInfo> fonts_info, Utils::ArrayView<uint16_t> codepage)
    {
        fonts.Alloc(fonts_info.size());
        for (std::size_t i = 0; i < fonts_info.size(); i++)
        {
            fonts[i].Open((Utils::BinaryInput &&) fonts_info[i].fname, fonts_info[i].ptsize, fonts_info[i].index);
        }

        textures.Alloc(textures_io.size());
        fonts_data.Alloc(fonts_info.size());
        for (std::size_t i = 0; i < textures_io.size(); i++)
        {
            Graphics::ImageData img = Graphics::ImageData::FromPNG((Utils::BinaryInput &&) textures_io[i], Graphics::Mirror::y);
            for (std::size_t j = 0; j < fonts_info.size(); j++)
            {
                if (fonts_info[j].texture != int(i))
                    continue;
                fonts[j].RenderGlyphs(fonts_data[j], img, fonts_info[j].dst, fonts_info[j].dstsz, codepage, fonts_info[j].quality);
            }
            textures[i].SetData(img);
        }

    }

    ~Renderer2D()
    {

    }
};

#endif