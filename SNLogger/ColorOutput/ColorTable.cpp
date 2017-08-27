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
    unsigned int bg = color.color / 16, fg = color.color % 16;
    int ret = 0;
#if defined WIN32 || defined WIN64
    if (&out == &std::cout || &out == &std::cerr) {
        unsigned int rlt = 0;
        HANDLE handle = ::GetStdHandle(&out == &std::cout ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE);
        if (bg != 0)
            rlt += bg * 16;
        if (fg != 0)
            rlt += fg;
        ret = SetConsoleTextAttribute(handle, rlt);
    }
#endif
    if (ret == 0 && (&out == &std::cout || &out == &std::cerr))
        out << getColorStdStr(color);
    return out;
}

const char* getColorCStr(const OutputColor color)
{
    return getColorStdStr(color).c_str();
}

const std::string getColorStdStr(const OutputColor color)
{
    unsigned int bg = color.color / 16, fg = color.color % 16;
    if (bg == 0 && fg == 0) {
        return "\e[0m";
    }
    std::string clr("\e[0;");
    unsigned int tmp = 0;
    //if (bg != 0) {
        tmp = 40 + color2Unix[bg % 8];
        if (bg / 8 == 1)
            clr += "5;";
        clr += std::to_string(tmp);
    //}
    if (clr[clr.size() - 1] != ';')
        clr += ';';
    //if (fg != 0) {
        tmp = 30 + color2Unix[fg % 8];
        if (fg / 8 == 1)
            clr += "1;";
        clr += std::to_string(tmp);
    //}
    clr += 'm';
    return clr;
}


}
