#pragma once
#include <chrono>
#include <ctime>

//reference https://www.techiedelight.com/measure-elapsed-time-program-chrono-library/

using namespace std;

class Time
{
private:

	static Time* timer;
	//sorted in ms
	clock_t gameStart;
	clock_t frameStart;
	clock_t frameEnd;
	clock_t levelStart;
	//stored in seconds
	float deltaTime = 0.0f;
public:
	Time() { gameStart = clock();};
	~Time() { delete this; }

	static Time* GetInstance();

	clock_t GetStartTime() { return gameStart; };
	clock_t GetFrameStart() { return frameStart; };
	clock_t GetFrameEnd() { return frameEnd; };
	clock_t GetLevelStart() { return levelStart; };

	clock_t currentTime() { return clock(); }

	float GetDeltaTime() { return deltaTime; };
	float GetRunTime() { return (clock() - gameStart)/CLOCKS_PER_SEC; };

	void StartFrame() { frameStart = clock(); };
	void EndFrame();
	void LevelStart() { levelStart = clock (); }

	

	
};

