#pragma once

#include "../Core/Common.hpp"

namespace BillyEngine {

namespace Key {
using KeyCode = u16;
enum : KeyCode {
    Space = SDL_SCANCODE_SPACE,
    Apostrophe = SDL_SCANCODE_APOSTROPHE, /* ' */
    Comma = SDL_SCANCODE_COMMA,
    Minus = SDL_SCANCODE_MINUS,
    Period = SDL_SCANCODE_PERIOD,
    Slash = SDL_SCANCODE_SLASH,

    D0 = SDL_SCANCODE_0, /* 0 */
    D1 = SDL_SCANCODE_1, /* 1 */
    D2 = SDL_SCANCODE_2, /* 2 */
    D3 = SDL_SCANCODE_3, /* 3 */
    D4 = SDL_SCANCODE_4, /* 4 */
    D5 = SDL_SCANCODE_5, /* 5 */
    D6 = SDL_SCANCODE_6, /* 6 */
    D7 = SDL_SCANCODE_7, /* 7 */
    D8 = SDL_SCANCODE_8, /* 8 */
    D9 = SDL_SCANCODE_9, /* 9 */

    Semicolon = SDL_SCANCODE_SEMICOLON, /* ; */
    Equal = SDL_SCANCODE_EQUALS,        /* = */

    A = SDL_SCANCODE_A,
    B = SDL_SCANCODE_B,
    C = SDL_SCANCODE_C,
    D = SDL_SCANCODE_D,
    E = SDL_SCANCODE_E,
    F = SDL_SCANCODE_F,
    G = SDL_SCANCODE_G,
    H = SDL_SCANCODE_H,
    I = SDL_SCANCODE_I,
    J = SDL_SCANCODE_J,
    K = SDL_SCANCODE_K,
    L = SDL_SCANCODE_L,
    M = SDL_SCANCODE_M,
    N = SDL_SCANCODE_N,
    O = SDL_SCANCODE_O,
    P = SDL_SCANCODE_P,
    Q = SDL_SCANCODE_Q,
    R = SDL_SCANCODE_R,
    S = SDL_SCANCODE_S,
    T = SDL_SCANCODE_T,
    U = SDL_SCANCODE_U,
    V = SDL_SCANCODE_V,
    W = SDL_SCANCODE_W,
    X = SDL_SCANCODE_Z,
    Y = SDL_SCANCODE_Y,
    Z = SDL_SCANCODE_Z,

    LeftBracket = SDL_SCANCODE_LEFTBRACKET,   /* [ */
    Backslash = SDL_SCANCODE_BACKSLASH,       /* \ */
    RightBracket = SDL_SCANCODE_RIGHTBRACKET, /* ] */
    BackQuote = SDL_SCANCODE_GRAVE,           /* ` */

    /* Function keys */
    Escape = SDL_SCANCODE_ESCAPE,
    Return = SDL_SCANCODE_RETURN,
    Tab = SDL_SCANCODE_TAB,
    Backspace = SDL_SCANCODE_BACKSPACE,
    Insert = SDL_SCANCODE_INSERT,
    Delete = SDL_SCANCODE_DELETE,
    RightArrow = SDL_SCANCODE_RIGHT,
    LeftArrow = SDL_SCANCODE_LEFT,
    DownArrow = SDL_SCANCODE_DOWN,
    UpArrow = SDL_SCANCODE_UP,
    PageUp = SDL_SCANCODE_PAGEUP,
    PageDown = SDL_SCANCODE_PAGEDOWN,
    Home = SDL_SCANCODE_HOME,
    End = SDL_SCANCODE_END,
    CapsLock = SDL_SCANCODE_CAPSLOCK,
    ScrollLock = SDL_SCANCODE_SCROLLLOCK,
    NumLock = SDL_SCANCODE_NUMLOCKCLEAR,
    PrintScreen = SDL_SCANCODE_PRINTSCREEN,
    Pause = SDL_SCANCODE_PAUSE,
    F1 = SDL_SCANCODE_F1,
    F2 = SDL_SCANCODE_F2,
    F3 = SDL_SCANCODE_F3,
    F4 = SDL_SCANCODE_F4,
    F5 = SDL_SCANCODE_F5,
    F6 = SDL_SCANCODE_F6,
    F7 = SDL_SCANCODE_F7,
    F8 = SDL_SCANCODE_F8,
    F9 = SDL_SCANCODE_F9,
    F10 = SDL_SCANCODE_F10,
    F11 = SDL_SCANCODE_F11,
    F12 = SDL_SCANCODE_F12,
    F13 = SDL_SCANCODE_F13,
    F14 = SDL_SCANCODE_F14,
    F15 = SDL_SCANCODE_F15,
    F16 = SDL_SCANCODE_F16,
    F17 = SDL_SCANCODE_F17,
    F18 = SDL_SCANCODE_F18,
    F19 = SDL_SCANCODE_F19,
    F20 = SDL_SCANCODE_F20,
    F21 = SDL_SCANCODE_F21,
    F22 = SDL_SCANCODE_F22,
    F23 = SDL_SCANCODE_F23,
    F24 = SDL_SCANCODE_F24,
    // F25 = SDL_SCANCODE_F25,

    /* Keypad */
    KP0 = SDL_SCANCODE_KP_0,
    KP1 = SDL_SCANCODE_KP_1,
    KP2 = SDL_SCANCODE_KP_2,
    KP3 = SDL_SCANCODE_KP_3,
    KP4 = SDL_SCANCODE_KP_4,
    KP5 = SDL_SCANCODE_KP_5,
    KP6 = SDL_SCANCODE_KP_6,
    KP7 = SDL_SCANCODE_KP_7,
    KP8 = SDL_SCANCODE_KP_8,
    KP9 = SDL_SCANCODE_KP_9,
    KPDecimal = SDL_SCANCODE_KP_DECIMAL,
    KPDivide = SDL_SCANCODE_KP_DIVIDE,
    KPMultiply = SDL_SCANCODE_KP_MULTIPLY,
    KPSubtract = SDL_SCANCODE_KP_MINUS,
    KPAdd = SDL_SCANCODE_KP_PLUS,
    KPEnter = SDL_SCANCODE_KP_ENTER,
    KPEqual = SDL_SCANCODE_EQUALS,

    Menu = SDL_SCANCODE_MENU,

    // TODO: maybe add some more
};

namespace Mods {
using Mods = u16;
enum : Mods {
    None = 0x0000,
    LeftShift = 0x0001,
    RightShift = 0x0002,
    LeftCtrl = 0x0040,
    RightCtrl = 0x0080,
    LeftAlt = 0x0100,
    RightAlt = 0x0200,
    LeftGUI = 0x0400,
    RightGUI = 0x0800,
    Num = 0x1000,
    Caps = 0x2000,
    Mode = 0x4000,

    Ctrl = KMOD_LCTRL | KMOD_RCTRL,
    Shift = KMOD_LSHIFT | KMOD_RSHIFT,
    Alt = KMOD_LALT | KMOD_RALT,
    GUI = KMOD_LGUI | KMOD_RGUI
};
}  // namespace Mods

}  // namespace Key
}  // namespace BillyEngine