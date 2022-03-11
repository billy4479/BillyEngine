#pragma once

// From glfw.h
// Thank you, clang-format...

#define ENUMERATE_MOUSE_BUTTONS(o)                                        \
    o(Button0, 0) o(Button1, 1) o(Button2, 2) o(Button3, 3) o(Button4, 4) \
        o(Button5, 5) o(Button6, 6) o(Button7, 7) o(ButtonLast, 7)        \
            o(ButtonLeft, 0) o(ButtonRight, 1) o(ButtonMiddle, 2)
