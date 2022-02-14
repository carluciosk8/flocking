/***************************************************************************
    Original code written in: May 2006    
    Adapted from Game Programming Gems 4 article by Noel Llopis
 ***************************************************************************/
#include "Timer.h"
#include "Clock.h"


Timer::Timer(Clock& clock) :
    m_clock (clock),
    m_currentTime (0),
    m_frameTime (0),
    m_bPaused (false),
    m_fScale (1.0f)
{
    m_clock.AddObserver(this);
}



Timer::~Timer()
{
    m_clock.RemoveObserver(this);
}



void Timer::notify ()
{
    if (!m_bPaused)
    {
        m_frameTime = m_clock.GetFrameDuration() * m_fScale;
        m_currentTime += m_frameTime;
    }
	else
		m_frameTime = 0;
}
