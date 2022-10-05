// ----------------------------------------------------
// Timer.cpp
// Body for CPU Tick Timer class
// ----------------------------------------------------

#include "Timer.h"

// ---------------------------------------------
Timer::Timer()
{
	Start();
}

// ---------------------------------------------
void Timer::Start()
{
	
	running = true;
	startingTime = glfwGetTime();
}

// ---------------------------------------------
void Timer::Stop()
{
	running = false;
	stoppingTime = glfwGetTime();
}

// ---------------------------------------------
double Timer::Read()
{
	if(running == true)
	{
		return glfwGetTime() - startingTime;
	}
	else
	{
		return stoppingTime - startingTime;
	}
}


