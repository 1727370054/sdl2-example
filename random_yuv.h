/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/8 18:21
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef SDL2_EXAMPLE_RANDOM_YUV_H
#define SDL2_EXAMPLE_RANDOM_YUV_H

#include "sdl_base.h"

class RandomYUV : public SDLBase
{
public:
    RandomYUV() = default;
    ~RandomYUV() override = default;

    bool init(const char *title = "test", int width = 800, int height = 600, Uint32 flags = SDL_INIT_VIDEO) override;

    void show();

    virtual void update() override;
private:
    char* _yuv_data = nullptr;
    char* _y;
    char* _u;
    char* _v;
};


#endif //SDL2_EXAMPLE_RANDOM_YUV_H
