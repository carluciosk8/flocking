/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "TimeSourceHRWin32.h"
#include <windows.h>



TimeSourceHRWin32::TimeSourceHRWin32()
{
    LARGE_INTEGER freq;
    ::QueryPerformanceFrequency(&freq);
    m_secsPerTick = 1.0/freq.QuadPart;
}


double TimeSourceHRWin32::getTime() const
{
    LARGE_INTEGER time;
    ::QueryPerformanceCounter(&time);
    return time.QuadPart * m_secsPerTick;
}

