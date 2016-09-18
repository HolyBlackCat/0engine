#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <cstdint>
#include <string>
#include <list>
#include <unordered_map>

#include "input_enums.h"
#include "math.h"
#include "os.h"

#define MarkLocation(x) ::Sys::CodeLocation CODE_LOCATION_OBJECT(x)

namespace Sys
{
    namespace Config
    {
        void ApplicationName(const char *name);
        void MessageNames(const char *info, const char *warning, const char *error);
        void NoCleanup(bool nc);
        void ExtraInitFlagsForSDL(int flags);
    }

    #if 0
    namespace Config
    {
        struct ArgData
        {
            const char *id, *text;
            const char *desc, *arg_name; // These may be null. If arg_name is not null, then this switch accepts an argument.
        };

        //                     TYPE                   NAME                            DEFAULT VALUE
        #define LXINTERNAL_CONFIG_VARS_SEQ \
            LXINTERNAL_CONFIG( std::list<ArgData> ,   args                           ,   {}                                       ); \
            LXINTERNAL_CONFIG( std::string        ,   app_name                       ,   "LX Engine"                              ); \
            LXINTERNAL_CONFIG( std::string        ,   msg_def_title_postfix_info     ,   ""                                       ); /* # */\
            LXINTERNAL_CONFIG( std::string        ,   msg_def_title_postfix_warn     ,   " - Warning"                             ); /* # */\
            LXINTERNAL_CONFIG( std::string        ,   msg_def_title_postfix_error    ,   " - Error"                               ); /* # */\
            LXINTERNAL_CONFIG( int                ,   additional_sdl_init_flags      ,   0                                        ); \
            LXINTERNAL_CONFIG( std::string        ,   window_name                    ,   "LX"                                     ); \
            LXINTERNAL_CONFIG( uvec2              ,   window_size                    ,   {800,600}                                ); \
            LXINTERNAL_CONFIG( uvec2              ,   window_min_size                ,   {800,600}                                ); /* Use {0,0} to disable min limit. This is ignored on mobile. */\
            LXINTERNAL_CONFIG( bool               ,   window_resizable               ,   1                                        ); \
            LXINTERNAL_CONFIG( bool               ,   window_fullscreen_at_startup   ,   0                                        ); /* Forced to be 0 on mobile (it would have no effect anyway). */\
            LXINTERNAL_CONFIG( bool               ,   window_maximize_at_startup     ,   0                                        ); /* Forced to be 1 on mobile (it would have no effect anyway). */\
            LXINTERNAL_CONFIG( int                ,   window_display_num             ,   0                                        ); \
            LXINTERNAL_CONFIG( Input::KeyID       ,   window_fullscreen_toggle_key   ,   Input::Key_F<12>()                       ); /* # Set this to 0 to disable switching. Does not work on mobile. */\
            LXINTERNAL_CONFIG( std::string        ,   opengl_config                  ,   ForWindows("3.3C_1_8888*") ForMac("3.2*_1_8888*") ForMobile("2.0E_1_8888*") ); /* See system.cpp:System::CommandLineArgs::Initialize() for description. */\
            LXINTERNAL_CONFIG( unsigned int       ,   opengl_max_texture_count       ,   48                                       ); /* Values larger than 48 may be not supported on some systems. */\
            LXINTERNAL_CONFIG( std::string        ,   openal_config                  ,   ForPC("44100,63+7") ForMobile("44100,31+7")); /* See system.cpp:System::CommandLineArgs::Initialize() for description. */\
            LXINTERNAL_CONFIG( float              ,   openal_default_ref_distance    ,   1                                        ); /* # Distance at which sound volume is 100%. */\
            LXINTERNAL_CONFIG( float              ,   openal_default_max_distance    ,   100                                      ); /* # If distance to a sound is larger that this, sound volume no longer decreases. */\
            LXINTERNAL_CONFIG( float              ,   openal_default_rolloff_factor  ,   1                                        ); /* # How fast sound gets more quiet when distance gets larger. */\
            LXINTERNAL_CONFIG( bool               ,   input_separate_mouse_and_touch ,   0                                        ); /* If set to `false`, mouse will generate fake touch events and vice versa. */\
            LXINTERNAL_CONFIG( bool               ,   no_cleanup                     ,   (OnWindows || OnAndroid ? 1 : 0)         ); /* # If set to `true`, application will clean up nothing on exit (just `std::exit(0)`). */\
        // # - these options can be changed at any time and take an effect immediately.

        #define LXINTERNAL_CONFIG(a, b, ...) extern a b
        LXINTERNAL_CONFIG_VARS_SEQ
        #undef LXINTERNAL_CONFIG
    }
    #endif

    void SetFps(double fps); // It makes sense only when vsync is disabled. Default is 60. This function can be called at any time, even inside of PreInit().

    double FrameDelta(); // Length of last frame in seconds.
    uint64_t FrameDeltaClockTicks(); // Same, but measured in clock ticks.
    double TickDelta(); // Length of last tick in seconds.
    uint64_t TickDeltaClockTicks(); // Same, but measured in clock ticks.

    bool NewSecond(); // Returns 1 once every second.

    int Fps(); // These are updated once every second.
    int Tps();

    uint64_t FrameStartTime(); // Returns time point at which a current frame started.
    uint64_t TickStartTime(); // Returns time point at which a current frame started.

    uint64_t FrameCounter();
    uint64_t TickCounter();

    const char *FileName();

    namespace ExitRequestType
    {
        enum Enum
        {
            no,
            normal,
            self,
            signal_abort,
            signal_interrupt,
            signal_termination,
        };
    }

    ExitRequestType::Enum ExitRequested(); // Clears the flag when called. If the app gets exit request, you have one tick to handle it or the app will close itself.

    /*
    namespace CommandLineArgs
    {
        unsigned int Count();
        const char *const *Array(); // -1 th item is executable name
        const std::unordered_map<std::string, std::string> &Map(); // .first is arg id, .second is argument passed to switch or "" if there is no argument.
        bool Check(const char *name, const char **arg_p = 0);
    }*/

    namespace Args
    {
        int Count();
        const char *const *Array(); // -1 th item is the executable name.

        #define LXINTERNAL_BUILTIN_ARGS_LIST \
            ARG( help                       , void  ) \
            ARG( display_num                , int   ) \
            ARG( opengl_version             , ivec2 ) \
            ARG( msaa                       , int   ) \
            ARG( fullscreen                 , bool  ) \
            ARG( maximized                  , bool  ) \
            ARG( ignore_openal_init_failure , void  ) \

        // Functions

        #define ARG(name, type) bool name();
        LXINTERNAL_BUILTIN_ARGS_LIST
        #undef ARG

        namespace Values
        {
            #define ARG_void(name)
            #define ARG_bool(name)  bool name();
            #define ARG_int(name)   int name();
            #define ARG_ivec2(name) ivec2 name();
            #define ARG(name, type) ARG_##type(name)
            LXINTERNAL_BUILTIN_ARGS_LIST
            #undef ARG_void
            #undef ARG_bool
            #undef ARG_int
            #undef ARG_ivec2
            #undef ARG
        }
    }

    enum class MessageType {info = 0, warning = 1, error = 2};
    void Message(const char *title, const char *text, MessageType type = MessageType::info);
    void Message(const char *text, MessageType type = MessageType::info);

    class CodeLocation final
    {
      public:
        CodeLocation(const char *name); // YOU MUST STORE POINTED MEMORY BY YOURSELF
        CodeLocation(const CodeLocation &) = delete;
        CodeLocation(CodeLocation &&) = delete;
        CodeLocation &operator=(const CodeLocation &) = delete;
        CodeLocation &operator=(CodeLocation &&) = delete;
        ~CodeLocation();
    };

    void RequestExit();
    [[noreturn]] void Exit();
    [[noreturn]] void Error(const char *text); // If text == 0, the app will be closed silently.

    void SetCurrentFunction(void (*ptr)());
    void (*CurrentFunction())();

    void BeginFrame();
    void EndFrame();
    void StartTick();
}

#endif