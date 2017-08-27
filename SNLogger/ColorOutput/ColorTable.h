#ifndef __SN_COLOR_TABLE_H__
#define __SN_COLOR_TABLE_H__

#include <ostream>

namespace SurgeNight
{

    enum ColorTable {
        COLOR_BLACK = 0,
        COLOR_BLUE,
        COLOR_GREEN,
        COLOR_SHALLOWGREEN,
        COLOR_RED,
        COLOR_PURPLE,
        COLOR_YELLOW,
        COLOR_WHITE,
        COLOR_GRAY,
        COLOR_LIGHTBLUE,
        COLOR_LIGHTGREEN,
        COLOR_LIGHTSHALLOWGREEN,
        COLOR_LIGHTRED,
        COLOR_LIGHTPURPLE,
        COLOR_LIGHTYELLOW,
        COLOR_LIGHTWHITE
    };

    struct OutputColor
    {
        unsigned int color;
        const OutputColor operator+(const OutputColor &clr) const;
    };

    static OutputColor snFgBlack = { COLOR_BLACK }, snFgBlue = { COLOR_BLUE },
                snFgGreen = { COLOR_GREEN }, snFgShgreen = { COLOR_SHALLOWGREEN },
                snFgRed = { COLOR_RED }, snFgPurple = { COLOR_PURPLE },
                snFgYellow = { COLOR_YELLOW }, snFgWhite = { COLOR_WHITE },
                snFgGray = { COLOR_GRAY }, snFgLgblue = { COLOR_LIGHTBLUE },
                snFgLggreen = { COLOR_LIGHTGREEN }, snFgLgshgreen = { COLOR_LIGHTSHALLOWGREEN },
                snFgLgred = { COLOR_LIGHTRED }, snFgLgpurple = { COLOR_LIGHTPURPLE },
                snFgLgyellow = { COLOR_LIGHTYELLOW }, snFgLgwhite = { COLOR_LIGHTWHITE },
                snFgClear = { COLOR_WHITE },

                snBgBlack = { COLOR_BLACK * 16 }, snBgBlue = { COLOR_BLUE * 16 },
                snBgGreen = { COLOR_GREEN * 16 }, snBgShgreen = { COLOR_SHALLOWGREEN * 16 },
                snBgRed = { COLOR_RED * 16 }, snBgPurple = { COLOR_PURPLE * 16 },
                snBgYellow = { COLOR_YELLOW * 16 }, snBgWhite = { COLOR_WHITE * 16 },
                snBgGray = { COLOR_GRAY * 16 }, snBgLgblue = { COLOR_LIGHTBLUE * 16 },
                snBgLggreen = { COLOR_LIGHTGREEN * 16 }, snBgLgshgreen = { COLOR_LIGHTSHALLOWGREEN * 16 },
                snBgLgred = { COLOR_LIGHTRED * 16 }, snBgLgpurple = { COLOR_LIGHTPURPLE * 16 },
                snBgLgyellow = { COLOR_LIGHTYELLOW * 16 }, snBgLgwhite = { COLOR_LIGHTWHITE * 16 },
                snBgClear = { COLOR_BLACK * 16 },
                snClear = { snFgClear + snBgClear };

    std::ostream& operator<<(std::ostream &out, const OutputColor &color);
    const char* getColorCStr(const OutputColor color);
    const std::string getColorStdStr(const OutputColor color);
}

#endif //__SN_COLOR_TABLE_H__