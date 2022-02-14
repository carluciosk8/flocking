/***************************************************************************
    Original code written in: May 2006    
    Adapted from Game Programming Gems 4 article by Noel Llopis
 ***************************************************************************/
#ifndef __OBSERVER_H__
#define __OBSERVER_H__


class IObserver
{
	public:
		virtual ~IObserver() {}
		virtual void notify() = 0;
};


#endif
