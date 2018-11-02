#ifndef WINDOW_SDLWINDOW_H
#define WINDOW_SDLWINDOW_H

#include <SDL2/SDL.h>
#include "Sound.h"

class SdlWindow {
public:
    SdlWindow(int width, int height);
    ~SdlWindow();
    void fill();
    void fill(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);
    void render();
    void grabMouse(bool grab);
    SDL_Renderer* getRenderer() const;
private:
    const int width;
    const int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Sound background;
};


#endif //WINDOW_SDLWINDOW_H
