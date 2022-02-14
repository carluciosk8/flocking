/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef TIMESOURCEHRLINUX_H_
#define TIMESOURCEHRLINUX_H_


#include "TimeSource.h"

#include <sys/time.h>

class TimeSourceHRLinux : public TimeSource
{
public:
    TimeSourceHRLinux();
    virtual double getTime() const;

private:
    struct timeval start_time;
};


#endif
