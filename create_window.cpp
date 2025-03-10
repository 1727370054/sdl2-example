/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/3 21:58
* @version: 1.0
* @description: 
********************************************************************************/

#include "create_window.h"

bool CreateWindow::init(const char *title, int width, int height, Uint32 flags)
{
    _window_width = width;
    _window_height = height;
    _window_title = title;

    if (SDL_Init(flags) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    ///< SDL_WINDOWPOS_UNDEFINED 窗口位置未定义，由系统确定
    _window = SDL_CreateWindow(_window_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _window_width, _window_height, SDL_WINDOW_SHOWN);
    if (_window == nullptr)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

//    /*
//     * SDL_RendererFlags是一个枚举类型，用于指定渲染器的创建标志：
//     * 1. SDL_RENDERER_SOFTWARE：使用软件渲染器（后备方案）。
//     * 2. SDL_RENDERER_ACCELERATED：使用硬件加速渲染器。
//     * 3. SDL_RENDERER_PRESENTVSYNC：渲染与屏幕刷新率同步（垂直同步）。
//     * 4. SDL_RENDERER_TARGETTEXTURE：渲染器支持渲染到纹理。
//     */
//    _renderer = SDL_CreateRenderer(_window,-1,SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
//
//    if (_renderer == nullptr)
//    {
//        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//        return false;
//    }
//
//    // 设置默认渲染颜色（黑色背景）
//    SDL_SetRenderDrawColor(_renderer,0, 0, 0, 255);

    // 获取窗口表面
    _screen_surface = SDL_GetWindowSurface(_window);
    if (_screen_surface == nullptr)
    {
        std::cerr << "Surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true; // 添加成功返回值
}

void CreateWindow::drawRect(int x, int y, int w, int h, SDL_Color color)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_FillRect(_screen_surface, nullptr, SDL_MapRGBA(_screen_surface->format, color.r, color.g, color.b, color.a));
    SDL_FillRect(_screen_surface, &rect, SDL_MapRGBA(_screen_surface->format, 50,50,32,10));
    SDL_UpdateWindowSurface(_window);
}
