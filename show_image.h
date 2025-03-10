/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/7 23:11
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef SDL2_EXAMPLE_SHOW_IMAGE_H
#define SDL2_EXAMPLE_SHOW_IMAGE_H

#include "sdl_base.h"

class ShowImage : public SDLBase
{
public:
    ShowImage() = default;
    ~ShowImage() override
    {
        cleanUp();
        IMG_Quit();
    }

    void show(const std::string& path);
};


#endif //SDL2_EXAMPLE_SHOW_IMAGE_H
