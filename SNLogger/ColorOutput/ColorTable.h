#ifndef __SN_COLOR_TABLE_H__
#define __SN_COLOR_TABLE_H__

#include <ostream>

namespace SurgeNight
{

    enum ColorTable {
        COLOR_CLEAR = 0,
        COLOR_BLACK = 1,
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
    struct {
        OutputColor Black = { COLOR_BLACK },          Blue = { COLOR_BLUE },
                    Green = { COLOR_GREEN },          Shgreen = { COLOR_SHALLOWGREEN },
                    Red = { COLOR_RED },              Purple = { COLOR_PURPLE },
                    Yellow = { COLOR_YELLOW },        White = { COLOR_WHITE },
                    Gray = { COLOR_GRAY },            Lgblue = { COLOR_LIGHTBLUE },
                    Lggreen = { COLOR_LIGHTGREEN },   Lgshgreen = { COLOR_LIGHTSHALLOWGREEN },
                    Lgred = { COLOR_LIGHTRED },       Lgpurple = { COLOR_LIGHTPURPLE },
                    Lgyellow = { COLOR_LIGHTYELLOW }, Lgwhite = { COLOR_LIGHTWHITE },
                    Clear = { COLOR_WHITE };
    } snFg;
    struct {
        OutputColor Black = { COLOR_BLACK * 17 },          Blue = { COLOR_BLUE * 17 },
                Green = { COLOR_GREEN * 17 },          Shgreen = { COLOR_SHALLOWGREEN * 17 },
                Red = { COLOR_RED * 17 },              Purple = { COLOR_PURPLE * 17 },
                Yellow = { COLOR_YELLOW * 17 },        White = { COLOR_WHITE * 17 },
                Gray = { COLOR_GRAY * 17 },            Lgblue = { COLOR_LIGHTBLUE * 17 },
                Lggreen = { COLOR_LIGHTGREEN * 17 },   Lgshgreen = { COLOR_LIGHTSHALLOWGREEN * 17 },
                Lgred = { COLOR_LIGHTRED * 17 },       Lgpurple = { COLOR_LIGHTPURPLE * 17 },
                Lgyellow = { COLOR_LIGHTYELLOW * 17 }, Lgwhite = { COLOR_LIGHTWHITE * 17 },
                Clear = { COLOR_BLACK * 17 };
    } snBg;
    static OutputColor snClear = { COLOR_CLEAR };

    std::ostream& operator<<(std::ostream &out, const OutputColor &color);
    const bool setConsoleColor(const OutputColor &color);
    const std::string getANSIColorStr(const OutputColor &color);
    const unsigned int
    getWinColorAttr(const OutputColor &color,
                    const OutputColor &oriColor = OutputColor{
                        snClear.color + snBg.Clear.color * 16 - 17 + snFg.Clear.color});
    }

#endif //__SN_COLOR_TABLE_H__
