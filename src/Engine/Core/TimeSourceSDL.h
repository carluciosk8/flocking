/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __TIMESOURCESDL_H__
#define __TIMESOURCESDL_H__


#include "TimeSource.h"

class TimeSourceSDL : public TimeSource
{
    public:
        TimeSourceSDL();
        ~TimeSourceSDL();

   	    virtual double getTime() const;
};


#endif
