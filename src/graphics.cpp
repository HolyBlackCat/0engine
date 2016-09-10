#include "graphics.h"

#include <cstdint>
#include <fstream>

#include "lib_sdlimg.h"
#include "lib_sdlttf.h"
#include "lib_zlib.h"
#include "window.h"

namespace Graphics
{
    static Utils::PoolManager<int> texture_pool_2d,
                                   texture_pool_cubemap;

    static bool sdl_image_init_ok = 0, sdl_ttf_init_ok = 0;

    static bool depth_test = 0;

    void Init()
    {
        texture_pool_2d     .Resize(Sys::Config::opengl_max_texture_count);
        texture_pool_cubemap.Resize(Sys::Config::opengl_max_texture_count);
        sdl_image_init_ok = (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG);
        if (!sdl_image_init_ok)
            Sys::Error(Jo("SDL image plugin init failed. Error message: `", IMG_GetError(), "`."));
        sdl_ttf_init_ok = TTF_Init() == 0;
        if (!sdl_ttf_init_ok)
            Sys::Error(Jo("SDL ttf plugin init failed. Error message: `", TTF_GetError(), "`."));
    }
    void Cleanup()
    {
        if (sdl_image_init_ok)
            IMG_Quit();
        if (sdl_ttf_init_ok)
            TTF_Quit();
    }
    void BeginFrame()
    {
        Clear();
    }
    void EndFrame()
    {
        SDL_GL_SwapWindow(Window::Handle());
        ForceErrorCheck();
    }

    void ForceErrorCheck()
    {
        std::string glerr;
        bool isglerr = 0;
        while (GLenum err = glGetError())
        {
            isglerr = 1;
            switch (err)
            {
              case GL_INVALID_ENUM:                  glerr += "GL: Invalid enum. ";                  break;
              case GL_INVALID_VALUE:                 glerr += "GL: Invalid value. ";                 break;
              case GL_INVALID_OPERATION:             glerr += "GL: Invalid operation. ";             break;
              case GL_INVALID_FRAMEBUFFER_OPERATION: glerr += "GL: Invalid framebuffer operation. "; break;
              case GL_OUT_OF_MEMORY:                 glerr += "GL: Out of memory. ";                 break;
              #ifdef GL_STACK_UNDERFLOW
              case GL_STACK_UNDERFLOW:               glerr += "GL: Stack underflow. ";               break;
              #endif
              #ifdef GL_STACK_OVERFLOW
              case GL_STACK_OVERFLOW:                glerr += "GL: Stack overflow. ";                break;
              #endif
              default:                               glerr += "GL: Unknown error. ";                 break;
            }
        }
        if (isglerr)
            Sys::Error(glerr.c_str());
    }

    namespace Attribs
    {
        static uint64_t status = 0;
        uint64_t Status()
        {
            return status;
        }
        void SetStatus(uint64_t new_status)
        {
            uint64_t old_status = status;
            status = new_status;
            for (int i = 0; new_status != old_status; i++)
            {
                if ((old_status ^ new_status) & 1)
                    (new_status & 1 ? glEnableVertexAttribArray : glDisableVertexAttribArray)(i);

                old_status >>= 1;
                new_status >>= 1;
            }
        }
        void Enable(unsigned int num)
        {
            if (num >= 64)
                Sys::Error(Jo("Attribute number is out of range. Must be not larger than 63, but ", num, " is used."));

            if (((status >> num) & 1) == 1)
                return;
            glEnableVertexAttribArray(num);
            status |= 1 << num;
        }
        void Disable(unsigned int num)
        {
            if (num >= 64)
                Sys::Error(Jo("Attribute number is out of range. Must be not larger than 63, but ", num, " is used."));

            if (((status >> num) & 1) == 0)
                return;
            glDisableVertexAttribArray(num);
            status &= ~(uint64_t)(1 << num);
        }
    }

    GLuint InternalState::vbo_binding = 0;
    bool InternalState::vbo_attribs_configured = 0;


    void Depth(bool on)
    {
        if (on == depth_test)
            return;
        depth_test = on;
        (on ? glEnable : glDisable)(GL_DEPTH_TEST);
    }

    void Clear()
    {
        glClear(depth_test ? GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT : GL_COLOR_BUFFER_BIT);
    }

    void ImageData::LoadTGA(Utils::BinaryInput io, Mirror mirror)
    {
        Clear();

        auto ParseError = [&](const char *txt){Exceptions::IO::CantParse(io.Name(), txt);};

        uint8_t id_field_len, tmp;

        io.ReadEx(id_field_len);                                                                                             // 00
        io.ReadEx(tmp); if (tmp != 0x00) ParseError("Files with colormaps are not supported.");                              // 01
        io.ReadEx(tmp); if (tmp != 0x02) ParseError("File must uncompressed 32 bpp TrueColor image (type check failure).");  // 02 - Sic! 0x02 instead of 0x00.
        io.ReadEx(tmp); if (tmp != 0x00) ParseError("Files with colormaps are not supported (1).");                          // 03
        io.ReadEx(tmp); if (tmp != 0x00) ParseError("Files with colormaps are not supported (2).");                          // 04
        io.ReadEx(tmp); if (tmp != 0x00) ParseError("Files with colormaps are not supported (3).");                          // 05
        io.ReadEx(tmp); if (tmp != 0x00) ParseError("Files with colormaps are not supported (4).");                          // 06
        io.ReadEx(tmp); if (tmp != 0x00) ParseError("Files with colormaps are not supported (5).");                          // 07
        io.SeekRel(4);                                                                                                       // 08
                                                                                                                             // 09
                                                                                                                             // 0a
                                                                                                                             // 0b
        io.ReadEx(tmp); size.x = tmp;                                                                                        // 0c
        io.ReadEx(tmp); size.x |= tmp << 8;                                                                                  // 0d
        io.ReadEx(tmp); size.y = tmp;                                                                                        // 0e
        io.ReadEx(tmp); size.y |= tmp << 8;                                                                                  // 0f
        io.ReadEx(tmp); if (tmp != 0x20) ParseError("File must uncompressed 32 bpp TrueColor image (bpp check failure).");   // 10
        io.ReadEx(tmp); if ((tmp&15)!=8) ParseError("File must uncompressed 32 bpp TrueColor image (alpha check failure)."); // 11

        // Sic! != vs == on purpose.
        bool swap_x = (tmp & 0b00010000) != ((int)mirror & (int)Mirror::x),
             swap_y = (tmp & 0b00100000) == ((int)mirror & (int)Mirror::y);

        io.SeekRel(id_field_len);

        data.Alloc(size.product());
        int x, y, xend, yend, xstep, ystep, xbegin;

        if (!swap_x)
        {
            xbegin = 0;
            xend = size.x;
            xstep = 1;
        }
        else
        {
            xbegin = size.x - 1;
            xend = -1;
            xstep = -1;
        }
        if (!swap_y)
        {
            y = 0;
            yend = size.y;
            ystep = 1;
        }
        else
        {
            y = size.y - 1;
            yend = -1;
            ystep = -1;
        }


        while (y != yend)
        {
            x = xbegin;
            while (x != xend)
            {
                auto &ref = At(ivec2(x, y));
                io.ReadEx(ref.b);
                io.ReadEx(ref.g);
                io.ReadEx(ref.r);
                io.ReadEx(ref.a);
                x += xstep;
            }
            y += ystep;
        }
    }

    void ImageData::SaveTGA(Utils::BinaryOutput io, Mirror mirror)
    {
        auto Byte = [&](uint8_t byte){io.WriteEx(byte);};
        auto Zero = [&](unsigned int len){while (len--) Byte(0x00);};
        Zero(2);
        Byte(0x02);
        Zero(9);
        Byte(size.x & 0xff);
        Byte((size.x >> 8) & 0xff);
        Byte(size.y & 0xff);
        Byte((size.y >> 8) & 0xff);
        Byte(0x20);
        Byte(0b00101000);

        int x, y, xend, yend, xstep, ystep, xbegin;

        if (((int)mirror & (int)Mirror::x) == 0)
        {
            xbegin = 0;
            xend = size.x;
            xstep = 1;
        }
        else
        {
            xbegin = size.x - 1;
            xend = -1;
            xstep = -1;
        }
        if (((int)mirror & (int)Mirror::y) == 0)
        {
            y = 0;
            yend = size.y;
            ystep = 1;
        }
        else
        {
            y = size.y - 1;
            yend = -1;
            ystep = -1;
        }


        while (y != yend)
        {
            x = xbegin;
            while (x != xend)
            {
                const auto &ref = At(ivec2(x, y));
                Byte(ref.b);
                Byte(ref.g);
                Byte(ref.r);
                Byte(ref.a);
                x += xstep;
            }
            y += ystep;
        }
    }

    void ImageData::LoadCompressed(Utils::BinaryInput io)
    {
        Clear();

        auto ParseError = [&](const char *txt){Exceptions::IO::CantParse(io.Name(), txt);};

        unsigned char tmp;

        io.ReadEx(tmp); if (tmp != '|')  ParseError("Magic number is missing.");
        io.ReadEx(tmp); if (tmp != '*')  ParseError("Magic number is missing.");
        io.ReadEx(tmp); if (tmp != '|' ) ParseError("Magic number is missing.");
        io.ReadEx(tmp); if (tmp != '\0') ParseError("Magic number is missing.");

        io.ReadEx(tmp); size.x = tmp;
        io.ReadEx(tmp); size.x |= tmp << 8;
        io.ReadEx(tmp); size.y = tmp;
        io.ReadEx(tmp); size.y |= tmp << 8;
        uint32_t len;
        io.ReadEx(tmp); len = tmp;
        io.ReadEx(tmp); len |= tmp << 8;
        io.ReadEx(tmp); len |= tmp << 16;
        io.ReadEx(tmp); len |= tmp << 24;
        Utils::Array<char> buf(len);
        data.Alloc(size.product());
        io.ReadEx((char *)buf, len);
        uLongf dstlen = ByteSize();
        uncompress((unsigned char *)&*data, &dstlen, (unsigned char *)(char *)buf, len);
    }

    void ImageData::SaveCompressed(Utils::BinaryOutput io)
    {
        auto Byte = [&](uint8_t byte){io.WriteEx(byte);};
        auto Uint32 = [&](uint32_t x){Byte(x & 0xff); Byte((x >> 8) & 0xff); Byte((x >> 16) & 0xff); Byte((x >> 24) & 0xff);};

        Byte('|');
        Byte('*');
        Byte('|');
        Byte('\0');
        Byte(size.x & 0xff);
        Byte((size.x >> 8) & 0xff);
        Byte(size.y & 0xff);
        Byte((size.y >> 8) & 0xff);
        uLongf len = compressBound(ByteSize());
        Utils::Array<char> buf(len);
        compress((unsigned char *)(char *)buf, &len, (unsigned char *)&*data, ByteSize());
        Uint32(len);
        io.WriteEx((char *)buf, len);
    }

    void ImageData::LoadPNG(Utils::BinaryInput io, Mirror mirror)
    {
        Clear();

        auto ParseError = [&](const char *txt){Exceptions::IO::CantParse(io.Name(), txt);};
        SDL_Surface *source = IMG_LoadPNG_RW((SDL_RWops *)io.RWops());
        if (!source)
            ParseError(FixEdges(IMG_GetError()));
        SDL_Surface *converted = SDL_ConvertSurfaceFormat(source, Utils::big_endian ? SDL_PIXELFORMAT_RGBA8888 : SDL_PIXELFORMAT_ABGR8888, 0);
        SDL_FreeSurface(source);
        if (!converted)
            ParseError("Can't convert the image to a native format.");

        size.x = converted->w;
        size.y = converted->h;

        data.Alloc(size.product());

        int x, y, xend, yend, xstep, ystep, xbegin;

        if (mirror == Mirror::no || mirror == Mirror::y)
        {
            xbegin = 0;
            xend = size.x;
            xstep = 1;
        }
        else
        {
            xbegin = size.x - 1;
            xend = -1;
            xstep = -1;
        }
        if (mirror == Mirror::no || mirror == Mirror::x)
        {
            y = 0;
            yend = size.y;
            ystep = 1;
        }
        else
        {
            y = size.y - 1;
            yend = -1;
            ystep = -1;
        }

        int src_x, src_y = 0;

        while (y != yend)
        {
            x = xbegin;
            src_x = 0;
            while (x != xend)
            {
                At(ivec2(x, y)) = ((u8vec4 *)((char *)converted->pixels + converted->pitch * src_y))[src_x];
                x += xstep;
                src_x++;
            }
            y += ystep;
            src_y++;
        }
        SDL_FreeSurface(converted);
    }

    void ImageData::SavePNG(Utils::BinaryOutput io, Mirror mirror)
    {
        Utils::Array<uint32_t> surface_buf(size.product()); // Surprisingly, SDL_CreateRGBSurfaceFrom does not copy data from passed buffer. It uses it for the surface instead.
        SDL_Surface *surface;
        if (Utils::big_endian)
            surface = SDL_CreateRGBSurfaceFrom(surface_buf, size.x, size.y, 32, size.x*4, 0xff << 8*3, 0xff << 8*2, 0xff << 8*1, 0xff << 8*0);
        else
            surface = SDL_CreateRGBSurfaceFrom(surface_buf, size.x, size.y, 32, size.x*4, 0xff << 8*0, 0xff << 8*1, 0xff << 8*2, 0xff << 8*3);
        if (!surface)
            Sys::Error("Can't create SDL surface");

        int x, y, xend, yend, xstep, ystep, xbegin;

        if (mirror == Mirror::no || mirror == Mirror::y)
        {
            xbegin = 0;
            xend = size.x;
            xstep = 1;
        }
        else
        {
            xbegin = size.x - 1;
            xend = -1;
            xstep = -1;
        }
        if (mirror == Mirror::no || mirror == Mirror::x)
        {
            y = 0;
            yend = size.y;
            ystep = 1;
        }
        else
        {
            y = size.y - 1;
            yend = -1;
            ystep = -1;
        }

        int dst_x, dst_y = 0;

        while (y != yend)
        {
            x = xbegin;
            dst_x = 0;
            while (x != xend)
            {
                ((u8vec4 *)((char *)surface->pixels + surface->pitch * dst_y))[dst_x] = At(ivec2(x, y));
                x += xstep;
                dst_x++;
            }
            y += ystep;
            dst_y++;
        }

        IMG_SavePNG_RW(surface, (SDL_RWops *)io.RWops(), 0);

        SDL_FreeSurface(surface);
    }


    int FontData::Kerning(uint16_t a, uint16_t b) const // This function relies on the original Font object which created the current instance.
    {
        // This was moved into .cpp to avoid a circular dependency.
        return font_ptr->GlyphKerning(a, b);
    }


    Shader::Shader(const char *name, ShaderSource source) // Can throw ShaderCompilationError and ShaderLinkingError. The name is not saved.
    {
        prog = glCreateProgram();
        vsh = glCreateShader(GL_VERTEX_SHADER);
        fsh = glCreateShader(GL_FRAGMENT_SHADER);

        if (!prog)
            Sys::Error("glCreateProgram() failed.");
        if (!(vsh && fsh))
            Sys::Error("glCreateShader() failed.");

        glAttachShader(prog, vsh);
        glAttachShader(prog, fsh);
        glShaderSource(vsh, 1, &source.vertex, 0);
        glShaderSource(fsh, 1, &source.fragment, 0);
        glCompileShader(vsh);
        glCompileShader(fsh);

        GLint vstat, fstat;
        glGetShaderiv(vsh, GL_COMPILE_STATUS, &vstat);
        glGetShaderiv(fsh, GL_COMPILE_STATUS, &fstat);

        if (vstat != GL_TRUE || fstat != GL_TRUE)
        {
            std::string vlog_str, flog_str;
            GLint vlen, flen;
            glGetShaderiv(vsh, GL_INFO_LOG_LENGTH, &vlen);
            glGetShaderiv(fsh, GL_INFO_LOG_LENGTH, &flen);
            if (vlen)
            {
                Utils::Array<char> vlog(vlen);
                glGetShaderInfoLog(vsh, vlen, 0, vlog);
                vlog_str = vlog;
            }
            if (flen)
            {
                Utils::Array<char> flog(flen);
                glGetShaderInfoLog(fsh, flen, 0, flog);
                flog_str = flog;
            }

            Exceptions::Graphics::ShaderCompilationError(name,
                                                                   (vstat == GL_TRUE ? "OK" : "NOT OK"),
                                                                   (fstat == GL_TRUE ? "OK" : "NOT OK"),
                                                                   ('\n'+FixEdges(vlog_str.c_str())),
                                                                   ('\n'+FixEdges(flog_str.c_str())));
        }

        int loc = 0;
        for (const char *it : source.attribs)
        {
            if (it)
                glBindAttribLocation(prog, loc++, it);
        }
        glLinkProgram(prog);
        glGetProgramiv(prog, GL_LINK_STATUS, &vstat);
        if (vstat != GL_TRUE)
        {
            glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &vstat);
            std::string log_str;
            if (vstat)
            {
                Utils::Array<char> log(vstat);
                glGetProgramInfoLog(prog, vstat, 0, log);
                if (log[vstat-2] == '\n')
                    log[vstat-2] = '\0';
                log_str = log;
            }

            Exceptions::Graphics::ShaderLinkingError(name, ('\n'+log_str).c_str());
        }

        loc = 0;
        if (source.uniforms.Size())
        {
            uniform_locs.Alloc(source.uniforms.Size());
            for (const char *it : source.uniforms)
            {
                uniform_locs[loc++] = glGetUniformLocation(prog, it);
            }
        }
    }


    Utils::PoolManager<int> &Texture::GetPool()       {return texture_pool_2d;}
    GLint                    Texture::GetTargetName() {return GL_TEXTURE_2D;}

    Utils::PoolManager<int> &TextureCube::GetPool()       {return texture_pool_cubemap;}
    GLint                    TextureCube::GetTargetName() {return GL_TEXTURE_CUBE_MAP;}

    GLuint Shader::binding = 0;

    GLuint Renderbuffer::binding = 0;

    GLuint Framebuffer::binding_draw = 0;
    ForPC(GLuint Framebuffer::binding_read = 0;)
}