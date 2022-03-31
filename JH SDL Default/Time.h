#pragma once
#include <chrono>

//reference https://www.techiedelight.com/measure-elapsed-time-program-chrono-library/

using namespace std::chrono;

class Time
{
private:

	static Time* timer;
	//sorted in ms
	time_point<steady_clock> gameStart;
	time_point<steady_clock> frameStart;
	time_point<steady_clock> frameEnd;
	time_point<steady_clock> levelStart;
	//stored in seconds
	float deltaTime = 0.0f;
public:
	Time() { gameStart = steady_clock::now();};
	~Time() { delete this; }

	static Time* GetInstance();

	time_point<steady_clock> GetStartTime() { return gameStart; };
	time_point<steady_clock> GetFrameStart() { return frameStart; };
	time_point<steady_clock> GetFrameEnd() { return frameEnd; };
	time_point<steady_clock> GetLevelStart() { return levelStart; };

	time_point<steady_clock> currentTime() { return steady_clock::now(); }

	float GetDeltaTime() { return deltaTime; };
	int GetRunTime() { return duration_cast<microseconds>(steady_clock::now() - gameStart).count(); };

	void StartFrame() { frameStart = steady_clock::now(); };
	void EndFrame();
	void LevelStart(){ levelStart = steady_clock::now(); }

	

	
};

