#ifndef TIMER_H
#define TIMER_H

//#include <SDL/SDL.h>


class CTimer
{
	public:

		void Init();
		float GetFPS(unsigned int uiFrames = 1);
		float GetMS();
		float GetSeconds();


	private:
		float m_fInvTicksPerSec;
		float m_fInvTicksPerMs;
//		__int64 m_i64StartTime;
//		__int64 m_i64LastTime;
};



inline void CTimer::Init()
{
//	__int64 i64Freq = 0;
//    ::QueryPerformanceFrequency((LARGE_INTEGER *)&i64Freq);
 //   ::QueryPerformanceCounter((LARGE_INTEGER *)&m_i64StartTime);
//	m_fInvTicksPerSec = (float)1/i64Freq;
//	m_fInvTicksPerMs = (float)1000/i64Freq;
//	m_i64LastTime = 0;
//	GetMS();
}



inline float CTimer::GetFPS(unsigned int uiFrames)
{
// 	static __int64 sLastTime = m_i64StartTime;
// 	__int64 i64NewTime = 0;
 	float fElapsedSecs = 0.00333;
//     ::QueryPerformanceCounter((LARGE_INTEGER *)&i64NewTime);
// 	fElapsedSecs = (i64NewTime - sLastTime) * m_fInvTicksPerSec;
// 	sLastTime = i64NewTime;
//
 	return (uiFrames / fElapsedSecs);
}



inline float CTimer::GetMS()
{
	return 10.0;
}



inline float CTimer::GetSeconds()
{
	return (float)(GetMS() * 0.001f);
}

#endif
