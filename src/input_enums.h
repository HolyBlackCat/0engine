#ifndef INPUT_ENUMS_H_INCLUDED
#define INPUT_ENUMS_H_INCLUDED

#include "lib/sdl.h"

namespace Input
{
    using KeyID = uint16_t;
    using MouseButtonID = uint8_t;

    /* How to get KeyIDs:
     *  Key<'#'>()          # = A..Z || a..z || 0..9 || one_of( `~!@#$%^&*()-=_+,.<>/?;:'"[]{}\|)
     *  Key_Num<'#'>()      # = 0..9 || one_of(+*-/.,=)
     *  Key_Num_Enter()
     *  Key_F<#>()          # = 1..24
     *  Key_#()             # = one_of(Space,Menu,Esc,Enter,Tab,Backspace,Insert,Delete,Up,Down,Left,Right,PageUp,PageDown,Home,End,CapsLock,ScrollLock,NumLock,PrintScreen,Pause)
     *  Key_#_$()           # = one_of(Alt,Ctrl,Shift,GUI)      $ = one_of(L,R)
     */

    #define LXINTERNAL_S(x, y) template <> constexpr inline KeyID Key<(x)>() {return SDL_SCANCODE_##y;}
    #define LXINTERNAL_SS(x, y, z) LXINTERNAL_S(x, z) LXINTERNAL_S(y, z)
    template <char N> constexpr inline KeyID Key();
    LXINTERNAL_S(' ', SPACE)
    LXINTERNAL_SS('0', ')', 0) //
    LXINTERNAL_SS('1', '!', 1) //
    LXINTERNAL_SS('2', '@', 2) //
    LXINTERNAL_SS('3', '#', 3) //
    LXINTERNAL_SS('4', '$', 4) //
    LXINTERNAL_SS('5', '%', 5)  //
    LXINTERNAL_SS('6', '^', 6)  //
    LXINTERNAL_SS('7', '&', 7)  //
    LXINTERNAL_SS('8', '*', 8)  //
    LXINTERNAL_SS('9', '(', 9)  //
    LXINTERNAL_SS('A', 'a', A) //
    LXINTERNAL_SS('B', 'b', B) //
    LXINTERNAL_SS('C', 'c', C) //
    LXINTERNAL_SS('D', 'd', D) //
    LXINTERNAL_SS('E', 'e', E) //
    LXINTERNAL_SS('F', 'f', F)  //
    LXINTERNAL_SS('G', 'g', G)  //
    LXINTERNAL_SS('H', 'h', H)  //
    LXINTERNAL_SS('I', 'i', I)  //
    LXINTERNAL_SS('J', 'j', J)  //
    LXINTERNAL_SS('K', 'k', K) //
    LXINTERNAL_SS('L', 'l', L) //
    LXINTERNAL_SS('M', 'm', M) //
    LXINTERNAL_SS('N', 'n', N) //
    LXINTERNAL_SS('O', 'o', O) //
    LXINTERNAL_SS('P', 'p', P)  //
    LXINTERNAL_SS('Q', 'q', Q)  //
    LXINTERNAL_SS('R', 'r', R)  //
    LXINTERNAL_SS('S', 's', S)  //
    LXINTERNAL_SS('T', 't', T)  //
    LXINTERNAL_SS('U', 'u', U) //
    LXINTERNAL_SS('V', 'v', V) //
    LXINTERNAL_SS('W', 'w', W) //
    LXINTERNAL_SS('X', 'x', X) //
    LXINTERNAL_SS('Y', 'y', Y) //
    LXINTERNAL_SS('Z', 'z', Z)  //
    LXINTERNAL_SS('\'','"', APOSTROPHE)
    LXINTERNAL_SS(',', '<', COMMA)
    LXINTERNAL_SS('.', '>', PERIOD)
    LXINTERNAL_SS('-', '_', MINUS)
    LXINTERNAL_SS('=', '+', EQUALS)
    LXINTERNAL_SS(';', ':', SEMICOLON)
    LXINTERNAL_SS('/', '?', SLASH)
    LXINTERNAL_SS('[', '{', LEFTBRACKET)
    LXINTERNAL_SS(']', '}', RIGHTBRACKET)
    LXINTERNAL_SS('\\','|', BACKSLASH)
    LXINTERNAL_SS('`', '~', GRAVE)
    #undef LXINTERNAL_S
    #undef LXINTERNAL_SS
    template <char N> constexpr inline KeyID Key_Num();
    #define LXINTERNAL_S(x, y) template <> constexpr inline KeyID Key_Num<(x)>() {return SDL_SCANCODE_KP_##y;}
    LXINTERNAL_S('=', EQUALS)
    LXINTERNAL_S('0', 0)
    LXINTERNAL_S('1', 1)
    LXINTERNAL_S('2', 2)
    LXINTERNAL_S('3', 3)
    LXINTERNAL_S('4', 4)
    LXINTERNAL_S('5', 5)
    LXINTERNAL_S('6', 6)
    LXINTERNAL_S('7', 7)
    LXINTERNAL_S('8', 8)
    LXINTERNAL_S('9', 9)
    LXINTERNAL_S('.', PERIOD)
    LXINTERNAL_S(',', PERIOD)
    LXINTERNAL_S('+', PLUS)
    LXINTERNAL_S('-', MINUS)
    LXINTERNAL_S('*', MULTIPLY)
    LXINTERNAL_S('/', DIVIDE)
    #undef LXINTERNAL_S
    #define LXINTERNAL_F(x) template <> constexpr inline KeyID Key_F<(x)>() {return SDL_SCANCODE_F##x;}
    template <unsigned int N> constexpr inline KeyID Key_F();
    LXINTERNAL_F(1 ) LXINTERNAL_F(2 ) LXINTERNAL_F(3 ) LXINTERNAL_F(4 ) LXINTERNAL_F(5 ) LXINTERNAL_F(6 )
    LXINTERNAL_F(7 ) LXINTERNAL_F(8 ) LXINTERNAL_F(9 ) LXINTERNAL_F(10) LXINTERNAL_F(11) LXINTERNAL_F(12)
    LXINTERNAL_F(13) LXINTERNAL_F(14) LXINTERNAL_F(15) LXINTERNAL_F(16) LXINTERNAL_F(17) LXINTERNAL_F(18)
    LXINTERNAL_F(19) LXINTERNAL_F(20) LXINTERNAL_F(21) LXINTERNAL_F(22) LXINTERNAL_F(23) LXINTERNAL_F(24)
    #undef LXINTERNAL_F
    #define LXINTERNAL_C(x, y) constexpr inline KeyID Key_##x() {return SDL_SCANCODE_##y;}
    LXINTERNAL_C(Num_Enter, KP_ENTER)
    LXINTERNAL_C(Menu, MENU)
    LXINTERNAL_C(Esc, ESCAPE)
    LXINTERNAL_C(Enter, RETURN)
    LXINTERNAL_C(Tab, TAB)
    LXINTERNAL_C(Backspace, BACKSPACE)
    LXINTERNAL_C(Insert, INSERT)
    LXINTERNAL_C(Delete, DELETE)
    LXINTERNAL_C(Up, UP)
    LXINTERNAL_C(Down, DOWN)
    LXINTERNAL_C(Left, LEFT)
    LXINTERNAL_C(Right, RIGHT)
    LXINTERNAL_C(PageUp, PAGEUP)
    LXINTERNAL_C(PageDown, PAGEDOWN)
    LXINTERNAL_C(Home, HOME)
    LXINTERNAL_C(End, END)
    LXINTERNAL_C(CapsLock, CAPSLOCK)
    LXINTERNAL_C(ScrollLock, SCROLLLOCK)
    LXINTERNAL_C(NumLock, NUMLOCKCLEAR)
    LXINTERNAL_C(PrintScreen, PRINTSCREEN)
    LXINTERNAL_C(Pause, PAUSE)
    LXINTERNAL_C(Space, SPACE)
    #define LXINTERNAL_CMOD(x, y) LXINTERNAL_C(x##_L, L##y) LXINTERNAL_C(x##_R, R##y)
    LXINTERNAL_CMOD(Alt, ALT)
    LXINTERNAL_CMOD(Ctrl, CTRL)
    LXINTERNAL_CMOD(Shift, SHIFT)
    LXINTERNAL_CMOD(GUI, GUI)
    #undef LXINTERNAL_CMOD
    #undef LXINTERNAL_C
}

#endif