/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "FlockingDemo.h"

#include <iostream>
#include <stdexcept>

using std::cerr;
using std::endl;
using std::runtime_error;


int main(int argc, char** argv)
{
    double fMult = 1.0;
    if (argc > 1) fMult = atof(argv[1]);

    if (fMult<0.2) fMult = 0.2;
    if (fMult>3.0) fMult = 3.0;

    int w = static_cast<int> (fMult*static_cast<double> (SCREEN_WIDTH));
    int h = static_cast<int> (fMult*static_cast<double> (SCREEN_HEIGHT));

    Application*  opApplication = new FlockingDemo(w,h);

    try
    {
        opApplication->init();
        opApplication->run();
        opApplication->shutdown();
    }
    catch (runtime_error error)
    {
        cerr << error.what() << endl;
    }

    return 0;
}
