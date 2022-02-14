/***************************************************************************
    Original code written in: May 2006    
    Adapted from Game Programming Gems 4 article by Noel Llopis
 ***************************************************************************/
#ifndef __TIMESOURCE_H__
#define __TIMESOURCE_H__


class TimeSource
{
	public:
		virtual ~TimeSource() {};
		virtual double getTime() const = 0;
};



#endif
