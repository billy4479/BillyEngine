#define SDL_MAIN_HANDLED
#include "Application.hpp"

int main() {
#ifdef DEBUG
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
#endif

    Application app("Test", 800, 600);
    app.Run();

    return 0;
}
