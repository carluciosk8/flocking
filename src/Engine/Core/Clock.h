/***************************************************************************
    Original code written in: May 2006    
    Adapted from Game Programming Gems 4 article by Noel Llopis
 ***************************************************************************/
#ifndef __CLOCK_H__
#define __CLOCK_H__


#include <cstddef>
#include <vector>
#include <deque>

class TimeSource;
class IObserver;


class Clock
{
	public:
		Clock(const TimeSource* pSource = NULL);
		~Clock();
	
		void SetTimeSource(const TimeSource * pSource);
		void FrameStep();
	
		inline double GetTime() const { return m_currentTime; }
		inline double GetFrameDuration() const { return m_frameTime; }
		inline int GetFrameNumber() const { return m_frameNumber; }
		float GetFrameRate() const { return 1.0f/(float)m_frameTime; }
	
		void AddObserver (IObserver * pObserver);
		void RemoveObserver (IObserver * pObserver);
	
		void SetFiltering (int frameWindow, double frameDefault = 0.030);
	
	private:
		double GetExactLastFrameDuration ();
		void AddToFrameHistory (double exactFrameDuration);
		double GetPredictedFrameDuration () const;
	
	
		const TimeSource * m_pTimeSource;
		double m_currentTime;
		double m_frameTime;
		int m_frameNumber;
	
		double m_sourceStartValue;
		double m_sourceLastValue;
	
		int    m_frameFilteringWindow;
		double m_frameDefaultTime;
		std::deque<double> m_frameDurationHistory;
	
		typedef std::vector<IObserver *> ObserverList;
		ObserverList m_observers;
};


#endif
