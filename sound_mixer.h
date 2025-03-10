/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/8 14:20
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef SDL2_EXAMPLE_SOUND_MIXER_H
#define SDL2_EXAMPLE_SOUND_MIXER_H

#include "sdl_base.h"

class SoundMixer : public SDLBase
{
public:
    SoundMixer();
    ~SoundMixer() override;
    bool init(const char* title, int width, int height, Uint32 flags = SDL_INIT_VIDEO) override;
    void cleanUp() override;
    void run() override;

    void loadMusic(const char* path, int audio_rate, uint16_t audio_format, int audio_channels);
    void loadSound(const char* path, int audio_rate, uint16_t audio_format, int audio_channels);
    void playSound();
    void playMusic();
    void stopMusic();
    void setVolume(int volume);
    int getVolume();
private:
    Mix_Chunk* _chunk = nullptr;   ///< 音效句柄
    int _channel = -1;             ///< 当前打开的音频的通道号

    Mix_Music * _music = nullptr;  ///< 音乐句柄

    int _audio_channels = -1;
    int _audio_rate = 0;
    uint16_t _audio_format = 0;
    int _audio_buffer_size = 4096;
    std::string _music_path = "";
    std::string _sound_path = "";

    std::thread _thread;
    bool _thread_run = true;
};


#endif //SDL2_EXAMPLE_SOUND_MIXER_H
