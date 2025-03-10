/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/3 22:06
* @version: 1.0
* @description: 
********************************************************************************/

#include "sdl_base.h"

bool SDLBase::init(const char *title, int width, int height, Uint32 flags)
{
    _window_width = width;
    _window_height = height;
    _window_title = title;

    _src_rect = {0, 0, _window_width, _window_height};
    _dst_rect = {0, 0, _window_width, _window_height};

    // 初始化 SDL
    if (SDL_Init(flags) < 0) {
        std::cerr << "SDL 初始化失败: " << SDL_GetError() << std::endl;
        return false;
    }

    // 创建窗口
    _window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height, SDL_WINDOW_SHOWN);
    if (!_window) {
        std::cerr << "窗口创建失败: " << SDL_GetError() << std::endl;
        cleanUp();
        return false;
    }

    // 创建渲染器
    /*
     * SDL_RendererFlags是一个枚举类型，用于指定渲染器的创建标志：
     * 1. SDL_RENDERER_SOFTWARE：使用软件渲染器（后备方案）。
     * 2. SDL_RENDERER_ACCELERATED：使用硬件加速渲染器。
     * 3. SDL_RENDERER_PRESENTVSYNC：渲染与屏幕刷新率同步（垂直同步）。
     * 4. SDL_RENDERER_TARGETTEXTURE：渲染器支持渲染到纹理。
     */
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer) {
        std::cerr << "渲染器创建失败: " << SDL_GetError() << std::endl;
        cleanUp();
        return false;
    }

//    // 设置默认渲染颜色（黑色背景）
//    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

    // 获取窗口表面
    _screen_surface = SDL_GetWindowSurface(_window);

    return true;
}

SDL_Texture *SDLBase::loadTexture(const char *path)
{
    // 释放之前的纹理
    if (_texture) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }

    // 加载 BMP 图像
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    if (!loadedSurface) {
        std::cerr << "无法加载图像 " << path << ": " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // 从表面创建纹理
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
    if (!texture) {
        std::cerr << "无法创建纹理: " << SDL_GetError() << std::endl;
    }

    // 释放临时表面
    SDL_FreeSurface(loadedSurface);

    return texture;
}

void SDLBase::cleanUp()
{
    if (_texture) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }

    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }

    if (_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }

    SDL_Quit();
}

void SDLBase::run()
{
//    if (!loadMedia()) {
//        std::cerr << "加载媒体失败!" << std::endl;
//        return;
//    }

    SDL_Event e;
    _quit = false;

//    _rect.w = 100;
//    _rect.h = 100;
//    _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _window_width, _window_height);

    // 主循环
    while (!_quit)
    {
        // 处理事件
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {
                _quit = true;
            }
            handleEvents(e);
        }

        // 清屏
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

        ///< 将上一次渲染器渲染的数据清空
        SDL_RenderClear(_renderer);

        // 更新状态
        update();

        // 渲染
        render();

        // 更新屏幕
        SDL_RenderPresent(_renderer);
    }
}

bool SDLBase::loadMedia()
{
    return false;
}

void SDLBase::handleEvents(SDL_Event &e)
{

}

void SDLBase::update()
{

}

void SDLBase::render()
{
    if (_renderer == nullptr)
        return;

    SDL_RenderCopy(_renderer, _texture, &_src_rect, &_dst_rect);
#if 1
//    _texture = loadTexture("./Hello_world.bmp");
//    SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);
#else
    std::uniform_int_distribution<> dis(0, 500);
    _rect.x = dis(_gen) % 500;
    _rect.y = dis(_gen) % 500;

    // 清屏
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

    ///< 绑定到 _texture 作为渲染目标
    ///< 这里可以SDL_SetRenderTarget(_renderer, nullptr); 代表设置渲染目标为窗口
    ///< 那么此时 SDL_RenderCopy(_renderer, nullptr, nullptr, nullptr); 数据在窗口上，需要从窗口拷贝给渲染器
    SDL_SetRenderTarget(_renderer, _texture);

    ///< 将上一次渲染器渲染的数据清空, 清除当前渲染目标（即 _texture）
    SDL_RenderClear(_renderer);

    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 0);
    // 绘制矩形
    SDL_RenderDrawRect(_renderer, &_rect);
    // 填充矩形
    SDL_RenderFillRect(_renderer, &_rect);

//    SDL_RenderDrawLine(_renderer, _rect.x, _rect.y, _rect.x + 100, _rect.y + 100);

    ///< 切换渲染目标到 NULL，表示切换回默认渲染目标（即窗口）。
    SDL_SetRenderTarget(_renderer, nullptr);

    ///< SDL_RenderCopy 的作用是 把 _texture 的内容复制到窗口（默认渲染目标）。
    SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);

    SDL_Delay(500);
#endif
}
