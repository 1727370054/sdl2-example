/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/8 21:59
* @version: 1.0
* @description: 
********************************************************************************/

#include "sdl_2_event.h"

bool SDL2Event::open(const std::string& background_path, const std::string& image_path)
{
    int flags = IMG_InitFlags::IMG_INIT_JPG | IMG_InitFlags::IMG_INIT_PNG | IMG_InitFlags::IMG_INIT_TIF
                | IMG_InitFlags::IMG_INIT_WEBP | IMG_InitFlags::IMG_INIT_JXL | IMG_InitFlags::IMG_INIT_AVIF;
    IMG_Init(flags);

#if 0
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) return false;

    _texture = SDL_CreateTextureFromSurface(_renderer, surface);

    SDL_FreeSurface(surface);
#else
//    _texture = IMG_LoadTexture(_renderer, path.c_str());
#endif

//    if (!_texture) return false;

    _background = IMG_LoadTexture(_renderer, background_path.c_str());
    _image = IMG_LoadTexture(_renderer, image_path.c_str());

    int w, h;
    int x, y;
    ///< 在渲染器中央放置前景
    SDL_QueryTexture(_image, NULL, NULL, &w, &h);
    x = _window_width / 2 - w / 2 + _dst_rect.x;
    y = _window_height / 2 - h / 2 + _dst_rect.y;
    _dst_rect.x = x;
    _dst_rect.y = y;
    _dst_rect.w = w;
    _dst_rect.h = h;

    return true;
}

void SDL2Event::handleEvents(SDL_Event &e)
{
    static int sx = 0, sy = 0;
    static bool is_drag = false;
    switch (e.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            std::cout << "mouse button down" << std::endl;
            sx = e.button.x - _dst_rect.x;
            sy = e.button.y - _dst_rect.y;
            if (e.button.x >= _dst_rect.x && e.button.x <= _dst_rect.x + _dst_rect.w
                && e.button.y >= _dst_rect.y && e.button.y <= _dst_rect.y + _dst_rect.h)
            {
                is_drag = true;
                std::cout << "is_drag: " << is_drag << std::endl;
            }
            else
            {
                is_drag = false;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            std::cout << "mouse button up" << std::endl;
            break;
        case SDL_MOUSEMOTION:
            if ((e.motion.state & SDL_BUTTON_LMASK) && is_drag)
            {
                _dst_rect.x = e.motion.x - sx;
                _dst_rect.y = e.motion.y - sy;

                if (_dst_rect.x < 0) _dst_rect.x = 0;
                if (_dst_rect.x + _dst_rect.w > _window_width) _dst_rect.x = _window_width - _dst_rect.w;
                if (_dst_rect.y < 0) _dst_rect.y = 0;
                if (_dst_rect.y + _dst_rect.h > _window_height) _dst_rect.y = _window_height - _dst_rect.h;
            }
            break;
        case SDL_KEYDOWN:
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_LEFT:
                    _dst_rect.x -= 10;
                    break;
                case SDLK_RIGHT:
                    _dst_rect.x += 10;
                    break;
                case SDLK_UP:
                    _dst_rect.y -= 10;
                    break;
                case SDLK_DOWN:
                    _dst_rect.y += 10;
                    break;
                default:
                    break;
            }
            break;
        }
        case SDL_MOUSEWHEEL:
            if (e.wheel.y > 0)
            {
                _dst_rect.h *= 1.1;
                _dst_rect.w *= 1.1;
            }
            if (e.wheel.y < 0)
            {
                _dst_rect.w /= 1.1;
                _dst_rect.h /= 1.1;
            }
            break;
    }

    SDLBase::handleEvents(e);
}

static void applySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *renderer)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    Uint32 format;
    int access;

    ///< 查询纹理属性, format, 纹理
    SDL_QueryTexture(tex, &format, &access, &pos.w, &pos.h);

    printf("纹理信息:\n");
    printf("  - 宽度: %d\n", pos.w);
    printf("  - 高度: %d\n", pos.h);
    printf("  - 像素格式: %s\n", SDL_GetPixelFormatName(format));
    printf("  - 访问模式: %d\n", access);

    SDL_RenderCopy(renderer, tex, NULL, &pos);
}

void SDL2Event::update()
{
    SDL_Rect pos;
    int w, h;
    SDL_QueryTexture(_background, nullptr, nullptr, &w, &h);
    pos.w = w;
    pos.h = h;
    ///< 在渲染器内平铺背景
    int x, y;
    for (y = 0; y < _window_height; y += h)
    {
        for (x = 0; x < _window_width; x += w)
        {
            pos.x = x;
            pos.y = y;
            SDL_RenderCopy(_renderer, _background, NULL, &pos);
        }
    }
}

void SDL2Event::render()
{
    SDL_RenderCopy(_renderer, _image, NULL, &_dst_rect);
    SDLBase::render();
}
