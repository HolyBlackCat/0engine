#include <bitset>
#include <cstring>

#include "lib/sdl.h"

#define INPUT_H_SPECIAL_ACCESS
#include "input.h"

#include "system.h"
#include "window.h"
#include "utils.h"


namespace Input
{
    static std::bitset<SDL_NUM_SCANCODES> board, board_pr, board_re;
    static Key any_key_down_id, any_key_pr_id, any_key_re_id;
    static ivec2 mouse_pos, mouse_pos_prev, mouse_shift;
    static std::bitset<32> mouse_buttons, mouse_buttons_pr, mouse_buttons_re;
    static int any_button_down_id, any_button_pr_id, any_button_re_id;
    static bool mouse_wheel_up, mouse_wheel_down, mouse_wheel_left, mouse_wheel_right;
    static bool mouse_focus, keyboard_focus;

    static ivec2 mouse_mapping_offset{0,0};
    static float mouse_mapping_scale = 1;

    static bool mmode_show = 1, mmode_show_needed = 1;
    static bool mmode_rel = 0, mmode_rel_needed = 0;
    static bool mouse_movement_needed;
    static ivec2 mouse_movement_dst;

    namespace Init
    {
        bool separate_mouse_and_touch = 0;
        void SeparateMouseAndTouch(bool s) {separate_mouse_and_touch = s;}
    }

    void Initialize()
    {
        ExecuteThisOnce();

        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
        mouse_pos = ((mouse_pos + mouse_mapping_offset) * mouse_mapping_scale).apply((long(*)(double))lround);

        SDL_SetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH, Init::separate_mouse_and_touch ? "1" : "0");
    }
    void Cleanup()
    {
        ExecuteThisOnce();
    }

    bool IsValidKey(int code)
    {
        return code >= 0 && code < int(board.size());
    }
    bool IsValidMouseButton(int code)
    {
        return code >= 0 && code < int(mouse_buttons.size());
    }

    void MoveKeyDown(int id)
    {
        if (!IsValidKey(id))
            return;
        board_pr[id] = 1;
        any_key_pr_id = Input::Key(id);
    }
    void MoveKeyUp(int id)
    {
        if (!IsValidKey(id))
            return;
        board_re[id] = 1;
        any_key_re_id = Input::Key(id);
    }

    void MoveMouseButtonDown(int id)
    {
        if (!IsValidMouseButton(id))
            return;
        mouse_buttons_pr[id] = 1;
        mouse_buttons[id] = 1;
        any_button_pr_id = id;
    }
    void MoveMouseButtonUp(int id)
    {
        if (!IsValidMouseButton(id))
            return;
        mouse_buttons_re[id] = 1;
        mouse_buttons[id] = 0;
        any_button_re_id = id;
    }

    void MoveMouseWheel(ivec2 shift)
    {
        if (shift.x)
            (shift.x > 0 ? mouse_wheel_right : mouse_wheel_left) = 1;
        if (shift.y)
            (shift.y > 0 ? mouse_wheel_up : mouse_wheel_down) = 1;
    }

    void PreEventsTick()
    {
        if (mmode_show != mmode_show_needed)
            SDL_ShowCursor((mmode_show = mmode_show_needed));
        if (mmode_rel != mmode_rel_needed)
            SDL_SetRelativeMouseMode((SDL_bool)(mmode_rel = mmode_rel_needed));
        if (mouse_movement_needed)
        {
            mouse_movement_needed = 0;
            SDL_WarpMouseInWindow(Window::Handle(), mouse_movement_dst.x, mouse_movement_dst.y);
        }

        board_pr.reset();
        board_re.reset();
        any_key_pr_id = (Input::Key)0;
        any_key_re_id = (Input::Key)0;

        mouse_buttons_pr.reset();
        mouse_buttons_re.reset();
        any_button_pr_id = 0;
        any_button_re_id = 0;

        mouse_wheel_up = 0;
        mouse_wheel_down = 0;
        mouse_wheel_left = 0;
        mouse_wheel_right = 0;

        mouse_focus = (SDL_GetMouseFocus() == Window::Handle());
        keyboard_focus = (SDL_GetKeyboardFocus() == Window::Handle());
    }
    void PostEventsTick()
    {
        board |= board_pr;
        board &= ~board_re;

        if (any_key_pr_id || any_key_re_id)
        {
            any_key_down_id = Input::Key(0);
            for (unsigned int i = 1; i < board.size(); i++) // Note the `i = 1`.
            {
                if (board[i])
                {
                    any_key_down_id = Input::Key(i);
                    break;
                }
            }
        }

        mouse_pos_prev = mouse_pos;

        SDL_GetRelativeMouseState(&mouse_shift.x, &mouse_shift.y);
        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

        mouse_pos = ((mouse_pos + mouse_mapping_offset) * mouse_mapping_scale).apply((long(*)(double))lround);

        if (any_button_pr_id || any_button_re_id)
        {
            any_button_down_id = 0;
            for (unsigned int i = 1; i < mouse_buttons.size(); i++) // Note the `i = 1`.
            {
                if (mouse_buttons[i])
                {
                    any_button_down_id = i;
                    break;
                }
            }
        }
    }


    bool KeyDown    (Key id) {Assert("Key ID out of range.", IsValidKey(id)); return board[id];}
    bool KeyPressed (Key id) {Assert("Key ID out of range.", IsValidKey(id)); return board_pr[id];}
    bool KeyReleased(Key id) {Assert("Key ID out of range.", IsValidKey(id)); return board_re[id];}
    int KeyCount() {return board.size();}
    Key AnyKeyDown    () {return any_key_down_id;}
    Key AnyKeyPressed () {return any_key_pr_id;}
    Key AnyKeyReleased() {return any_key_re_id;}

    std::string KeyName(Key id)
    {
        return SDL_GetScancodeName((SDL_Scancode)id);
    }


    void ShowMouse(bool n)
    {
        mmode_show_needed = n;
    }

    void ShowMouseImmediate(bool n)
    {
        SDL_ShowCursor((mmode_show = mmode_show_needed = n));
    }

    void RelativeMouseMode(bool n)
    {
        mmode_rel_needed = n;
    }

    void RelativeMouseModeImmediate(bool n)
    {
        SDL_SetRelativeMouseMode((SDL_bool)(mmode_rel = mmode_rel_needed = n));
    }

    bool MouseFocus()
    {
        return mouse_focus;
    }
    bool KeyboardFocus()
    {
        return keyboard_focus;
    }

    void SetMouseMapping(ivec2 offset, float scale)
    {
        mouse_mapping_offset = offset;
        mouse_mapping_scale = scale;
    }
    void ResetMouseMapping()
    {
        SetMouseMapping({0,0}, 1);
    }

    ivec2 MousePos()
    {
        return mouse_pos;
    }

    ivec2 MousePosDelta()
    {
        return mouse_pos - mouse_pos_prev;
    }

    ivec2 MouseShift()
    {
        return mouse_shift;
    }

    bool MouseInRect(ivec2 pos, ivec2 size) {return mouse_pos >= pos && mouse_pos < pos + size;}

    bool MouseButtonDown    (int id) {Assert("Mouse button ID out of range.", IsValidMouseButton(id)); return mouse_buttons[id];}
    bool MouseButtonPressed (int id) {Assert("Mouse button ID out of range.", IsValidMouseButton(id)); return mouse_buttons_pr[id];}
    bool MouseButtonReleased(int id) {Assert("Mouse button ID out of range.", IsValidMouseButton(id)); return mouse_buttons_re[id];}

    int MouseButtonCount() {return mouse_buttons.size();}
    int AnyMouseButtonDown    () {return any_button_down_id;}
    int AnyMouseButtonPressed () {return any_button_pr_id;}
    int AnyMouseButtonReleased() {return any_button_re_id;}
    bool MouseWheelUp   () {return mouse_wheel_up;}
    bool MouseWheelDown () {return mouse_wheel_down;}
    bool MouseWheelLeft () {return mouse_wheel_left;}
    bool MouseWheelRight() {return mouse_wheel_right;}

    void SetMousePos(ivec2 pos)
    {
        mouse_movement_needed = 1;
        mouse_movement_dst = (pos / mouse_mapping_scale - mouse_mapping_offset).apply((long(*)(double))lround);
    }
    void SetMousePosImmediate(ivec2 pos)
    {
        pos = (pos / mouse_mapping_scale - mouse_mapping_offset).apply((long(*)(double))lround);
        SDL_WarpMouseInWindow(Window::Handle(), pos.x, pos.y);
    }
}
