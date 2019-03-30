#pragma once
#include <Windows.h>
#include "ConsolePrint.h"

#define DESIRED_FPS 60.0
#define DESIRED_FPS_MS (1000.0 / DESIRED_FPS)
#define MAX_FPS (3 * DESIRED_FPS_MS)

static float m_LastFrameTime;
static LARGE_INTEGER m_StartingTime;

class Timer
{

public:

	static float calcLastFrameTime() 
	{
			
		LARGE_INTEGER EndingTime;
		LARGE_INTEGER ElapsedMicroseconds;
		LARGE_INTEGER Frequency;

		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&EndingTime);
		if (m_StartingTime.QuadPart == NULL)
		{
			m_StartingTime = EndingTime;
		}
		ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - m_StartingTime.QuadPart;
		ElapsedMicroseconds.QuadPart *= 100000;
		ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

		m_StartingTime = EndingTime;

		m_LastFrameTime = (float)ElapsedMicroseconds.QuadPart;

		if (m_LastFrameTime > MAX_FPS)
		{
			//DEBUG_PRINT("More than Desired: %f", m_LastFrameTime  );
			return MAX_FPS;
		}
		return m_LastFrameTime;
	}

private:
	
};

