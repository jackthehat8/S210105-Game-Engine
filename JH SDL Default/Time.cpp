#include "Time.h"

Time* Time::timer = NULL;

Time* Time::GetInstance()
{
	//creates a new Time class if ones does not exist to be referenced to
	if (timer == NULL)
		timer = new Time();
	return timer;
}

void Time::EndFrame()
{
	frameEnd = steady_clock::now();
	deltaTime = duration_cast<milliseconds>(frameEnd - frameStart).count();
	deltaTime /= 1000; //converts to seconds from milliseconds
	if (deltaTime > 1)
		deltaTime = 1;
}

