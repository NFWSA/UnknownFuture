#include "SNString/FormatString.h"
#include "SNVariant/Variant.h"
#include <iostream>
#include <string>

using namespace std;
using namespace SurgeNight;

int main()
{
    cout << FormatString("%-05.6d %% %012.7f %.6s", {Variant(125), Variant(3.14), Variant(string("Hello"))}) << endl;
    return 0;
}
