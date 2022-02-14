/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "TimeSourceHRLinux.h"


TimeSourceHRLinux::TimeSourceHRLinux()
{
    gettimeofday(&start_time, (struct timezone*)0);
}


double TimeSourceHRLinux::getTime() const
{
    struct timeval end_time;

    gettimeofday(&end_time, (struct timezone*)0);

    return (end_time.tv_usec-start_time.tv_usec)*0.000001 + (end_time.tv_sec-start_time.tv_sec);
}
