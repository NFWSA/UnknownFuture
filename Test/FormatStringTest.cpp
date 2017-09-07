#include "SNString/FormatString.h"
#include "SNVariant/Variant.h"
#include "SNConfig/Reader/ConfigReader.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using namespace SurgeNight;

int main()
{
    cout << FormatString("%-05.6d %% %012.7f %.6s", {Variant(125), Variant(3.14), Variant(string("Hello"))}) << endl;
    ObjectVariant config = ConfigReader::getConfigFrom("Test/test.ini", ConfigReader::ConfigFormat::CONFIG_FORMAT_INI);
    ObjectVariant data = config["FormatString"].asObject();
    cout << "\nFrom ini ...\n";
    cout << data["format"] << endl;
    vector<Variant> args;
    for (auto i = 0u; i < data["size"].asInt(); ++i) {
        args.push_back(data[string("arg") + to_string(i)]);
    }
    cout << FormatString(data["format"].asString(), args) << endl;
    cout << "\nFrom input file ...\n";
    ifstream fin("Test/format.in", fstream::in);
    string line, str;
    int n;
    while (getline(fin, line)) {
        cout << line << endl;
        fin >> n;
        args.clear();
        while (n-- > 0) {
            fin >> str;
            args.push_back(toVariant(str));
        }
        cout << FormatString(line, args) << endl;
        fin >> std::ws;
    }
    fin.close();
    return 0;
}
