#ifndef INPUT_ENUMS_H_INCLUDED
#define INPUT_ENUMS_H_INCLUDED

#include "lib/sdl.h"

namespace Input
{
    enum Key
    {
        #define KEY(name, sdl_name) name = SDL_SCANCODE_##sdl_name,

        KEY(null         , UNKNOWN     )

        KEY(_0, 0) KEY(_1, 1) KEY(_2, 2) KEY(_3, 3) KEY(_4, 4)
        KEY(_5, 5) KEY(_6, 6) KEY(_7, 7) KEY(_8, 8) KEY(_9, 9)

        KEY(a, A) KEY(b, B) KEY(c, C) KEY(d, D) KEY(e, E)
        KEY(f, F) KEY(g, G) KEY(h, H) KEY(i, I) KEY(j, J)
        KEY(k, K) KEY(l, L) KEY(m, M) KEY(n, N) KEY(o, O)
        KEY(p, P) KEY(q, Q) KEY(r, R) KEY(s, S) KEY(t, T)
        KEY(u, U) KEY(v, V) KEY(w, W) KEY(x, X) KEY(y, Y)
        KEY(z, Z)

        KEY(apostrophe   , APOSTROPHE  )
        KEY(comma        , COMMA       )
        KEY(period       , PERIOD      )
        KEY(minus        , MINUS       )
        KEY(equals       , EQUALS      )
        KEY(semicolon    , SEMICOLON   )
        KEY(slash        , SLASH       )
        KEY(l_bracket    , LEFTBRACKET )
        KEY(r_bracket    , RIGHTBRACKET)
        KEY(backslash    , BACKSLASH   )
        KEY(grave        , GRAVE       )

        KEY(num_0, KP_0) KEY(num_1, KP_1) KEY(num_2, KP_2) KEY(num_3, KP_3) KEY(num_4, KP_4)
        KEY(num_5, KP_5) KEY(num_6, KP_6) KEY(num_7, KP_7) KEY(num_8, KP_8) KEY(num_9, KP_9)

        KEY(num_period   , KP_PERIOD   )
        KEY(num_equals   , KP_EQUALS   )
        KEY(num_enter    , KP_ENTER    )
        KEY(num_plus     , KP_PLUS     )
        KEY(num_minus    , KP_MINUS    )
        KEY(num_multiply , KP_MULTIPLY )
        KEY(num_divide   , KP_DIVIDE   )

        KEY(f1 , F1 ) KEY(f2 , F2 ) KEY(f3 , F3 ) KEY(f4 , F4 ) KEY(f5 , F5 ) KEY(f6 , F6 )
        KEY(f7 , F7 ) KEY(f8 , F8 ) KEY(f9 , F9 ) KEY(f10, F10) KEY(f11, F11) KEY(f12, F12)
        KEY(f13, F13) KEY(f14, F14) KEY(f15, F15) KEY(f16, F16) KEY(f17, F17) KEY(f18, F18)
        KEY(f19, F19) KEY(f20, F20) KEY(f21, F21) KEY(f22, F22) KEY(f23, F23) KEY(f24, F24)

        KEY(menu         , MENU        )
        KEY(escape       , ESCAPE      )
        KEY(enter        , RETURN      )
        KEY(tab          , TAB         )
        KEY(backspace    , BACKSPACE   )
        KEY(insert       , INSERT      )
        KEY(del          , DELETE      )
        KEY(up           , UP          )
        KEY(down         , DOWN        )
        KEY(left         , LEFT        )
        KEY(right        , RIGHT       )
        KEY(page_up      , PAGEUP      )
        KEY(page_down    , PAGEDOWN    )
        KEY(home         , HOME        )
        KEY(end          , END         )
        KEY(caps_lock    , CAPSLOCK    )
        KEY(scroll_lock  , SCROLLLOCK  )
        KEY(num_lock     , NUMLOCKCLEAR)
        KEY(print_screen , PRINTSCREEN )
        KEY(pause        , PAUSE       )
        KEY(space        , SPACE       )

        KEY(l_shift      , LSHIFT      )
        KEY(r_shift      , RSHIFT      )
        KEY(l_ctrl       , LCTRL       )
        KEY(r_ctrl       , RCTRL       )
        KEY(l_alt        , LALT        )
        KEY(r_alt        , RALT        )
        KEY(l_gui        , LGUI        )
        KEY(r_gui        , RGUI        )

        #undef KEY
    };
}

using Input::Key;

#endif
