#pragma once
#include <ctime>

using namespace std;

/// This is used for time in the game
/// 
/// This can be used for timers or for making sure the game runs are the same speed with different frame rates
/// This is useful for the profiler which uses times for how long parts took to run
class Time
{
private:

	/// The instance of the timer
	static Time* timer;
	
	/// The time the game started
	///sorted in milliseconds
	clock_t gameStart;

	/// The start of the frame
	///sorted in milliseconds
	clock_t frameStart;

	/// The end of the frame
	///sorted in milliseconds
	clock_t frameEnd;

	/// The start time of the levl
	///sorted in milliseconds
	clock_t levelStart;

	/// The amount of time the previous frame lasted
	/// Stored in seconds
	float deltaTime = 0.0f;

public:
	/// sets the gameStart Time
	Time() { gameStart = clock();}

	///Destructs nothing as deleting itself is only needed
	~Time() {}

	/// Gets the instance of the time class
	static Time* GetInstance();

	/// gets the start time in milliseconds
	/// <returns>the start time</returns>
	clock_t GetStartTime() { return gameStart; };

	/// gets the frame start in milliseconds
	/// <returns> the frame start</returns>
	clock_t GetFrameStart() { return frameStart; };

	/// gets the frame end in milliseconds
	/// <returns> the frame end</returns>
	clock_t GetFrameEnd() { return frameEnd; };

	/// gets the level start in milliseconds
	/// <returns> the level start</returns>
	clock_t GetLevelStart() { return levelStart; };

	/// Gets the current time in milliseconds
	clock_t currentTime() { return clock(); }

	/// Gets the delta time in seconds
	float GetDeltaTime() { return deltaTime; };
	
	/// Gets how long the game has been running
	float GetRunTime() { return (clock() - gameStart)/CLOCKS_PER_SEC; };

	/// Starts a new frame
	void StartFrame() { frameStart = clock(); };
	/// Ends the current frame
	void EndFrame();
	/// Starts the level timer
	void LevelStart() { levelStart = clock (); }
};

