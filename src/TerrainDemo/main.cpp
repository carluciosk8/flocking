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
    Application*  opApplication = new FlockingDemo;
    
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
