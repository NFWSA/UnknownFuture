#include "FormatString.h"
#include "SNVariant/Variant.h"
#include "SNStateMachine/StateMachine.h"
#include <sstream>
#include <iomanip>

namespace SurgeNight
{

namespace impl
{
    enum {
        ID_BEGIN,
        ID_ALIGN_LEFT, ID_ALIGN_RIGHT,
        ID_FILL_SPACE, ID_FILL_ZERO,
        ID_WIDTH, ID_WIDTH_CUSTOM,
        ID_PRECISION_BEG, ID_PRECISION, ID_PRECISION_CUSTOM,
        ID_TYPE_DECOR, ID_TYPE
    };
    decltype(auto) getFormatMachine()
    {
        static StateMachine<short, char> machine {
            ID_BEGIN, ID_ALIGN_LEFT, ID_ALIGN_RIGHT, ID_FILL_SPACE, ID_FILL_ZERO,
            ID_WIDTH, ID_WIDTH_CUSTOM, ID_PRECISION_BEG, ID_PRECISION, ID_PRECISION_CUSTOM, ID_TYPE_DECOR, ID_TYPE
        };
        if (!machine.isLock()) {
            std::initializer_list<char> numList = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' },
                nozeroNumList = { '1', '2', '3', '4', '5', '6', '7', '8', '9' },
                typeDecorList = { 'h', 'l', 'j', 'z', 't', 'L' },
                typeList = { 'c', 's', 'd', 'i', 'o', 'x', 'X', 'u', 'f', 'F', 'e', 'E', 'a', 'A', 'g', 'G', 'n', 'p' };

            machine.addTransTable(ID_BEGIN, {
                {'-', ID_ALIGN_LEFT}, { '+', ID_ALIGN_RIGHT },
                {' ', ID_FILL_SPACE}, { '0', ID_FILL_ZERO },
                {'*', ID_WIDTH_CUSTOM}, {'.', ID_PRECISION_BEG}
            });
            machine.addTransTable(ID_BEGIN, ID_WIDTH, nozeroNumList);
            machine.addTransTable(ID_BEGIN, ID_TYPE_DECOR, typeDecorList);
            machine.addTransTable(ID_BEGIN, ID_TYPE, typeList);

            machine.addTransTable(ID_ALIGN_LEFT, {
                {' ', ID_FILL_SPACE}, { '0', ID_FILL_ZERO },
                {'*', ID_WIDTH_CUSTOM}, {'.', ID_PRECISION_BEG}
            });
            machine.addTransTable(ID_ALIGN_RIGHT, {
                {' ', ID_FILL_SPACE}, { '0', ID_FILL_ZERO },
                {'*', ID_WIDTH_CUSTOM}, {'.', ID_PRECISION_BEG}
            });
            machine.addTransTable(ID_ALIGN_LEFT, ID_WIDTH, nozeroNumList);
            machine.addTransTable(ID_ALIGN_LEFT, ID_TYPE_DECOR, typeDecorList);
            machine.addTransTable(ID_ALIGN_LEFT, ID_TYPE, typeList);
            machine.addTransTable(ID_ALIGN_RIGHT, ID_WIDTH, nozeroNumList);
            machine.addTransTable(ID_ALIGN_RIGHT, ID_TYPE_DECOR, typeDecorList);
            machine.addTransTable(ID_ALIGN_RIGHT, ID_TYPE, typeList);

            machine.addTransTable(ID_FILL_SPACE, { {'*', ID_WIDTH_CUSTOM}, {'.', ID_PRECISION_BEG} });
            machine.addTransTable(ID_FILL_ZERO, { {'*', ID_WIDTH_CUSTOM}, {'.', ID_PRECISION_BEG} });
            machine.addTransTable(ID_FILL_SPACE, ID_WIDTH, nozeroNumList);
            machine.addTransTable(ID_FILL_SPACE, ID_TYPE_DECOR, typeDecorList);
            machine.addTransTable(ID_FILL_SPACE, ID_TYPE, typeList);
            machine.addTransTable(ID_FILL_ZERO, ID_WIDTH, nozeroNumList);
            machine.addTransTable(ID_FILL_ZERO, ID_TYPE_DECOR, typeDecorList);
            machine.addTransTable(ID_FILL_ZERO, ID_TYPE, typeList);

            machine.addTransTable(ID_WIDTH_CUSTOM, ID_PRECISION_BEG, {'.'});
            machine.addTransTable(ID_WIDTH_CUSTOM, ID_TYPE_DECOR, typeDecorList);
            machine.addTransTable(ID_WIDTH_CUSTOM, ID_TYPE, typeList);

            machine.addTransTable(ID_WIDTH, ID_WIDTH, numList);
            machine.addTransTable(ID_WIDTH, ID_PRECISION_BEG, {'.'});
            machine.addTransTable(ID_WIDTH, ID_TYPE_DECOR, typeDecorList);
            machine.addTransTable(ID_WIDTH, ID_TYPE, typeList);

            machine.addTransTable(ID_PRECISION_BEG, ID_PRECISION, nozeroNumList);
            machine.addTransTable(ID_PRECISION_BEG, ID_TYPE_DECOR, typeDecorList);
            machine.addTransTable(ID_PRECISION_BEG, ID_TYPE, typeList);
            machine.addTransTable(ID_PRECISION_BEG, ID_PRECISION_CUSTOM, { '*' });

            machine.addTransTable(ID_PRECISION_CUSTOM, ID_TYPE_DECOR, typeDecorList);
            machine.addTransTable(ID_PRECISION_CUSTOM, ID_TYPE, typeList);

            machine.addTransTable(ID_PRECISION, ID_PRECISION, numList);
            machine.addTransTable(ID_PRECISION, ID_TYPE_DECOR, typeDecorList);
            machine.addTransTable(ID_PRECISION, ID_TYPE, typeList);

            machine.addTransTable(ID_TYPE_DECOR, ID_TYPE_DECOR, typeDecorList);
            machine.addTransTable(ID_TYPE_DECOR, ID_TYPE, typeList);

            machine.finish();
        }
        return machine;
    }
}

FormatString::FormatString(const std::string &content, std::initializer_list<Variant> args) : FormatString(content, std::vector<Variant>(args))
{

}

FormatString::FormatString(const std::string &content, const std::vector<Variant> &args)
{
    m_str.reserve(content.size() * 1.2f);
    std::string tmp;
    std::ostringstream out, cached;
    auto machine = impl::getFormatMachine();
    machine.reset();
    bool formating = false;
    auto arg = args.begin();
    short wstep = 0; // 1 width 2 precision
    short precision = 0, width = 0;
    for (auto i = 0u; i < content.size(); ++i) {
        if (!formating) {
            if ('%' != content[i]) {
                out << content[i];
                continue;
            }
            ++i;
            if (i >= content.size())
                break;
            formating = true;
            precision = 0;
            width = 0;
        }
        auto ch = content[i];
        if ('%' == ch) {
            out << '%';
            formating = false;
            continue;
        }
        if (!machine(ch)) {
            formating = false;
            machine.reset();
            // TODO need to do something
            continue;
        }
        if (machine.is(impl::ID_ALIGN_LEFT))
            out << std::left;
        else if (machine.is(impl::ID_ALIGN_RIGHT))
            out << std::right;
        else if (machine.is(impl::ID_FILL_SPACE))
            out << std::setfill(' ');
        else if (machine.is(impl::ID_FILL_ZERO))
            out << std::setfill('0');
        else if (machine.is(impl::ID_WIDTH)) {
            wstep = 1;
            cached << ch;
        }
        else if (machine.is(impl::ID_WIDTH_CUSTOM)) {
            if (arg != args.end()) {
                width = arg->asInt();
                ++arg;
            }
        }
        else if (machine.is(impl::ID_PRECISION)) {
            if (1 == wstep) {
                width = std::stoi(cached.str());
                cached.str("");
                wstep = 0;
            }
            cached << ch;
            wstep = 2;
        }
        else if (machine.is(impl::ID_PRECISION_CUSTOM)) {
            if (1 == wstep) {
                width = std::stoi(cached.str());
                cached.str("");
                wstep = 0;
            }
            if (arg != args.end()) {
                precision = arg->asInt();
                ++arg;
            }
        }
        else if (machine.is(impl::ID_TYPE_DECOR)) {
            if (1 == wstep) {
                width = std::stoi(cached.str());
                cached.str("");
                wstep = 0;
            }
            else if (2 == wstep) {
                precision = std::stoi(cached.str());
                cached.str("");
                wstep = 0;
            }
        }
        else if (machine.is(impl::ID_TYPE)) {
            if (1 == wstep) {
                width = std::stoi(cached.str());
                cached.str("");
                wstep = 0;
            }
            else if (2 == wstep) {
                precision = std::stoi(cached.str());
                cached.str("");
                wstep = 0;
            }
            formating = false;
            machine.reset();
            if (arg != args.end()){
                out << std::setw(width) << std::setprecision(precision);
                auto fill = out.fill();
                if (out.left & out.flags())
                    out << std::setfill(' ');
                if ('f' == ch)
                    out << std::fixed << arg->asDouble() << std::defaultfloat;
                else if ('e' == ch)
                    out << std::scientific << arg->asDouble() << std::defaultfloat;
                else if ('E' == ch)
                    out << std::scientific << std::uppercase<< arg->asDouble() << std::nouppercase << std::defaultfloat;
                else if ('d' == ch || 'i' == ch) {
                    if (precision != 0) {
                        cached << std::setw(precision) << std::setfill('0') << arg->asInt() << std::setfill(' ');
                        out << std::setfill(' ') << cached.str();
                        cached.str("");
                    }
                    else
                        out << arg->asInt();
                }
                else if ('o' == ch)
                    out << std::oct << arg->asInt() << std::dec;
                else if ('x' == ch)
                    out << std::hex << arg->asInt() << std::dec;
                else if ('X' == ch)
                    out << std::hex << std::uppercase << arg->asInt() << std::dec << std::nouppercase;
                else if ('c' == ch)
                    out << arg->asChar();
                else if ('s' == ch)
                    out << arg->asString();
                ++arg;
                out << std::right << std::setfill(' ');// << std::setprecision(6);
            }
        }
    }
    m_str = out.str();
}

std::ostream& operator<<(std::ostream &out, const FormatString &str)
{
    return out << str.m_str;
}

}
