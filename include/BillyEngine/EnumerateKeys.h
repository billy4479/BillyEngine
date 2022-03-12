#pragma once

// From glfw.h
// Thank you, clang-format...

#define ENUMERATE_KEYS(o)                                                      \
    o(Space, 32) o(Apostrophe, 39) /* ' */                                     \
        o(Comma, 44)               /* )\ */                                    \
        o(Minus, 45)               /* - */                                     \
        o(Period, 46)              /* . */                                     \
        o(Slash, 47)               /* / */                                     \
                                                                               \
        o(D0, 48) /* 0 */                                                      \
        o(D1, 49) /* 1 */                                                      \
        o(D2, 50) /* 2 */                                                      \
        o(D3, 51) /* 3 */                                                      \
        o(D4, 52) /* 4 */                                                      \
        o(D5, 53) /* 5 */                                                      \
        o(D6, 54) /* 6 */                                                      \
        o(D7, 55) /* 7 */                                                      \
        o(D8, 56) /* 8 */                                                      \
        o(D9, 57) /* 9 */                                                      \
                                                                               \
        o(Semicolon, 59) /* ; */                                               \
        o(Equal, 61)     /* , */                                               \
                                                                               \
        o(A, 65) o(B, 66) o(C, 67) o(D, 68) o(E, 69) o(F, 70) o(G, 71)         \
            o(H, 72) o(I, 73) o(J, 74) o(K, 75) o(L, 76) o(M, 77) o(N, 78)     \
                o(O, 79) o(P, 80) o(Q, 81) o(R, 82) o(S, 83) o(T, 84) o(U, 85) \
                    o(V, 86) o(W, 87) o(X, 88) o(Y, 89) o(Z, 90)               \
                                                                               \
                        o(LeftBracket, 91) /* [ */                             \
        o(Backslash, 92)                   /* \ */                             \
        o(RightBracket, 93)                /* ] */                             \
        o(GraveAccent, 96)                 /* ` */                             \
                                                                               \
        o(World1, 161) /* non-US #1 */                                         \
        o(World2, 162) /* non-US #2 */                                         \
                                                                               \
        /* Function keys */                                                    \
        o(Escape, 256) o(Enter, 257) o(Tab, 258) o(Backspace, 259)             \
            o(Insert, 260) o(Delete, 261) o(Right, 262) o(Left, 263)           \
                o(Down, 264) o(Up, 265) o(PageUp, 266) o(PageDown, 267) o(     \
                    Home, 268) o(End, 269) o(CapsLock, 280) o(ScrollLock, 281) \
                    o(NumLock, 282) o(PrintScreen, 283) o(Pause, 284)          \
                        o(F1, 290) o(F2, 291) o(F3, 292) o(F4, 293) o(F5, 294) \
                            o(F6, 295) o(F7, 296) o(F8, 297) o(F9, 298)        \
                                o(F10, 299) o(F11, 300) o(F12, 301)            \
                                    o(F13, 302) o(F14, 303) o(F15, 304)        \
                                        o(F16, 305) o(F17, 306) o(F18, 307)    \
                                            o(F19, 308) o(F20, 309)            \
                                                o(F21, 310) o(F22, 311)        \
                                                    o(F23, 312) o(F24, 313)    \
                                                        o(F25, 314)            \
                                                                               \
        /* Keypad */                                                           \
        o(KP0, 320) o(KP1, 321) o(KP2, 322) o(KP3, 323) o(KP4, 324) o(         \
            KP5, 325) o(KP6, 326) o(KP7, 327) o(KP8, 328) o(KP9, 329)          \
            o(KPDecimal, 330) o(KPDivide, 331) o(KPMultiply, 332) o(           \
                KPSubtract, 333) o(KPAdd, 334) o(KPEnter, 335) o(KPEqual, 336) \
                                                                               \
                o(LeftShift, 340) o(LeftControl, 341) o(LeftAlt, 342)          \
                    o(LeftSuper, 343) o(RightShift, 344) o(RightControl, 345)  \
                        o(RightAlt, 346) o(RightSuper, 347) o(Menu, 348)
