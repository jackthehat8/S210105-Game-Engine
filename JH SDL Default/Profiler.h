#pragma once
#include "Time.h"
#include <string>
#include <vector>


using namespace std;

struct profileSample;

class Profiler
{
public:
	Profiler();
	static Profiler* GetInstance();
	profileSample* GetCurrentSample() { return currentSample; }
	void SetCurrentSample(profileSample* newSample) { currentSample = newSample; }
	int currentFrame = -1;
	void StartFrame();
	void EndFrame();

	void DrawGUI();
private:
	static Profiler* instance;
	profileSample* currentSample;
	vector<profileSample*> frames; //stores the root of each frame

	bool liveFrameGraph = true;
	int selectedFrame = 0;
};

struct profileSample
{
	string name;
	clock_t startTime;
	clock_t endTime;
	int timeDifference;
	profileSample* parent;
	vector<profileSample*> subSamples;

	profileSample(string name_) {
		name = name_;
		startTime = Time::GetInstance()->currentTime();
		parent = Profiler::GetInstance()->GetCurrentSample();
		if (parent != nullptr)
			parent->subSamples.push_back(this);
	}

	void GetFrameData(vector<int> &data) {
		data.push_back(timeDifference);
		for (auto subSample : subSamples) {
			GetFrameData(data);
		}
	}

	void EndSample() {
		endTime = Time::GetInstance()->currentTime();
		timeDifference = 1000*(endTime - startTime)/CLOCKS_PER_SEC;
		Profiler::GetInstance()->SetCurrentSample(parent);
	}
};