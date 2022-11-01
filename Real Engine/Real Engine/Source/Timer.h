#ifndef __TIMER_H__
#define __TIMER_H__

#include "glew.h"
#include "GLFW/glfw3.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Stop();

	double Read();

private:

	bool	running;
	double	startingTime;
	double	stoppingTime;
};

#endif //__TIMER_H__