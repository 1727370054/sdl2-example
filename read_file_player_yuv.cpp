/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/8 20:12
* @version: 1.0
* @description: 
********************************************************************************/

#include "read_file_player_yuv.h"

bool ReadFilePlayerYUV::open(const std::string &path, uint32_t pixel_format)
{
    _pixel_format = pixel_format;

    _ifstream.open(path, std::ios::binary);
    if (!_ifstream.is_open())
    {
        std::cout << "open file failed" << std::endl;
        return false;
    }

    ///< 直接可以支持YUV444格式
    _buffer.resize(_window_width * _window_height * 3);

    if (_pixel_format == SDL_PIXELFORMAT_YUY2
        || _pixel_format == SDL_PIXELFORMAT_UYVY
        || _pixel_format == SDL_PIXELFORMAT_YVYU
        || _pixel_format == SDL_PIXELFORMAT_IYUV) // yuv422
    {
        _buffer_size = _window_width * _window_height * 2;
    }

    if (_pixel_format == SDL_PIXELFORMAT_YV12
        || _pixel_format == SDL_PIXELFORMAT_IYUV
        || _pixel_format == SDL_PIXELFORMAT_NV12
        || _pixel_format == SDL_PIXELFORMAT_NV21) // yuv420
    {
        _buffer_size = _window_width * _window_height * 3 / 2;
    }

    _pitch = _window_width * SDL_BYTESPERPIXEL(_pixel_format);

    _texture = SDL_CreateTexture(_renderer, _pixel_format, SDL_TEXTUREACCESS_STREAMING, _window_width, _window_height);

    return true;
}

const double FRAME_RATE = 23.976;  // 目标帧率
const double FRAME_DURATION = 1000.0 / FRAME_RATE; // 每帧间隔 (ms)
void ReadFilePlayerYUV::update()
{
    ///< 读取的时候，一次要读取一帧数据
    _ifstream.read(static_cast<char *>(_buffer.data()), _buffer_size);

    SDL_UpdateTexture(_texture, nullptr, _buffer.data(), _pitch);

//    /// 音视频同步： 休眠
    SDL_Delay(FRAME_DURATION); //// 1S = 1000ms, 1000 / 40 = 25 fps(帧率：每秒25帧）
}
