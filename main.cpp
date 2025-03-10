#include <iostream>
#include <random>

#include "sdl_base.h"
#include "create_window.h"
#include "load_bmp.h"
#include "show_image.h"
#include "sound_mixer.h"
#include "sdl_audio.h"
#include "random_yuv.h"
#include "read_file_player_yuv.h"
#include "sdl_2_event.h"

#undef main

int main()
{
//    CreateWindow window("SDL_窗口测试", 800, 600);
//    window.drawRect(200, 200, 100, 100, { 255, 73, 62, 0 });
//    window.run();

//    LoadBMP bmp;
//    bmp.init("SDL_加载位图测试", 800, 600);
////    bmp.load("./Hello_world.bmp");
//    bmp.render_load("./Hello_world.bmp");
//    bmp.run();

//    ShowImage image;
//    image.init("SDL_显示图片测试", 800, 600);
////    image.show("./Hello_world.png");
//    image.show("./Hello_world.jpg");
//    image.run();

//    SoundMixer mixer;
//    mixer.init("SDL_播放音乐和音效测试", 800, 600);
////    mixer.loadSound("./sound.wav", 44100, AUDIO_S16SYS, 2);
////    mixer.playSound();
//    mixer.loadMusic("./起风了-林俊杰.mp3", 44100, AUDIO_S16SYS, 2);
//    mixer.setVolume(128);
//    mixer.playMusic();
//    mixer.run();

    SDLAudio audio(44100, AUDIO_S16SYS, 2);
    audio.set_volume(128);
    if (!audio.init("SDL_播放音频测试", 800, 600))
        return 1;

    if (!audio.open("./tc-jj.pcm"))
        return 2;

    audio.play();
    audio.run();

//    RandomYUV yuv;
//    yuv.init("SDL_随机YUV测试", 800, 600);
//    yuv.show();
//    yuv.run();

//    ReadFilePlayerYUV read_file_player_yuv;
//    if (!read_file_player_yuv.init("SDL_播放YUV测试", 1920, 1080))
//        return 1;
//
//    if (!read_file_player_yuv.open("./test_yuv420p.yuv", SDL_PIXELFORMAT_IYUV))
//        return 2;
//
//    read_file_player_yuv.run();

//    SDL2Event event;
//    if (!event.init("SDL_2_Event测试", 800, 600))
//    {
//        return 1;
//    }
//    if (!event.open("background.png", "./event.png"))
//    {
//        return 2;
//    }
//    event.run();

    return 0;
}
