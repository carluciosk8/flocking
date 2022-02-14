/***************************************************************************
    Original code written in: May 2006    
    Adapted from Game Programming Gems 4 article by Noel Llopis
 ***************************************************************************/
#ifndef __TIMER_H__
#define __TIMER_H__


#include "Observer.h"


class Clock;

class Timer : private IObserver
{
	public:
		Timer(Clock & clock);
		virtual ~Timer();
	
		inline double getTime() const  { return m_currentTime; }
		inline double getFrameDuration() const  { return m_frameTime; }
	
		void pause (bool bOn)  { m_bPaused = bOn; }
		void setScale (float fScale)  { m_fScale = fScale; }   
		
		bool isPaused () const  { return m_bPaused; }
		float getScale () const  { return m_fScale; }
	
	
	private:
		virtual void notify();
		
		Clock & m_clock;
	
		double  m_currentTime;
		double  m_frameTime;
	
		bool    m_bPaused;
		float   m_fScale;
};



#endif
