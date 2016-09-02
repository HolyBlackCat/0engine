#define LXINTERNAL_WINDOW_H_SPECIAL_ACCESS
#define LXINTERNAL_INPUT_H_SPECIAL_ACCESS

#include "window.h"

#include "lib_gl.h"
#include "input.h"
#include "system.h"
#include "utils.h"

void Resize();

namespace Window
{
    static SDL_Window *handle = 0;
    static SDL_GLContext context_handle = 0;
    static ivec2 size;

    static bool resize_needed = 0;
    static ivec2 new_size;

    enum class GlProfile    {core, compat, embedded, dont_care};
    enum class GlAccMode    {dont_care, hard, soft};
    enum class GlCompatMode {dont_care, frw_compat};

    static int gl_major, gl_minor;
    static GlProfile gl_profile;
    static GlAccMode gl_acc;
    static int gl_msaa;
    static GlCompatMode gl_compat;
    static uvec4 gl_bits;
    static int gl_vsync; // -1 = late swap tearing, -2 = don't care. This can be queried at runtime.
    static unsigned int display_num;
    static bool resizable;
    static bool fullscreen; // This serves as a config variable and also is updated at runtime.
    static bool maximized;  // Same as above.

    namespace OpenGL
    {
        int Major() {return gl_major;}
        int Minor() {return gl_minor;}
        bool ES()   {return gl_profile == GlProfile::embedded;}
    }

    static void PrepareVideoSettings(const char *txt, bool custom)
    {
        resizable = Sys::Config::window_resizable;
        fullscreen = Sys::Config::window_fullscreen_at_startup;
        if (fullscreen)
        {
            if (Sys::CommandLineArgs::Check("lxsys-windowed"))
                fullscreen = 0;
        }
        else
        {
            if (Sys::CommandLineArgs::Check("lxsys-fullscreen"))
                fullscreen = 1;
        }

        if (resizable)
        {
            maximized = Sys::Config::window_maximize_at_startup;
            if (maximized)
            {
                if (Sys::CommandLineArgs::Check("lxsys-no-maximize"))
                    maximized = 0;
            }
            else
            {
                if (Sys::CommandLineArgs::Check("lxsys-maximize"))
                    maximized = 1;
            }
        }
        else
            maximized = 0;

        static auto Fail = [=]
        {
            if (custom)
                Sys::Error("Unable to parse OpenGL config.", "Fix command line switches. Use `--help` to get more information.");
            else
                Sys::Error("Unable to parse OpenGL config.");
        };

        const char *display_num_str;
        if (Sys::CommandLineArgs::Check("lxsys-display-num", &display_num_str))
        {
            if (*display_num_str == 0 || *display_num_str < '0' || *display_num_str > '9')
                Fail();
            display_num = 0;
            do
            {
                if (*display_num_str < '0' || *display_num_str > '9')
                    Fail();
                display_num = display_num * 10 + (*display_num_str - '0');
                display_num_str++;
            }
            while (*display_num_str);
        }
        else
            display_num = Sys::Config::window_display_num;

        static auto IsDigit = [&]()->bool{return *txt >= '0' && *txt <= '9';};
        static auto GetDigit = [&]()->int{return *txt - '0';};
        gl_major = 0;
        if (!IsDigit())
            Fail();
        do
        {
            gl_major = gl_major * 10 + GetDigit();
            txt++;
        }
        while (IsDigit());
        if (*(txt++) != '.')
            Fail();
        gl_minor = 0;
        if (!IsDigit())
            Fail();
        do
        {
            gl_minor = gl_minor * 10 + GetDigit();
            txt++;
        }
        while (IsDigit());

        switch (*(txt++))
        {
          case '*':
            gl_profile = GlProfile::core;
            break;
          case 'C':
            gl_profile = GlProfile::compat;
            break;
          case 'E':
            gl_profile = GlProfile::embedded;
            break;
          case 'x':
            gl_profile = GlProfile::dont_care;
            break;
          default:
            Fail();
        }

        switch (*(txt++))
        {
          case '_':
            gl_acc = GlAccMode::dont_care;
            break;
          case 'H':
            gl_acc = GlAccMode::hard;
            break;
          case 'S':
            gl_acc = GlAccMode::soft;
            break;
          default:
            Fail();
        }

        gl_msaa = 0;
        if (!IsDigit())
            Fail();
        do
        {
            gl_msaa = gl_msaa * 10 + GetDigit();
            txt++;
        }
        while (IsDigit());

        if (gl_msaa != 1 && gl_msaa != 2 && gl_msaa != 4 && gl_msaa != 8 && gl_msaa != 16)
            Fail();

        switch (*(txt++))
        {
          case '_':
            gl_compat = GlCompatMode::dont_care;
            break;
          case 'F':
            gl_compat = GlCompatMode::frw_compat;
            break;
          default:
            Fail();
        }

        if (!IsDigit())
            Fail();
        gl_bits.r = GetDigit();
        txt++;
        if (!IsDigit())
            Fail();
        gl_bits.g = GetDigit();
        txt++;
        if (!IsDigit())
            Fail();
        gl_bits.b = GetDigit();
        txt++;
        if (!IsDigit())
            Fail();
        gl_bits.a = GetDigit();
        txt++;
        switch (*(txt++))
        {
          case '_':
            gl_vsync = -2;
            break;
          case '-':
            gl_vsync = 0;
            break;
          case '+':
            gl_vsync = 1;
            break;
          case '*':
            gl_vsync = -1;
            break;
          default:
            Fail();
        }

        if (*txt)
            Fail();
    }

    void Init()
    {
        ExecuteThisOnce();

        { // Input
            MarkLocation("Input");
            Input::Init();
        }

        const char *gl_cfg_str;
        if (Sys::CommandLineArgs::Check("lxsys-opengl-config", &gl_cfg_str))
        {
            PrepareVideoSettings(gl_cfg_str, 1);
        }
        else
        {
            PrepareVideoSettings(Sys::Config::opengl_config.c_str(), 0);
        }

        int flags = SDL_WINDOW_OPENGL;
        if (resizable)
            flags += SDL_WINDOW_RESIZABLE;
        if (fullscreen)
            flags += SDL_WINDOW_FULLSCREEN;
        if (maximized)
            flags += SDL_WINDOW_MAXIMIZED;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor);
        switch (gl_profile)
        {
          case GlProfile::core:
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            break;
          case GlProfile::compat:
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
            break;
          case GlProfile::embedded:
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
            break;
          case GlProfile::dont_care:
            break;
        }
        switch (gl_acc)
        {
          case GlAccMode::hard:
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
            break;
          case GlAccMode::soft:
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 0);
            break;
          case GlAccMode::dont_care:
            break;
        }
        if (gl_msaa != 1)
        {
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, gl_msaa);
        }
        if (gl_compat == GlCompatMode::frw_compat)
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        if (gl_bits.r) SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   gl_bits.r);
        if (gl_bits.g) SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, gl_bits.g);
        if (gl_bits.b) SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  gl_bits.b);
        if (gl_bits.a) SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, gl_bits.a);

        if (resizable && fullscreen)
            size = Window::DisplaySize() - 64;
        else
            size = Sys::Config::window_size;

        static constexpr const char *err_solution = "Update your video drivers or mess with GL setting using command line arguments. (Use `--help` to get a list of them.)\n"
                                                    "If you're using a laptop or have multiple videocards, go to your video driver settings and force it to use best available video card.\n"
                                                    "If all else fails, buy a new videocard or give up.";

        handle = SDL_CreateWindow(Sys::Config::window_name.c_str(),
                                  SDL_WINDOWPOS_CENTERED_DISPLAY(display_num), SDL_WINDOWPOS_CENTERED_DISPLAY(display_num),
                                  size.x, size.y,
                                  flags);
        if (!handle)
            Sys::Error(Jo("Window creation failed. Probably your system, video card or video driver does not support OpenGL ", gl_cfg_str, ". Message: `", SDL_GetError(), "`."), err_solution);

        if (!OnMobile && Sys::Config::window_min_size.any())
            SDL_SetWindowMinimumSize(handle, Sys::Config::window_min_size.x, Sys::Config::window_min_size.y);

        context_handle = SDL_GL_CreateContext(handle);
        if (!context_handle)
            Sys::Error(Jo("OpenGL context creation failed. Probably your system, video card or video driver does not support OpenGL ", gl_cfg_str, ". Message: `", SDL_GetError(), "`."), err_solution);

        #if OnWindows || defined(ASSUME_ANDROID)
        glewExperimental = 1;
        {
            MarkLocation("GLEW");
            if (glewInit() != GLEW_OK)
                Sys::Error("GLEW init failed.");
            while (glGetError()) {} // Skip any errors that can be caused by glewExperimental == 1.
        }
        #endif
        #if OnMobile && !defined(ASSUME_ANDROID)
        GLboolean status = 0;
        glGetBooleanv(GL_SHADER_COMPILER, &status);
        if (!status)
            Sys::Error("This device does not support shader compilation.");
        #endif

        switch (gl_vsync)
        {
          case 0:
            if (SDL_GL_SetSwapInterval(0) != 0)
                SDL_GL_SetSwapInterval(gl_vsync = 1);
            break;
          case 1:
            if (SDL_GL_SetSwapInterval(1) != 0)
                SDL_GL_SetSwapInterval(gl_vsync = 0);
            break;
          case -1:
            if (SDL_GL_SetSwapInterval(-1) != 0)
                if (SDL_GL_SetSwapInterval(gl_vsync = 1) != 0)
                    SDL_GL_SetSwapInterval(gl_vsync = 0);
            break;
          default:
            gl_vsync = SDL_GL_GetSwapInterval();
            if (gl_vsync != 0 && gl_vsync != 1)
                gl_vsync = 0;
            break;
        }

        // Forcing resize event.
        SDL_Event resize_event;
        resize_event.type = SDL_WINDOWEVENT;
        resize_event.window.event = SDL_WINDOWEVENT_SIZE_CHANGED;
        SDL_PushEvent(&resize_event);

        Tick();
    }
    void Cleanup()
    {
        ExecuteThisOnce();

        { // Input cleanup
            MarkLocation("Input");
            Input::Cleanup();
        }

        if (context_handle)
            SDL_GL_DeleteContext(context_handle);
        if (handle)
            SDL_DestroyWindow(handle);
    }

    void Tick()
    {
        Input::PreEventsTick();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
              case SDL_QUIT:
                Sys::RequestExit();
                break;
              case SDL_KEYDOWN:
                if (event.key.repeat == 0)
                    Input::MoveKeyDown(event.key.keysym.scancode);
                break;
              case SDL_KEYUP:
                if (event.key.repeat == 0)
                    Input::MoveKeyUp(event.key.keysym.scancode);
                break;
              case SDL_MOUSEBUTTONDOWN:
                Input::MoveMouseButtonDown(event.button.button);
                break;
              case SDL_MOUSEBUTTONUP:
                Input::MoveMouseButtonUp(event.button.button);
                break;
              case SDL_MOUSEWHEEL:
                Input::MoveMouseWheel({event.wheel.x, event.wheel.y});
                break;
              case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                  case SDL_WINDOWEVENT_SIZE_CHANGED:
                    {
                        ivec2 tmp;
                        SDL_GetWindowSize(handle, &tmp.x, &tmp.y);
                        new_size = tmp;
                    }
                    resize_needed = 1;
                    break;
                  case SDL_WINDOWEVENT_MAXIMIZED:
                    maximized = 1;
                    break;
                  case SDL_WINDOWEVENT_RESTORED:
                    maximized = 0;
                    break;
                }
                break;
              case SDL_APP_TERMINATING: // This is used on mobile only. We want to exit gracefully.
              case SDL_RENDER_DEVICE_RESET: // This means that we've lost our GL context state. It's easier to just exit.
                Sys::Exit();
                break;
              case SDL_KEYMAPCHANGED: // The layout have changed, we need to resize keyboard buffer to avoid any issues.
                Input::ResetKeyboardBuffer();
                break;
            }
        }

        Input::PostEventsTick();

        if (Input::KeyPressed(Sys::Config::window_fullscreen_toggle_key))
        {
            Fullscreen(!fullscreen);
            if (fullscreen == 0 && Sys::Config::window_min_size.any())
                SDL_SetWindowMinimumSize(handle, Sys::Config::window_min_size.x, Sys::Config::window_min_size.y);
        }
    }

    void Update()
    {
        if (resize_needed)
        {
            resize_needed = 0;
            size = new_size;
            ::Resize();
        }
    }

    SDL_Window *Handle() {return handle;}
    SDL_GLContext ContextHandle() {return context_handle;}
    ivec2 Size() {return size;}
    bool Maximized() {return maximized;}

    void Fullscreen(bool on)
    {
        if (on == fullscreen)
            return;

        fullscreen = on;

        if (resizable && on)
        {
            SDL_DisplayMode mode = CurrentDisplayMode();
            size.x = mode.w;
            size.y = mode.h;
            SDL_SetWindowDisplayMode(handle, &mode);
        }

        SDL_SetWindowFullscreen(handle, on ? SDL_WINDOW_FULLSCREEN : 0);
    }

    void SetTitle(const char *txt)
    {
        SDL_SetWindowTitle(handle, txt);
    }
    void Resize(ivec2 new_size)
    {
        size = new_size;
        SDL_SetWindowSize(handle, new_size.x, new_size.y);
    }

    ivec2 DisplaySize(unsigned int num)
    {
        static unsigned int last_num = -1;
        static ivec2 last_size;
        if (num == last_num)
            return last_size;
        SDL_Rect tmp;
        SDL_GetDisplayBounds(num, &tmp);
        last_num = num;
        last_size = {(int)tmp.w, (int)tmp.h};
        return last_size;
    }

    ivec2 CurrentDisplaySize()
    {
        return DisplaySize(CurrentDisplayNum());
    }

    SDL_DisplayMode DisplayMode(unsigned int num)
    {
        static unsigned int last_num = -1;
        static SDL_DisplayMode last_mode;
        if (num == last_num)
            return last_mode;
        SDL_DisplayMode tmp;
        SDL_GetDesktopDisplayMode(num, &tmp);
        last_num = num;
        last_mode = tmp;
        return last_mode;
    }
    SDL_DisplayMode CurrentDisplayMode()
    {
        return DisplayMode(CurrentDisplayNum());
    }
    unsigned int CurrentDisplayNum()
    {
        return SDL_GetWindowDisplayIndex(handle);
    }

    SwapModes SwapMode()
    {
        return (SwapModes)gl_vsync;
    }
}
