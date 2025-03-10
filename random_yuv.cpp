/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/8 18:21
* @version: 1.0
* @description: 
********************************************************************************/

#include "random_yuv.h"

bool RandomYUV::init(const char *title, int width, int height, Uint32 flags)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    ///< yuv420 数据只需要  width * height * 1.5 字节, * 2 为了预留更多空间
    _yuv_data = new char[width * height * 2];
    memset(_yuv_data, 0, width * height * 2);

    ///< 这两种算法均可
//    _y = _yuv_data;
//    _u = _yuv_data + width * height;
//    _v = _yuv_data + width * height + width * height / 4;

    _y = _yuv_data;
    _u = _y + width * height;
    _v = _u + width * height / 4;

    return SDLBase::init(title, width, height, flags);
}

static void FillYuvImage(char* pYuv, int nWidth, int nHeight, int nIndex)
{
    int x, y, i;

    i = nIndex;

    char* pY = pYuv;
    char* pU = pYuv + nWidth * nHeight;
    char* pV = pYuv + nWidth * nHeight * 5 / 4;

    /* Y */
    for (y = 0; y < nHeight; y++)
    {
        for (x = 0; x < nWidth; x++)
        {
//            pY[y * nWidth + x] = x + y + i * 2;//+ y
            pY[y * nWidth + x] = 1000;//+ y
        }
    }

    /* Cb and Cr */
    for (y = 0; y < nHeight / 2; y++)
    {
        for (x = 0; x < nWidth / 2; x++)
        {
//            pU[y * (nWidth / 2) + x] = 64 + y + i * 2;
//            pV[y * (nWidth / 2) + x] = 64 + x + i * 5;
            pU[y * (nWidth / 2) + x] = 120;
            pV[y * (nWidth / 2) + x] = 85;
        }
    }
}
void RandomYUV::show()
{
    _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, _window_width, _window_height);
}

void RandomYUV::update()
{
    static int index = 0;

    FillYuvImage(_yuv_data, _window_width, _window_height, index++);

    int ret = SDL_UpdateYUVTexture(_texture, NULL,
                                   reinterpret_cast<const Uint8 *>(_y),
                                   _window_width, reinterpret_cast<const Uint8 *>(_u),
                                   _window_width / 2, reinterpret_cast<const Uint8 *>(_v), _window_width / 2);
    if (ret < 0)
    {
        printf("SDL_UpdateYUVTexture failed: %s\n", SDL_GetError());
        return;
    }
}

