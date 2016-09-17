#include <csignal>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

#define LXINTERNAL_WINDOW_H_SPECIAL_ACCESS
#define LXINTERNAL_GRAPHICS_H_SPECIAL_ACCESS
#define LXINTERNAL_AUDIO_H_SPECIAL_ACCESS
#define LXINTERNAL_NETWORK_H_SPECIAL_ACCESS
#define LXINTERNAL_SDL_NO_UNDEF_MAIN

#include "system.h"

#include "audio.h"
#include "graphics.h"
#include "lib_zlib.h"
#include "math.h"
#include "network.h"
#include "window.h"
#include "utils.h"

void PreInit(); // You can't use most engine features here. You may only read args and exit (with or without error) from here.

namespace Sys
{
    /*
    namespace Config
    {
        #define LXINTERNAL_CONFIG(a, b, ...) a b(__VA_ARGS__)
        LXINTERNAL_CONFIG_VARS_SEQ
        #undef LXINTERNAL_CONFIG
    }*/

    static unsigned int argc;
    static char **argv;
    static bool sdl_init_ok = 0;
    static uint64_t desired_tick_len;

    static ExitRequestType::Enum exit_requested = ExitRequestType::no,
                                 exit_request_by_signal_handler = ExitRequestType::no,
                                 exit_request_by_user = ExitRequestType::no;

    namespace Config
    {
        static std::string app_name = "LX Engine",
                           msg_title_info = "",
                           msg_title_warning = "",
                           msg_title_error = "";
        static bool no_cleanup = OnWindows || OnAndroid;
        static int extra_sdl_init_flags = 0;

        void ApplicationName(const char *name)
        {
            app_name = name;
        }

        void MessageNames(const char *info, const char *warning, const char *error)
        {
            msg_title_info = info;
            msg_title_warning = warning;
            msg_title_error = error;
        }

        void NoCleanup(bool nc)
        {
            no_cleanup = nc;
        }

        void ExtraInitFlagsForSDL(int flags)
        {
            extra_sdl_init_flags = flags;
        }
    }

    enum class ErrorType
    {
        sig_segv, sig_ill, sig_fpe,
        terminate, unexpected,
        unknown,
    };

    static void HandleError(ErrorType err)
    {
        switch (err)
        {
            case ErrorType::sig_ill:   Error("Signal: Illegal instruction. (Invalid machine code.)"); return;
            case ErrorType::sig_fpe:   Error("Signal: Floating point exception. (Invalid arithmetic operation.)"); return;
            case ErrorType::sig_segv:  Error("Signal: Segmentation fault. (Invalid memory access.)"); return;
            case ErrorType::terminate: try {throw;} catch (std::exception &e) {Error(Jo("Exception: ", e.what()));}
                                                    catch (const char *e)     {Error(Jo("Exception: \"", e, "\"."));}
                                                    catch (...)               {Error(Jo("Exception: Unknown."));}
                                                    Error("The terminate function was called but no unhandled exception was found."); return;
            case ErrorType::unexpected: try {throw;} catch (std::exception &e) {Error(Jo("Unexpected exception: ", e.what()));}
                                                     catch (const char *e)     {Error(Jo("Unexpected exception: \"", e, "\"."));}
                                                     catch (...)               {Error(Jo("Unexpected exception: Unknown."));}
                                                     Error("The unexpected exception handler was called but no unhandled exception was found."); return;
            default: Error("Unknown. (An unknown error was passed to error handler.)"); return;
        }
    }


    static void SignalHandler(int id)
    {
        switch (id)
        {
            case SIGSEGV: Sys::HandleError(Sys::ErrorType::sig_segv); break;
            case SIGFPE:  Sys::HandleError(Sys::ErrorType::sig_fpe);  break;
            case SIGILL:  Sys::HandleError(Sys::ErrorType::sig_ill);  break;
            case SIGINT:  exit_request_by_signal_handler = ExitRequestType::signal_interrupt;   break;
            case SIGTERM: exit_request_by_signal_handler = ExitRequestType::signal_termination; break;
            case SIGABRT: exit_request_by_signal_handler = ExitRequestType::signal_abort;       break;
            default:      Sys::HandleError(Sys::ErrorType::unknown);  break;
        }
    }

    const char *FileName() {return argv[-1];}

    ExitRequestType::Enum ExitRequested() // Clears the flag when called. If the app gets exit request, you have one tick to handle it or the app will close itself.
    {
        ExitRequestType::Enum ret = exit_requested;
        exit_requested = ExitRequestType::no;
        return ret;
    }

    /*namespace CommandLineArgs
    {
        static std::unordered_map<std::string, std::string> map;
        static std::list<std::string> id_list;

        static void Initialize()
        {
            ExecuteThisOnce();

            auto AddArg = [&](const char *id, const char *text, const char *desc = 0, const char *arg = 0)
            {
                Config::args.push_front({id, text, desc, arg});
                id_list.push_front(id);
            };

            for (const auto &it : Config::args)
            {
                id_list.push_back(it.id);

                static const char *id = "lxsys-";
                int pos = 0;
                while (1)
                {
                    if (!id[pos])
                        Error(Jo("Command line arguments' ids starting with `", id, "` are reserved for future use, thus `", it.id, "` id is illegal."));
                    if (id[pos] != it.id[pos])
                        break;
                    pos++;
                }
            }

            AddArg("lxsys-ignore-al-init-fail", "--ignore-openal-init-failure", "Continue to run even if OpenAL init fails.");
            AddArg("lxsys-openal-show-config",  "--show-openal-config",         "Show default OpenAL config.");
            AddArg("lxsys-openal-config",       "--openal-config=",             "Overwrite OpenAL settings. Example: `44100,31+4`. Format: <frequency>`,`<mono sources>`+`<stereo sources>", "mode");
            AddArg("lxsys-opengl-show-config",  "--show-opengl-config",         "Show default OpenGL config.");
            AddArg("lxsys-opengl-config",       "--opengl-config=",             "Overwrite OpenGL settings. Example: `3.3C_1_0000*`. Format:\n      <major>`.`<minor>{`*`(core)|`C`(compatibility)|`E`(embedded)|`x`(none or don't care)}(profile)"
                                                                        "\n      {`_`(don't care)|`H`(hardware)|`S`(sofware)}<msaa>{`_`(don't care)|`F`(forward compatibility)}<redbits><greenbits><bluebits><alphabits>(0 if you don't care)"
                                                                        "\n      {`_`(don't care)|`-`(no vsync)|`+`(vsync)|`*`(late swap tearing (vsync when last frame was not missed) or just vsync if LST is not supported)}", "mode");
            AddArg("lxsys-display-num",         "--display-num=",               "Force a specific display to use.", "display");
            AddArg("lxsys-no-maximize",         "--no-maximize",                "Don't maximize window at startup.");
            AddArg("lxsys-maximize",            "--maximize",                   "Maximize window at startup.");
            AddArg("lxsys-windowed",            "--windowed",                   "Force windowed mode.");
            AddArg("lxsys-fullscreen",          "--fullscreen",                 "Force fullscreen mode.");
            AddArg("lxsys-help",                "--help",                       "Show this page.");

            for (auto it = Config::args.begin(); it != --Config::args.end(); it++)
            {
                auto jt = it;
                jt++;
                while (jt != Config::args.end())
                {
                    if (!std::strcmp(it->id, jt->id))
                        Error(Jo("Two command line arguments have same id: `", it->id, "`."));
                    if (!std::strcmp(it->text, jt->text))
                        Error(Jo("Two command line arguments have same text: `", it->text, "`."));
                    jt++;
                }
            }

            for (unsigned int i = 0; i < argc; i++)
            {
                for (auto it = Config::args.begin(); it != Config::args.end(); it++)
                {
                    int pos = 0;
                    while (1)
                    {
                        if (it->text[pos] == '\0')
                        {
                            if (argv[i][pos] == '\0' || it->arg_name)
                            {
                                map.insert({it->id, argv[i] + pos});
                                goto next_arg;
                            }
                            else
                                break;
                        }
                        if (it->text[pos] != argv[i][pos])
                            break;
                        pos++;
                    }
                }
                Error(Jo("Invalid command line switch `", argv[i], "`."));
              next_arg:
                ;
            }

            if (Check("lxsys-help"))
            {
                std::string tmp = "Following command line switches can be used:\n\n";
                for (auto it : Config::args)
                {
                    tmp += it.text;
                    if (it.arg_name)
                    {
                        tmp += '<';
                        tmp += it.arg_name;
                        tmp += '>';
                    }
                    tmp += "\n      ";
                    if (it.desc)
                    {
                        tmp += it.desc;
                        tmp += '\n';
                    }
                    else
                        tmp += "(No descrition.)\n";
                }
                Message(tmp.c_str());
                Exit();
            }

            if (Check("lxsys-opengl-show-config"))
            {
                Message(("Default OpenGL config: " + Config::opengl_config).c_str());
                Exit();
            }

            if (Check("lxsys-openal-show-config"))
            {
                Message(("Default OpenAL config: " + Config::openal_config).c_str());
                Exit();
            }

            Config::args.clear();
        }

        unsigned int Count()       {return argc;}
        const char *const *Array() {return argv;}
        const std::unordered_map<std::string, std::string> &Map() {return map;}
        bool Check(const char *name, const char **arg_p)
        {
            auto it = map.find(std::string(name));
            if (it == map.end())
            {
                for (const auto &it : id_list)
                    if (it == name)
                        return 0;
                Error(Jo("Invalid command line argument id `", name, "` was used as an argument for Sys::CommandLineArgs::Check()."));
            }
            if (arg_p)
                *arg_p = it->second.c_str();
            return 1;
        }
    }*/

    namespace Args
    {
        int Count()
        {
            return argc;
        }
        const char *const *Array()
        {
            return argv;
        }

        // Variables

        namespace Internal
        {
            #define ARG(name, type) static bool name;
            LXINTERNAL_BUILTIN_ARGS_LIST
            #undef ARG

            namespace Values
            {
                #define ARG_void(name)
                #define ARG_uint(name) static int name;
                #define ARG(name, type) ARG_##type(name)
                LXINTERNAL_BUILTIN_ARGS_LIST
                #undef ARG_void
                #undef ARG_uint
                #undef ARG
            }
        }

        // Functions

        #define ARG(name, type) bool name() {return Internal::name;}
        LXINTERNAL_BUILTIN_ARGS_LIST
        #undef ARG

        namespace Values
        {
            #define ARG_void(name)
            #define ARG_uint(name) int name() {return Internal::Values::name;}
            #define ARG(name, type) ARG_##type(name)
            LXINTERNAL_BUILTIN_ARGS_LIST
            #undef ARG_void
            #undef ARG_uint
            #undef ARG
        }

        static void Initialize()
        {
            ExecuteThisOnce();

            constexpr auto CheckVoidArg = [](const char *name, const char *str) -> bool
            {
                if (*(str++) != '-' || *(str++) != '-') return 0; // Dupe intended!

                while (1)
                {
                    if (*name != *str)
                    {
                        if (!(*name == '_' && *str == '-'))
                            return 0;
                    }
                    if (*name == '\0')
                        return 1;

                    name++;
                    str++;
                }
            };

            constexpr auto CheckUintArg = [](const char *name, const char *str, int *out) -> bool
            {
                const char *str_copy = str;

                if (*(str++) != '-' || *(str++) != '-') return 0; // Dupe intended!

                while (1)
                {
                    if (*name != *str)
                    {
                        if (*name == '\0')
                        {
                            if (*str == '=')
                            {
                                str++;
                                if (!*str)
                                    Error(Jo("Following command line parameter must have an argument: ", str_copy));
                                *out = std::strtol(str, (char **)&str, 10);
                                if (*str != '\0')
                                    Error(Jo("Unable to parse the argument for the following command line parameter: ", str_copy));
                                if (*out < 0)
                                    Error(Jo("Following command line parameter must have a non-negative argument: ", str_copy));
                                return 1;
                            }
                            else
                                return 0;
                        }
                        else if (!(*name == '_' && *str == '-'))
                            return 0;
                    }
                    if (!*name)
                        Error(Jo("Following command line parameter must have an argument: ", str_copy));

                    name++;
                    str++;
                }
            };

            for (int i = 0; i < Count(); i++)
            {
                #define ARG_void(name) CheckVoidArg(#name, Array()[i])
                #define ARG_uint(name) CheckUintArg(#name, Array()[i], &Internal::Values::name)
                #define ARG(name, type) if (ARG_##type(name)) {Internal::name = 1; continue;}
                LXINTERNAL_BUILTIN_ARGS_LIST
                #undef ARG_void
                #undef ARG_uint
                #undef ARG
                Error(Jo("Invalid command line argument: ", Array()[i], "\nUse --help to get a list of all available arguments."));
            }

            if (help())
            {
                std::string buf = "Available options:\n";
                #define ARG_void
                #define ARG_uint "=<..>"
                #define ARG(name, type) \
                    buf += "--"; \
                    for (char it : #name) \
                    { \
                        switch (it) \
                        { \
                            case '\0': buf += ARG_##type "\n"; break; \
                            case '_': buf += '-'; break; \
                            default: buf += it; break; \
                        } \
                    }
                LXINTERNAL_BUILTIN_ARGS_LIST
                #undef ARG_void
                #undef ARG_uint
                #undef ARG
                Message(buf.c_str());
                Exit();
            }
        }
    }

    void Message(const char *title, const char *text, MessageType type)
    {
        int arr[3] {SDL_MESSAGEBOX_INFORMATION, SDL_MESSAGEBOX_WARNING, SDL_MESSAGEBOX_ERROR};
        SDL_ShowSimpleMessageBox(arr[(int)type], title, text, 0);
    }
    void Message(const char *text, MessageType type)
    {
        switch (type)
        {
          case MessageType::info:
            Message(Config::msg_title_info[0] ? Config::msg_title_info.c_str() : Config::app_name.c_str(), text, type);
            break;
          case MessageType::warning:
            Message(Config::msg_title_warning[0] ? Config::msg_title_warning.c_str() : Jo(Config::app_name, " - Warning"), text, type);
            break;
          case MessageType::error:
            Message(Config::msg_title_error[0] ? Config::msg_title_error.c_str() : Jo(Config::app_name, " - Error"), text, type);
            break;
        }
    }

    static constexpr int code_locations_stack_size = 24;
    static struct {const char *name;} code_locations_stack[code_locations_stack_size];
    static int code_locations_stack_pos = 0;

    CodeLocation::CodeLocation(const char *name)
    {
        if (code_locations_stack_pos < code_locations_stack_size)
            code_locations_stack[code_locations_stack_pos] = {name};
        code_locations_stack_pos++;
    }
    CodeLocation::~CodeLocation()
    {
        if (code_locations_stack_pos == 0)
            Error("Code locations stack underflow.");
        code_locations_stack_pos--;
    }

    static void AppCleanup()
    {
        if (Config::no_cleanup)
            return;

        ExecuteThisOnce();

        MarkLocation("Cleanup");

        { // Network
            MarkLocation("Network");
            Network::Cleanup();
        }

        { // Audio
            MarkLocation("Audio");
            Audio::Cleanup();
        }

        { // Graphics
            MarkLocation("Graphics");
            Graphics::Cleanup();
        }

        { // Window
            MarkLocation("Window");
            Window::Cleanup();
        }

        { // SDL
            MarkLocation("SDL");
            if (sdl_init_ok)
                SDL_Quit();
        }
    }

    [[noreturn]] void Exit()
    {
        AppCleanup();
        std::exit(0);
    }

    void RequestExit()
    {
        exit_request_by_user = ExitRequestType::self;
    }

    [[noreturn]] void Error(const char *text)
    {
        // Recursion breaker.
        static bool started = 0;
        if (started) goto ret;
        started = 1;

        // Removing handlers
        std::signal(SIGSEGV, SIG_DFL);
        std::signal(SIGFPE,  SIG_DFL);
        std::signal(SIGILL,  SIG_DFL);
        std::signal(SIGABRT, SIG_DFL);
        std::signal(SIGINT,  SIG_DFL);
        std::signal(SIGTERM, SIG_DFL);

        if (text)
        {
            std::string locs_list;

            if (code_locations_stack_pos == 0)
            {
                locs_list = "\n    at <global>";
            }
            else
            {
                if (code_locations_stack_pos >= code_locations_stack_size)
                    locs_list = "\n    at ...";
                for (int i = std::min(code_locations_stack_pos, code_locations_stack_size)-1; i >= 0; i--)
                {
                    locs_list += "\n    at ";
                    locs_list += code_locations_stack[i].name;
                }
            }

            Message(Jo("Error: ", text, '\n', locs_list), MessageType::error);
        }

        Exit();
      ret:
        std::exit(0);
    }

    static void AppInit()
    {
        ExecuteThisOnce();
        MarkLocation("Init");

        constexpr int default_fps = 60;

        SetFps(default_fps);

        ::PreInit();

        #if OnMobile && !ASSUME_ANDROID
        Sys::Config::window_fullscreen_at_startup = 1;
        Sys::Config::window_maximize_at_startup = 0;
        Sys::Config::window_fullscreen_toggle_key = 0;
        #endif

        { // Args
            MarkLocation("Args");
            Args::Initialize();
        }

        { // SDL
            MarkLocation("SDL");
            SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");
            if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | Config::extra_sdl_init_flags)) // Returns non-zero int on failure.
            {
                const char *p = SDL_GetError();
                if (!p || !*p)
                    Error("SDL init failed.");
                else
                    Error(Jo("SDL init failed. Error message: `", p, "`."));
            }
            sdl_init_ok = 1;
        }

        { // Window
            MarkLocation("Window");
            Window::Initialize();
        }

        { // Graphics
            MarkLocation("Graphics");
            Graphics::Initialize();
        }

        { // Audio
            MarkLocation("Audio");
            Audio::Initialize();
        }

        { // Network
            MarkLocation("Network");
            Network::Initialize();
        }
    }

    static void (*current_function)() = 0;

    void SetCurrentFunction(void (*ptr)())
    {
        current_function = ptr;
    }

    void (*CurrentFunction())()
    {
        return current_function;
    }

    void SetFps(double fps)
    {
        desired_tick_len = Utils::Clock::SecsToTicks(1.0 / fps);
    }


    static bool new_second;
    static uint64_t last_second = ~(uint64_t)0;

    bool NewSecond()
    {
        return new_second;
    }

    int fps = 0, tps = 0;
    uint64_t frame_counter_at_prev_sec = 0, tick_counter_at_prev_sec = 0;

    int Fps() {return fps;}
    int Tps() {return tps;}


    static uint64_t frame_start_time, frame_delta_ticks;
    static double frame_delta_secs;

    uint64_t FrameStartTime()       {return frame_start_time;}
    double FrameDelta()             {return frame_delta_secs; }
    uint64_t FrameDeltaClockTicks() {return frame_delta_ticks;}

    static uint64_t tick_start_time, tick_delta_ticks;
    static double tick_delta_secs;

    uint64_t TickStartTime()       {return tick_start_time;}
    double TickDelta()             {return tick_delta_secs; }
    uint64_t TickDeltaClockTicks() {return tick_delta_ticks;}


    static uint64_t frame_counter, tick_counter;

    uint64_t FrameCounter() {return frame_counter;}
    uint64_t TickCounter()  {return tick_counter;}

    void BeginFrame()
    {
        frame_start_time = Utils::Clock::Time(); // sic

        MarkLocation("Frame start");

        Window::Update();

        Graphics::BeginFrame();
    }

    void EndFrame()
    {
        MarkLocation("Frame end");
        Graphics::EndFrame();
        Audio::Tick();

        if (Window::SwapMode() == Window::ContextSwapMode::no_vsync)
        {
            uint64_t tick_end = Utils::Clock::Time();
            if (tick_end - frame_start_time < desired_tick_len)
                Utils::Clock::WaitTicks(desired_tick_len - (tick_end - frame_start_time));
        }

        frame_delta_ticks = Utils::Clock::Time() - frame_start_time;
        frame_delta_secs = Utils::Clock::TicksToSecs(frame_delta_ticks);

        frame_counter++;
    }

    void StartTick()
    {
        MarkLocation("Tick");

        tick_start_time = Utils::Clock::Time();

        if (tick_start_time / Utils::Clock::Tps() != last_second)
        {
            last_second = tick_start_time / Utils::Clock::Tps();
            new_second = 1;
        }
        else
            new_second = 0;

        if (new_second)
        {
            fps = frame_counter - frame_counter_at_prev_sec;
            tps = tick_counter - tick_counter_at_prev_sec;
            frame_counter_at_prev_sec = frame_counter;
            tick_counter_at_prev_sec = tick_counter;
        }

        Window::Tick();

        if (exit_requested)
            Exit();

        if (Window::GotExitRequestAtThisTick())
            exit_requested = ExitRequestType::normal;

        if (exit_request_by_user)
        {
            exit_requested = exit_request_by_user;
            exit_request_by_user = ExitRequestType::no;
        }

        if (exit_request_by_signal_handler)
        {
            exit_requested = exit_request_by_signal_handler;
            exit_request_by_signal_handler = ExitRequestType::no;
        }

        tick_counter++;
    }
}

extern "C"
{
    ForPC
    (
        // This makes video drivers use best available videocard for the application.
        __declspec(dllexport) uint32_t NvOptimusEnablement                  = 1; // For Nvidia. Docs suggest that this should have type dword, but I don't want windows headers here.
        __declspec(dllexport) int      AmdPowerXpressRequestHighPerformance = 1; // For Amd.
    )
}

int main(int argc, char **argv)
{
    MarkLocation("Main");

    // Saving args
    Sys::argc = argc - 1;
    Sys::argv = argv + 1;

    // Setting handlers
    std::signal(SIGSEGV, Sys::SignalHandler);
    std::signal(SIGFPE,  Sys::SignalHandler);
    std::signal(SIGILL,  Sys::SignalHandler);
    std::signal(SIGABRT, Sys::SignalHandler);
    std::signal(SIGINT,  Sys::SignalHandler);
    std::signal(SIGTERM, Sys::SignalHandler);

    std::set_terminate([]{Sys::HandleError(Sys::ErrorType::terminate);});
    std::set_unexpected([]{Sys::HandleError(Sys::ErrorType::unexpected);});

    Sys::AppInit();
    {
        MarkLocation("Logic");
        while (Sys::current_function) Sys::current_function();
    }
    Sys::AppCleanup();
    return 0;
}