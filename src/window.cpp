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
    static ivec2 size, min_size;
    static bool fullscreen, maximized;
    static bool resizable;

    static bool resize_needed = 0;
    static ivec2 new_size;

    static ContextSwapMode swap_mode;

    static bool got_exit_request_at_this_tick = 0;

    namespace Init
    {
        static std::string name = "LX";
        static ivec2 size(800,600), min_size(800,600);
        static bool resizable = 0;
        static bool fullscreen = 0;
        static bool maximize = 0;

        void Name(const char *txt)
        {
            name = txt;
        }
        void Size(ivec2 sz)
        {
            size = sz;
        }
        void MinimalSize(ivec2 sz)
        {
            min_size = sz;
        }
        void Resizable(bool r)
        {
            resizable = r;
        }
        void Fullscreen(bool f)
        {
            fullscreen = f;
        }
        void Maximize(bool m)
        {
            maximize = m;
        }

        namespace OpenGL
        {
            ForWindows(static int major = 3, minor = 3;)
            ForMac    (static int major = 3, minor = 2;)
            ForMobile (static int major = 2, minor = 0;)
            ForWindows(static ContextProfile profile = ContextProfile::compatibility;)
            ForMac    (static ContextProfile profile = ContextProfile::dont_care;)
            ForMobile (static ContextProfile profile = ContextProfile::es;)
            static ContextAcceleration acceleration = ContextAcceleration::dont_care;
            static int msaa = 0;
            static ContextCompatibility compatibility = ContextCompatibility::dont_care;
            static ivec4 color_bits = {8,8,8,0};
            static ContextSwapMode swap = ContextSwapMode::late_swap_tearing;

            void Version(int maj, int min)
            {
                major = maj;
                minor = min;
            }
            void Profile(ContextProfile p)
            {
                profile = p;
            }
            void Acceleration(ContextAcceleration a)
            {
                acceleration = a;
            }
            void MSAA(int aa)
            {
                msaa = aa;
            }
            void Compatibility(ContextCompatibility c)
            {
                compatibility = c;
            }
            void ColorBits(ivec4 bits)
            {
                color_bits = bits;
            }
            void Vsync(ContextSwapMode s)
            {
                swap = s;
            }
        }
    }

    namespace Config
    {
        static Input::KeyID fullscreen_switch_key = ForPC(Input::Key_F<12>()) ForMobile(0);
        void FullscreenSwitchKey(Input::KeyID id)
        {
            fullscreen_switch_key = id;
        }
    }

    namespace OpenGL
    {
        int Major() {return Init::OpenGL::major;}
        int Minor() {return Init::OpenGL::minor;}
        bool ES()   {return Init::OpenGL::profile == ContextProfile::embedded;}
    }

    /*static void PrepareVideoSettings(const char *txt)
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
            gl_profile = GlProfile::compatibility;
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
    }*/

    void Initialize()
    {
        ExecuteThisOnce();

        { // Input
            MarkLocation("Input");
            Input::Initialize();
        }

        int flags = SDL_WINDOW_OPENGL;
        if (Init::resizable)
            flags |= SDL_WINDOW_RESIZABLE;
        if (Init::fullscreen)
            flags |= SDL_WINDOW_FULLSCREEN;
        if (Init::maximize)
            flags |= SDL_WINDOW_MAXIMIZED;

        fullscreen = Init::fullscreen;
        maximized = Init::maximize;
        resizable = Init::resizable;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, Init::OpenGL::major);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, Init::OpenGL::minor);

        switch (Init::OpenGL::profile)
        {
          case ContextProfile::core:
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            break;
          case ContextProfile::compatibility:
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
            break;
          case ContextProfile::embedded:
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
            break;
          case ContextProfile::dont_care:
            break;
        }
        switch (Init::OpenGL::acceleration)
        {
          case ContextAcceleration::hard:
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
            break;
          case ContextAcceleration::soft:
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 0);
            break;
          case ContextAcceleration::dont_care:
            break;
        }
        if (Init::OpenGL::msaa > 1)
        {
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, Init::OpenGL::msaa);
        }
        if (Init::OpenGL::compatibility == ContextCompatibility::forward)
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        if (Init::OpenGL::color_bits.r) SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   Init::OpenGL::color_bits.r);
        if (Init::OpenGL::color_bits.g) SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, Init::OpenGL::color_bits.g);
        if (Init::OpenGL::color_bits.b) SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  Init::OpenGL::color_bits.b);
        if (Init::OpenGL::color_bits.a) SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, Init::OpenGL::color_bits.a);

        int display;
        if (Sys::Args::display_num())
            display = Sys::Args::Values::display_num();
        else
            display = 0;


        if (Init::resizable && Init::fullscreen)
            size = Window::DisplaySize(display) - 64;
        else
            size = Init::size;

        min_size = Init::min_size;

        auto WindowError = [](const char *base_txt) -> const char *
        {
            const char *profile;
            switch (Init::OpenGL::profile)
            {
                case ContextProfile::core:          profile = " Core profile"; break;
                case ContextProfile::compatibility: profile = " Compatibility profile"; break;
                case ContextProfile::embedded:      profile = " ES"; break;
                default: profile = ""; break;
            }

            const char *acc;
            switch (Init::OpenGL::acceleration)
            {
                case ContextAcceleration::hard: acc = " (hardware)"; break;
                case ContextAcceleration::soft: acc = " (software)"; break;
                default: acc = ""; break;
            }

            const char *forward;
            if (Init::OpenGL::compatibility == ContextCompatibility::forward)
                forward = " (forward compatible)";
            else
                forward = "";

            const char *msaa;
            if (Init::OpenGL::msaa > 1)
                msaa = Jo(" with ", Init::OpenGL::msaa, "x MSAA");
            else
                msaa = "";

            const char *color_bits;
            if (Init::OpenGL::color_bits != ivec4(0,0,0,0))
                color_bits = Jo(" with ", Init::OpenGL::color_bits, " bits per color plane");
            else
                color_bits = "";

            const char *sync;
            switch (Init::OpenGL::swap)
            {
                case ContextSwapMode::vsync:             sync = " with vsync enabled"; break;
                case ContextSwapMode::no_vsync:          sync = " with vsync disabled"; break;
                case ContextSwapMode::late_swap_tearing: sync = " with late swap tearing"; break;
                default: sync = ""; break;
            }


            Sys::Error(Jo(base_txt, " Probably your system, video card or video driver does not support required the OpenGL version or settings.\n"
                          "Following settings were used:\n"
                          "OpenGL ", Init::OpenGL::major, '.', Init::OpenGL::minor, profile, acc, forward, msaa, color_bits, sync, ".\n"
                          "Error message: `", Utils::FixEdges(SDL_GetError()), "`.\n"
                          "Update your video drivers or mess with GL setting using command line arguments. (Use `--help` to get a list of them.)\n"
                          "If you're using a laptop or have multiple videocards, go to your video driver settings and force it to use best available video card.\n"
                          "If all else fails, buy a new videocard or give up."));
        };

        handle = SDL_CreateWindow(Init::name.c_str(),
                                  SDL_WINDOWPOS_CENTERED_DISPLAY(display), SDL_WINDOWPOS_CENTERED_DISPLAY(display),
                                  size.x, size.y,
                                  flags);
        if (!handle)
            WindowError("Window creation failed.");

        if (!OnMobile && Init::min_size.any())
            SDL_SetWindowMinimumSize(handle, Init::min_size.x, Init::min_size.y);

        context_handle = SDL_GL_CreateContext(handle);
        if (!context_handle)
            WindowError("OpenGL context creation failed.");

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

        swap_mode = Init::OpenGL::swap;
        switch (swap_mode)
        {
          case ContextSwapMode::no_vsync:
            if (SDL_GL_SetSwapInterval(0) != 0)
                SDL_GL_SetSwapInterval(1), swap_mode = ContextSwapMode::vsync;
            break;
          case ContextSwapMode::vsync:
            if (SDL_GL_SetSwapInterval(1) != 0)
                SDL_GL_SetSwapInterval(0), swap_mode = ContextSwapMode::no_vsync;
            break;
          case ContextSwapMode::late_swap_tearing:
            if (SDL_GL_SetSwapInterval(-1) != 0)
            {
                swap_mode = ContextSwapMode::vsync;
                if (SDL_GL_SetSwapInterval(1) != 0)
                    SDL_GL_SetSwapInterval(0), swap_mode = ContextSwapMode::no_vsync;
            }
            break;
          default:
            swap_mode = (ContextSwapMode)SDL_GL_GetSwapInterval();
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

    bool GotExitRequestAtThisTick()
    {
        return got_exit_request_at_this_tick;
    }

    void Tick()
    {
        Input::PreEventsTick();

        got_exit_request_at_this_tick = 0;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
              case SDL_QUIT:
                got_exit_request_at_this_tick = 1;
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

        if (Input::KeyPressed(Config::fullscreen_switch_key))
        {
            Fullscreen(!fullscreen);
            if (fullscreen == 0 && min_size.any())
                SDL_SetWindowMinimumSize(handle, min_size.x, min_size.y);
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

    ContextSwapMode SwapMode()
    {
        return (ContextSwapMode)swap_mode;
    }
}
