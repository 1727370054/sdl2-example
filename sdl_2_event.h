/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/8 21:59
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef SDL2_EXAMPLE_SDL_2_EVENT_H
#define SDL2_EXAMPLE_SDL_2_EVENT_H

#include "sdl_base.h"

class SDL2Event : public SDLBase
{
public:
    SDL2Event() = default;
    ~SDL2Event()
    {
        IMG_Quit();
        cleanUp();
    }

    void handleEvents(SDL_Event& e) override;

    void update() override;

    bool open(const std::string& background_path, const std::string& image_path);

    void render() override;
private:
    SDL_Texture *_background = nullptr, *_image = nullptr;
};


#endif //SDL2_EXAMPLE_SDL_2_EVENT_H
