/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/8 14:20
* @version: 1.0
* @description: 
********************************************************************************/

#include "sound_mixer.h"

SoundMixer::SoundMixer()
{

}

SoundMixer::~SoundMixer()
{

}

bool SoundMixer::init(const char *title, int width, int height, Uint32 flags)
{
    unsigned int mix_flags = MIX_InitFlags::MIX_INIT_FLAC | MIX_InitFlags::MIX_INIT_MOD | MIX_InitFlags::MIX_INIT_MP3
            | MIX_InitFlags::MIX_INIT_OGG | MIX_InitFlags::MIX_INIT_MID | MIX_InitFlags::MIX_INIT_OPUS
            | MIX_InitFlags::MIX_INIT_WAVPACK;
    int initialized = Mix_Init(mix_flags);
    if ((initialized & mix_flags) != mix_flags)
    {
        std::cout << "Mix_Init: Failed to init required flags: " << Mix_GetError() << std::endl;
        return false;
    }

    return SDLBase::init(title, width, height, flags);
}

void SoundMixer::cleanUp()
{
    if (_chunk)
        Mix_FreeChunk(_chunk);

    if (_music)
        Mix_FreeMusic(_music);

    Mix_Quit();
    SDLBase::cleanUp();
}

void SoundMixer::run()
{
    SDLBase::run();
}
void SoundMixer::loadSound(const char *path, int audio_rate, uint16_t audio_format, int audio_channels)
{
    _sound_path = path;
    _audio_rate = audio_rate;
    _audio_format = audio_format;
    _audio_channels = audio_channels;

    if (Mix_OpenAudio(_audio_rate, _audio_format, _audio_channels, _audio_buffer_size) < 0)
    {
        std::cout << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
        return;
    }

    if ((_chunk = Mix_LoadWAV(_sound_path.c_str())) == nullptr)
    {
        std::cout << "Mix_LoadMUS: " << Mix_GetError() << std::endl;
        return;
    }
}

void SoundMixer::playSound()
{
    _thread = std::thread([&]()
    {
        while (_thread_run)
        {
            if (Mix_Playing(_channel) == 0)
            {
                _channel = Mix_PlayChannel(-1, _chunk, 0);
                if (_channel == -1)
                {
                    std::cout << "Mix_PlayChannel: " << Mix_GetError() << std::endl;
                    return;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    _thread.detach();
}

void SoundMixer::loadMusic(const char *path, int audio_rate, uint16_t audio_format, int audio_channels)
{
    _music_path = path;
    _audio_rate = audio_rate;
    _audio_format = audio_format;
    _audio_channels = audio_channels;

    if (Mix_OpenAudio(_audio_rate, _audio_format, _audio_channels, _audio_buffer_size) < 0)
    {
        std::cout << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
        return;
    }

    if ((_music = Mix_LoadMUS(_music_path.c_str())) == nullptr)
    {
        std::cout << "Mix_LoadMUS: " << Mix_GetError() << std::endl;
        return;
    }
}
void SoundMixer::playMusic()
{
    _thread = std::thread([&]()
    {
        while (_thread_run)
        {
            if (Mix_PlayingMusic() == 0) ///< 检查当前是否有音乐正在播放。
            {
                /*
                 * 功能：播放指定的音乐文件。
                 * 参数：
                 * Mix_Music* music：要播放的音乐对象。
                 * int loops：播放次数（-1 表示循环播放）。
                 * 返回值：成功返回 0，失败返回 -1。
                 */
                if (Mix_PlayMusic(_music, 0) == -1)
                {
                    std::cout << "Mix_PlayMusic: " << Mix_GetError() << std::endl;
                    return;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    _thread.detach();
}

void SoundMixer::stopMusic()
{

}

void SoundMixer::setVolume(int volume)
{
    if (volume < 0 || volume > 128)
        return;

    Mix_VolumeMusic(volume);
    Mix_VolumeChunk(_chunk, volume);
}

int SoundMixer::getVolume()
{
    return 0;
}
