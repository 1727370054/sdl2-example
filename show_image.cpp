/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/7 23:11
* @version: 1.0
* @description: 
********************************************************************************/

#include "show_image.h"

void ShowImage::show(const std::string &path)
{
    int flags = IMG_InitFlags::IMG_INIT_JPG | IMG_InitFlags::IMG_INIT_PNG | IMG_InitFlags::IMG_INIT_TIF
            | IMG_InitFlags::IMG_INIT_WEBP | IMG_InitFlags::IMG_INIT_JXL | IMG_InitFlags::IMG_INIT_AVIF;
    IMG_Init(flags);

    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr)
        return;

    _texture = SDL_CreateTextureFromSurface(_renderer, surface);

    SDL_FreeSurface(surface);
}
