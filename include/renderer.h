//
// Created by Ville Välimaa on 31/10/2017.
//

#ifndef UNTITLED_RENDERER_H
#define UNTITLED_RENDERER_H

#include "SDL.h"

class gpu_renderer {
private:
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    void drawPixel(int location);
public:
    virtual ~gpu_renderer();
    void init();
    void updateFramebuffer(unsigned char* gfx_buffer);
};


#endif //UNTITLED_RENDERER_H
