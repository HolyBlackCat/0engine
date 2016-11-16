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

    namespace Args
    {
        int Count();
        const char *const *Array(); // -1 th item is the executable name.

        #define LXINTERNAL_BUILTIN_ARGS_LIST \
            ARG( help                       , void   ) \
            ARG( display_num                , int    ) \
            ARG( opengl_version             , ivec2  ) \
            ARG( opengl_profile             , string ) \
            ARG( msaa                       , int    ) \
            ARG( color_bits                 , ivec4  ) \
            ARG( depth_bits                 , int    ) \
            ARG( stencil_bits               , int    ) \
            ARG( swap_mode                  , string ) \
            ARG( opengl_frw_compat          , bool   ) \
            ARG( opengl_acceleration        , string ) \
            ARG( fullscreen                 , bool   ) \
            ARG( maximized                  , bool   ) \
            ARG( audio_freq                 , int    ) \
            ARG( audio_mono_stereo_srcs     , ivec2  ) \
            ARG( ignore_openal_init_failure , void   ) \

        // Functions

        #define ARG(name, type) bool name();
        LXINTERNAL_BUILTIN_ARGS_LIST
        #undef ARG

        namespace Values
        {
            using std::string;
            #define ARG(name, type) type name();
            LXINTERNAL_BUILTIN_ARGS_LIST
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
    void Tick();
}

#endif