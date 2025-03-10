/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/8 16:05
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef SDL2_EXAMPLE_SDL_AUDIO_H
#define SDL2_EXAMPLE_SDL_AUDIO_H

#include "sdl_base.h"

class SDLAudio : public SDLBase
{
public:
    SDLAudio(int freq, SDL_AudioFormat format, uint8_t channels
        ,SDL_AudioCallback callback = nullptr, void* userdata = nullptr);
    virtual ~SDLAudio() override
    {
        cleanUp();
    }

    bool init(const char* title, int width, int height, Uint32 flags = SDL_INIT_VIDEO) override;

    bool open(const std::string& path);

    void play();

    void run() override;

    void set_volume(int volume)
    {
        _volume = volume;
    }

    void audioCallback(void* userdata, uint8_t* stream, int len);
private:

    std::ifstream _ifstream;
    std::vector<uint8_t> _buffer;
    int _buffer_size = 4096;
    SDL_AudioSpec _spec;
    std::atomic<uint8_t*> _audio_pos; // 原子指针
    std::atomic<int> _audio_len;      // 原子长度

    int _volume = 100;
};

#endif //SDL2_EXAMPLE_SDL_AUDIO_H
