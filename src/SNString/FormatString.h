#ifndef SN_FORMAT_STRING_H
#define SN_FORMAT_STRING_H

#include <initializer_list>
#include <string>
#include <vector>

namespace SurgeNight
{

class Variant;

class FormatString
{
public:
    FormatString(const std::string &content, std::initializer_list<Variant> args);
    FormatString(const std::string &content, const std::vector<Variant> &args);
    ~FormatString() = default;

    friend std::ostream& operator<<(std::ostream &out, const FormatString &str);

private:
    std::string m_str;
};

}

#endif // SN_FORMAT_STRING_H
