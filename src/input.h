#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <cstdint>
#include <map>
#include <type_traits>

#include "input_enums.h"
#include "math.h"
#include "utils.h"

namespace Input
{
    #ifdef E0INTERNAL_INPUT_H_SPECIAL_ACCESS
    void Initialize();
    void Cleanup();
    void ResetKeyboardBuffer(); // This is for when keyboard layout changes.
    void MoveKeyDown(int id);
    void MoveKeyUp(int id);
    void MoveMouseButtonDown(int id);
    void MoveMouseButtonUp(int id);
    void MoveMouseWheel(ivec2 shift);
    void PreEventsTick();
    void PostEventsTick();
    #endif

    namespace Init
    {
        void SeparateMouseAndTouch(bool);
    }
                                //                   time -> -> -> -> -> -> -> -> -> ->
    bool KeyDown    (Key id); // 1 if pressed or down   0 1 1 1 0 0 | 0 1 0 0 | 0 0 0 //
    bool KeyPressed (Key id); // 1 if pressed           0 1 0 0 0 0 | 0 1 0 0 | 0 1 0 // ID 0 = dummy.
    bool KeyReleased(Key id); // 1 if up                0 0 0 0 1 0 | 0 0 1 0 | 0 1 0 //
    Key KeyCount(); // Returns an amount of key IDs. Valid IDs are 0 : n-1.
    Key AnyKeyDown    (); //
    Key AnyKeyPressed (); // Return 0 if there is no such key.
    Key AnyKeyReleased(); //
    std::string KeyName(Key id);

    // _Immediate functions work instantly, while treir normal alternatives work after a current tick ends.
    void ShowMouse(bool n);
    void ShowMouseImmediate(bool n);
    void RelativeMouseMode(bool n);
    void RelativeMouseModeImmediate(bool n);
    bool MouseFocus();
    bool KeyboardFocus();
    void SetMouseMapping(ivec2 offset, float scale);
    void ResetMouseMapping();
    ivec2 MousePos();
    ivec2 MousePosDelta();
    ivec2 MouseShift(); // Same as MousePosDelta(), but it ignores mapping and works nice even with relative mode.
    bool MouseInRect(ivec2 pos, ivec2 size);
    bool MouseButtonDown(int id);     //
    bool MouseButtonPressed(int id);  // Work same as Key...() ones. ID 0 = dummy, 1 = left, 2 = middle, 3 = right, ...
    bool MouseButtonReleased(int id); //
    int MouseButtonCount(); // Returns an amount of mouse button IDs. Valid IDs are 1 .. n.
    int AnyMouseButtonDown    (); //
    int AnyMouseButtonPressed (); // Return 0 if there is no key.
    int AnyMouseButtonReleased(); //
    bool MouseWheelUp();    //
    bool MouseWheelDown();  // Opposite directions never return 1 together on same tick.
    bool MouseWheelLeft();  //
    bool MouseWheelRight(); //
    void SetMousePos(ivec2 pos);
    void SetMousePosImmediate(ivec2 pos);
}

#endif
