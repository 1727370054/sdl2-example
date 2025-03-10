/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/3 22:06
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef SDL2_EXAMPLE_SDL_BASE_H
#define SDL2_EXAMPLE_SDL_BASE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <fstream>
#include <atomic>
#include <string>
#include <iostream>
#include <random>
#include <thread>

class SDLBase
{
protected:
    // 基本的 SDL 句柄
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
    SDL_Surface* _screen_surface = nullptr;

    // 常用的资源句柄
    SDL_Texture* _texture = nullptr;
    SDL_Rect _src_rect;
    SDL_Rect _dst_rect;


    // 窗口基本属性
    int _window_width = 0;
    int _window_height = 0;
    std::string _window_title;

    // 控制主循环
    bool _quit = false;

    std::random_device _rd;
    std::mt19937 _gen{_rd()};

    std::thread _worker_thread;
public:
    SDLBase() = default;
    virtual ~SDLBase() {
        cleanUp();
    }

    // 初始化 SDL 及窗口
    virtual bool init(const char* title = "test", int width = 800, int height = 600, Uint32 flags = SDL_INIT_VIDEO);

    // 加载 BMP 纹理
    SDL_Texture* loadTexture(const char* path);

    // 资源清理
    virtual void cleanUp();

    // 虚函数，由子类实现
    virtual bool loadMedia();
    virtual void handleEvents(SDL_Event& e);
    virtual void update();
    virtual void render();

    // 主循环
    virtual void run();
};

#endif //SDL2_EXAMPLE_SDL_HANDLES_H
