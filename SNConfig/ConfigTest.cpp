#include "Reader/ConfigReader.h"
#include <string>
#include <iostream>

using namespace std;
using namespace SurgeNight;

int main()
{
    string str;
    cin >> str;
    ConfigData data = ConfigReader::getConfigFrom(str, ConfigReader::ConfigFormat::CONFIG_FORMAT_INI);
    cout << data.getString("az") << ' ' << data.getDouble("bs") << ' ' << data.getInt("sd") << endl;
    return 0;
}
