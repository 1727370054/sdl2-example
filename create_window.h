/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/3 21:58
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef SDL2_EXAMPLE_CREATE_WINDOW_H
#define SDL2_EXAMPLE_CREATE_WINDOW_H

#include "sdl_base.h"

#include <iostream>
#include <string>

class CreateWindow : public SDLBase
{
public:
    CreateWindow(const char* title, int width, int height)
    {
        (void)init(title, width, height, SDL_INIT_EVERYTHING);
    }
    ~CreateWindow() override = default;

    bool init(const char* title, int width, int height, Uint32 flags = SDL_INIT_VIDEO) override;

    void drawRect(int x, int y, int w, int h, SDL_Color color);
};


#endif //SDL2_EXAMPLE_CREATE_WINDOW_H
