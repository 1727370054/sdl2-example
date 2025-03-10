/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/7 18:49
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef SDL2_EXAMPLE_LOAD_BMP_H
#define SDL2_EXAMPLE_LOAD_BMP_H

#include "sdl_base.h"

class LoadBMP : public SDLBase
{
public:
    LoadBMP() = default;
    void load(const std::string& path);
    void render_load(const std::string& path);
};


#endif //SDL2_EXAMPLE_LOAD_BMP_H
