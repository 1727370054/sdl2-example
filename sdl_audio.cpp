/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/8 16:05
* @version: 1.0
* @description: 
********************************************************************************/

#include "sdl_audio.h"

static void audio_callback(void *userdata, uint8_t *stream, int len)
{
    SDLAudio *audio = static_cast<SDLAudio *>(userdata);
    audio->audioCallback(userdata, stream, len);
}
SDLAudio::SDLAudio(int freq, SDL_AudioFormat format, uint8_t channels, SDL_AudioCallback callback, void *userdata)
{
    _spec.freq = freq;
    _spec.format = format;
    _spec.channels = channels;
    _spec.samples = 1024;

    if (callback == nullptr)
    {
        _spec.callback = audio_callback;
        _spec.userdata = this;
    }
    else
    {
        _spec.callback = callback;
        _spec.userdata = userdata;
    }
}

bool SDLAudio::init(const char *title, int width, int height, Uint32 flags)
{
    if (SDL_OpenAudio(&_spec, nullptr) < 0)
        return false;

    return SDLBase::init(title, width, height, flags);
}

bool SDLAudio::open(const std::string &path)
{
    _ifstream.open(path, std::ios::binary | std::ios::in);
    if (!_ifstream.is_open())
        return false;

    _buffer.resize(_buffer_size);

    /**
     * @brief 当 pause_on 为 1 时，音频设备会暂停，不再调用音频回调函数，此时音频输出会停止。
        当 pause_on 为 0 时，音频设备会重新启动，开始调用音频回调函数，音频输出会恢复
     */

    ///< 启动音频设备后，音频回调函数 audioCallback 是由 SDL 内部的一个独立音频线程调用的，而不是主线程。
    SDL_PauseAudio(0);

    return true;
}

void SDLAudio::play()
{
    _worker_thread = std::thread([this](){
        while (!_ifstream.eof())
        {
            _ifstream.read(reinterpret_cast<char *>(_buffer.data()), _buffer_size);
            if (_ifstream.bad())
                break;

            _audio_pos.store(reinterpret_cast<uint8_t *>(_buffer.data()), std::memory_order_relaxed);
            _audio_len.store(static_cast<int>(_ifstream.gcount()), std::memory_order_relaxed);
            while (_audio_len.load(std::memory_order_relaxed) > 0)       // 等待audio_len长度的数据播放完成
                SDL_Delay(1);
        }
    });

    _worker_thread.detach();
}

void SDLAudio::audioCallback(void *userdata, uint8_t *stream, int len)
{
    ///< 在混合音频数据之前，需要确保输出流是干净的，避免残留的音频数据影响播放效果。
    SDL_memset(stream, 0, len);
    int remaining_len = _audio_len.load(std::memory_order_relaxed);
    if (remaining_len == 0) {
        SDL_memset(stream, 0, len);
        return;
    }
    ///< len 为 stream 的长度, _audio_len 为剩余的音频数据长度，取两者最小值，避免超出 stream 的长度
    ///< 和 _audio_pos 的长度
    len = std::min(len, remaining_len);
    uint8_t* pos = _audio_pos.load(std::memory_order_relaxed);
    SDL_MixAudio(stream, pos, len, _volume);

    _audio_pos.fetch_add(len, std::memory_order_relaxed);
    _audio_len.fetch_sub(len, std::memory_order_relaxed);

    std::cout << "len: " << len << std::endl;
}

void SDLAudio::run()
{
    SDLBase::run();
}
