#include <iostream>
#include <fstream>
#include "SNLogger/ColorOutput/ColorTable.h"

using namespace std;
using namespace SurgeNight;

int main()
{
    cout << snBgRed + snFgLggreen << "Error:" << snClear << " This is a test!" << endl;
    cout << snBgLggreen + snFgLgwhite << "Info:" << snClear << " This is an info message..." << endl;
    cerr << snBgRed + snFgLggreen << "Error:" << snClear << " This is a test!" << endl;
    cerr << snBgLggreen + snFgLgwhite << "Info:" << snClear << " This is an info message..." << endl;
    ofstream fout("out.txt", fstream::out);
    fout << snBgRed + snFgLggreen << "Error:" << snClear << " This is a test!" << endl;
    fout << snBgLggreen + snFgLgwhite << "Info:" << snClear << " This is an info message..." << endl;
    fout.close();
    return 0;
}
