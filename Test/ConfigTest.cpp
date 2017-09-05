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
    cout << "az: >" << data["az"].asString() << "<\n"
         << "bs: >" << data["bs"].asDouble() << "<\n"
         << "sd: >" << data["sd"].asInt() << "<\n"
         << "[tag test].fds: >" << data["tag test"].asObject()["fds"].asChar() << "<\n"
         << "[taged].ooo: >" << data["taged"].asObject()["ooo"].asString() << "<\n"
         << endl;
    return 0;
}
