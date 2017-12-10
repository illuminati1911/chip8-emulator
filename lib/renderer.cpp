//
// Created by Ville Välimaa on 31/10/2017.
//

#include <iostream>
#include "renderer.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 512;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

void gpu_renderer::init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
}

void gpu_renderer::updateFramebuffer(unsigned char* gfx_buffer) {
    /// Clear screen
    ///
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    /// Apply gfx_buffer to SDL renderer and render
    ///
    for (int i = 0; i < 64*32; i++) {
        if (gfx_buffer[i] == 0x1) {
            this->drawPixel(i);
        }
    }
    SDL_RenderPresent(renderer);
}

void gpu_renderer::drawPixel(int location) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    std::unique_ptr<SDL_Rect> virtualPixel = std::make_unique<SDL_Rect>();
    virtualPixel->x = (location % 64) * 16;
    virtualPixel->y = location / 64 * 16;
    virtualPixel->w = 16;
    virtualPixel->h = 16;
    SDL_RenderFillRect(renderer, virtualPixel.get());
}

gpu_renderer::~gpu_renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
