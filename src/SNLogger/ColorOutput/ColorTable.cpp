#include "ColorTable.h"
#include <string>
#include <iostream>
#if defined WIN32 || defined WIN64
#include <windows.h>
#endif

const unsigned int color2Unix[] = { 0, 4, 2, 6, 1, 5, 3, 7 };

namespace SurgeNight
{

const OutputColor OutputColor::operator+(const OutputColor &clr) const
{
    return OutputColor { color + clr.color };
}

std::ostream& operator<<(std::ostream &out, const OutputColor &color)
{
    int ret = 0;
#if defined WIN32 || defined WIN64
    if (&out == &std::cout || &out == &std::cerr) {
        HANDLE handle = ::GetStdHandle(&out == &std::cout ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE);
        //CONSOLE_SCREEN_BUFFER_INFO csbi;
        //GetConsoleScreenBufferInfo(handle, &csbi);
        ret = SetConsoleTextAttribute(handle, getWinColorAttr(color));//, OutputColor{ csbi.wAttributes }));
    }
#endif
    if (ret == 0 && (&out == &std::cout || &out == &std::cerr))
        out << getANSIColorStr(color);
    return out;
}

const bool setConsoleColor(const OutputColor &color)
{
#warning note: Please use ostream& << snOutputColor.
    return false;
}

const std::string getANSIColorStr(const OutputColor &color)
{
    unsigned int bg = color.color / 17, fg = color.color % 17;
    if (bg == 0 && fg == 0) {
        return "\e[0m";
    }
    std::string clr("\e[0;");
    unsigned int tmp = 0;
    if (bg != 0) {
        tmp = 40 + color2Unix[(bg - 1) % 8];
        if ((bg - 1) / 8 == 1)
            clr += "5;";
        clr += std::to_string(tmp);
    }
    if (fg != 0) {
        if (clr[clr.size() - 1] != ';')
            clr += ';';
        tmp = 30 + color2Unix[(fg - 1) % 8];
        if ((fg - 1) / 8 == 1)
            clr += "1;";
        clr += std::to_string(tmp);
    }
    clr += 'm';
    return clr;
}

const unsigned int getWinColorAttr(const OutputColor &color, const OutputColor &oriColor)
{
    unsigned int rlt = 0;
    unsigned int bg = color.color / 17, fg = color.color % 17;
    unsigned int obg = oriColor.color / 16, ofg = oriColor.color % 16;
    if (bg == 0 && fg == 0) {
        rlt = snBg.Clear.color * 16 - 17 + snFg.Clear.color;
    }
    else {
        if (bg != 0)
            rlt += bg * 16 - 16;
        else
            rlt += obg * 16;
        if (fg != 0)
            rlt += fg - 1;
        else
            rlt += ofg;
    }
    return rlt;
}

}
