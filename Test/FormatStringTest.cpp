#include "SNString/FormatString.h"
#include "SNVariant/Variant.h"
#include "SNConfig/Reader/ConfigReader.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace SurgeNight;

int main()
{
    cout << FormatString("%-05.6d %% %012.7f %.6s", {Variant(125), Variant(3.14), Variant(string("Hello"))}) << endl;
    ObjectVariant config = ConfigReader::getConfigFrom("Test/test.ini", ConfigReader::ConfigFormat::CONFIG_FORMAT_INI);
    ObjectVariant data = config["FormatString"].asObject();
    cout << "\nFrom ini ...\n";
    cout << data["format"] << endl << endl;
    vector<Variant> args;
    for (auto i = 0u; i < data["size"].asInt(); ++i) {
        args.push_back(data[string("arg") + to_string(i)]);
    }
    cout << FormatString(data["format"].asString(), args);
    return 0;
}
