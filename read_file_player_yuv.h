/********************************************************************************
* @author: hwk
* @email: orionlink@163.com
* @date: 2025/3/8 20:12
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef SDL2_EXAMPLE_READ_FILE_PLAYER_YUV_H
#define SDL2_EXAMPLE_READ_FILE_PLAYER_YUV_H

#include "sdl_base.h"

class ReadFilePlayerYUV : public SDLBase
{
public:
    ReadFilePlayerYUV() = default;
    ~ReadFilePlayerYUV() override = default;

    /**
     * @brief 只支持打包格式的yuv
     * @param path
     * @param pixel_format
     * @return
     */
    bool open(const std::string& path, uint32_t pixel_format);

protected:
    void update() override;
private:
    std::ifstream _ifstream;
    std::vector<char> _buffer;
    uint32_t _pixel_format;
    uint32_t _buffer_size;
    int _pitch = 0; ///< 一行像素数据中的字节数
};


#endif //SDL2_EXAMPLE_READ_FILE_PLAYER_YUV_H
