/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/7 18:49
* @version: 1.0
* @description: 
********************************************************************************/

#include "load_bmp.h"

void LoadBMP::load(const std::string &path)
{
    if (!_screen_surface) return;

    SDL_Surface* temp = nullptr;
    temp = SDL_LoadBMP(path.c_str());
    SDL_Rect srcrect = {0, 0, 200, 200};
    SDL_Rect dstrect = {100, 100, 0, 0};
    SDL_BlitSurface(temp, nullptr, _screen_surface, nullptr);
    SDL_UpdateWindowSurface(_window);
    SDL_FreeSurface(temp);
    temp = nullptr;
}

void LoadBMP::render_load(const std::string &path)
{
    _texture = loadTexture(path.c_str());
}
