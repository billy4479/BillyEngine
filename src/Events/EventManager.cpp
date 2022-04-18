#include "EventManager.hpp"

#include <GLFW/glfw3.h>

#include "Core/Logger.hpp"
#include "Events/KeyboardEvent.hpp"
#include "Events/MouseCodes.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/WindowEvent.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/Window.hpp"

namespace BillyEngine {

class Callbacks {
   public:
    static void WindowClose(GLFWwindow* window) {
        auto e = WindowCloseEvent{};
        e.Data = CreateWindowEventData(window);
        The().Dispatcher(e);
    }

    static void WindowMove(GLFWwindow* window, i32, i32) {
        auto e = WindowMoveEvent{};
        e.Data = CreateWindowEventData(window);
        The().Dispatcher(e);
    }

    static void WindowResize(GLFWwindow* window, i32, i32) {
        auto e = WindowResizeEvent{};
        e.Data = CreateWindowEventData(window);
        The().Dispatcher(e);
    }

    static void WindowFocusChanged(GLFWwindow* window, i32) {
        auto e = WindowFocusEvent{};
        e.Data = CreateWindowEventData(window);
        The().Dispatcher(e);
    }

    static void Key(GLFWwindow*, i32 key, i32 scancode, i32 action, i32 mods) {
        switch (action) {
            case GLFW_PRESS:
            case GLFW_REPEAT: {
                auto e = KeyPressedEvent{};
                e.Data.Keycode = key;
                e.Data.Scancode = scancode;
                e.Data.Mods = mods;
                The().Dispatcher(e);
                break;
            }
            case GLFW_RELEASE: {
                auto e = KeyReleasedEvent{};
                e.Data.Keycode = key;
                e.Data.Scancode = scancode;
                e.Data.Mods = mods;
                The().Dispatcher(e);
                break;
            }
            default:
                VERIFY_NOT_REACHED();
        }
    }

    static void Char(GLFWwindow*, u32 keycode) {
        // TODO: `keycode` is a Unicode point instead.
        //       Should it be handled differently?

        auto e = KeyTypedEvent{};
        e.Data.Keycode = keycode;
        e.Data.Scancode = glfwGetKeyScancode(keycode);
        e.Data.Mods = 0;  // FIXME: Mhh, there should be a way...
        The().Dispatcher(e);
    }

    static void MouseButton(GLFWwindow* window, i32 button, i32 action,
                            i32 mods) {
        MouseEvent::MouseEventData data{};
        data.Mods = mods;
        data.Button = button;
        data.ScrollOffset = {0, 0};
        data.Position = GetMousePosition(window);
        switch (action) {
            case GLFW_PRESS: {
                auto e = MouseButtonPressedEvent{};
                e.Data = data;
                The().Dispatcher(e);
                break;
            }
            case GLFW_RELEASE: {
                auto e = MouseButtonReleasedEvent{};
                e.Data = data;
                The().Dispatcher(e);
                break;
            }
            default:
                VERIFY_NOT_REACHED();
        }
    }

    static void MouseScroll(GLFWwindow* window, f64 xOffset, f64 yOffset) {
        auto e = MouseScrolledEvent{};
        e.Data.ScrollOffset = {(f32)xOffset, (f32)yOffset};
        e.Data.Button = Buttons::ButtonNone;
        e.Data.Mods = 0;
        e.Data.Position = GetMousePosition(window);
        The().Dispatcher(e);
    }

    static void MouseMove(GLFWwindow*, f64 x, f64 y) {
        auto e = MouseMovedEvent{};
        e.Data.Button = Buttons::ButtonNone;
        e.Data.Mods = 0;
        e.Data.ScrollOffset = {0, 0};
        e.Data.Position = {x, y};
        The().Dispatcher(e);
    }

   public:
    static Callbacks& The() {
        if (s_Instance == nullptr) s_Instance = new Callbacks;
        return *s_Instance;
    }
    std::function<void(const Event&)> Dispatcher;

   private:
    static WindowEvent::WindowEventData CreateWindowEventData(
        GLFWwindow* window) {
        WindowEvent::WindowEventData data;
        glfwGetWindowPos(window, &data.Position.x, &data.Position.y);
        glfwGetFramebufferSize(window, &data.Size.x, &data.Size.y);
        data.HasFocus = glfwGetWindowAttrib(window, GLFW_FOCUSED);
        return data;
    }

    static glm::ivec2 GetMousePosition(GLFWwindow* window) {
        f64 x, y;
        glfwGetCursorPos(window, &x, &y);
        return {x, y};
    }

    static Callbacks* s_Instance;
    Callbacks() = default;
};

Callbacks* Callbacks::s_Instance = nullptr;

EventManager::EventManager(Window& window) {
    Callbacks::The().Dispatcher = [this](const Event& e) {
        for (const auto& [id, f] : m_Listeners) f(e);
    };

    auto w = window.m_Window;

    glfwSetWindowCloseCallback(w, &Callbacks::WindowClose);
    glfwSetWindowPosCallback(w, &Callbacks::WindowMove);
    glfwSetFramebufferSizeCallback(w, &Callbacks::WindowResize);
    glfwSetWindowFocusCallback(w, &Callbacks::WindowFocusChanged);

    glfwSetKeyCallback(w, &Callbacks::Key);
    glfwSetCharCallback(w, &Callbacks::Char);

    glfwSetMouseButtonCallback(w, &Callbacks::MouseButton);
    glfwSetScrollCallback(w, &Callbacks::MouseScroll);
    glfwSetCursorPosCallback(w, &Callbacks::MouseMove);
}

EventManager::~EventManager() {}

void EventManager::HandleEvents() { glfwPollEvents(); }

void EventManager::RemoveListener(u32 id) { m_Listeners.erase(id); }

}  // namespace BillyEngine