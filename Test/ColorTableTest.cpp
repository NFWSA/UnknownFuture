#include <iostream>
#include <fstream>
#include "SNLogger/ColorOutput/ColorTable.h"

using namespace std;
using namespace SurgeNight;

int main()
{
    cout << snBg.Red + snFg.Lggreen << "Error:" << snClear << " This is a test!" << endl;
    cout << snBg.Lggreen + snFg.Lgwhite << "Info:" << snClear << " This is an info message..." << endl;
    cerr << snBg.Lgred << "Error:" << snFg.Lgblue << " This is a test!" << endl;
    cerr << snBg.Lggreen + snFg.Lgwhite << "Info:" << snClear << " This is an info message..." << endl;
    ofstream fout("out.txt", fstream::out);
    fout << snBg.Lgred + snFg.Lggreen << "Error:" << snClear << " This is a test!" << endl;
    fout << snBg.Lggreen + snFg.Lgwhite << "Info:" << snClear << " This is an info message..." << endl;
    fout.close();
    return 0;
}
