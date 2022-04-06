#pragma once
#include "Time.h"
#include <string>
#include <vector>

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <imgui_sdl.h>
#include <imgui_internal.h>


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
	int frameOffset = 0;
};

struct profileSample
{
	string name;
	int startTime;
	int endTime;
	int sampleDuration;
	profileSample* parent;
	vector<profileSample*> subSamples;

	profileSample(string name_) {
		name = name_;
		startTime = 1000 * (Time::GetInstance()->currentTime())/CLOCKS_PER_SEC;
		parent = Profiler::GetInstance()->GetCurrentSample();
		if (parent != nullptr)
			parent->subSamples.push_back(this);
		Profiler::GetInstance()->SetCurrentSample(this);
	}

	void EndSample() {
		endTime = (1000 * (Time::GetInstance()->currentTime())) / CLOCKS_PER_SEC;
		sampleDuration = endTime - startTime;
		Profiler::GetInstance()->SetCurrentSample(parent);
	}

	ImDrawList* DrawSample(profileSample* root, const ImVec2 startPos, ImVec2 canvasRegion, ImDrawList* drawlist, int depth = 0);

	
};