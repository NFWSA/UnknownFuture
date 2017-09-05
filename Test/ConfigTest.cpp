#include "SNConfig/Reader/ConfigReader.h"
#include <string>
#include <iostream>

using namespace std;
using namespace SurgeNight;

int main()
{
    string str;
    cin >> str;
    ObjectVariant data = ConfigReader::getConfigFrom(str, ConfigReader::ConfigFormat::CONFIG_FORMAT_INI);
    cout << "------------------ get config data manually ------------" << endl;
    cout << "az: >" << data["az"].asString() << "<\n"
         << "bs: >" << data["bs"].asDouble() << "<\n"
         << "sd: >" << data["sd"].asInt() << "<\n"
         << "[tag test].fds: >" << data["tag test"].asObject()["fds"].asChar() << "<\n"
         << "[taged].ooo: >" << data["taged"].asObject()["ooo"].asString() << "<\n"
         << endl;
    cout << "----------------- auto ergod config -------------------" << endl;
    cout << "--------------------- main part -----------------------" << endl;
    for (auto &item : data) {
        if (item.second.isObject())
            continue;
        cout << " key:>" << item.first << "<  -  value:>" << item.second << "<" << endl;
    }
    for (auto &item : data) {
        if (!item.second.isObject())
            continue;
        cout << "----------------- >" << item.first <<  "< parts ------------------" << endl;
        for (auto &x : item.second.asObject()) {
            cout << " key:>" << x.first << "<  -  value:>" << x.second << "<" << endl;
        }
    }
    cout << "--------------------- auto format outpu -----------------------" << endl;
    cout << data << endl;
    return 0;
}
