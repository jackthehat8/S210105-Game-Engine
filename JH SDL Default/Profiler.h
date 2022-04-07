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

/// The profiler is a tool used to see how long sections of code took to execute to be able to make it more efficient over time
class Profiler
{
public:
	/// This does nothing as all items have default values 
	Profiler();

	/// This gets the Profiler Instance
	static Profiler* GetInstance();

	/// this gets the current sample for the frame
	/// 
	/// This is set to the last started sample to make subSamples of every items called while that sample hasnt ended
	profileSample* GetCurrentSample() { return currentSample; }

	/// This sets the current sample
	/// <param name="newSample">the sample to set it to</param>
	void SetCurrentSample(profileSample* newSample) { currentSample = newSample; }

	/// this is the current frame saved
	/// 
	/// this starts at -1 as during start frame 
	int currentFrame = -1;

	/// Starts the frame 
	/// 
	/// First it is checked that he last frame was ended before the current one starts
	/// currentFrame is incremented by 1
	/// This creates the root node which is the main loop (as this is called at the start of the frame)
	/// This is stored in frames and all other samples are subSamples of it
	/// currentSample is set to the root
	void StartFrame();
	/// Ends the frame
	/// 
	/// First this makes sure all samples have been ended before ending the roots sample
	/// it sets currentSample equal to nullpointer to make sure that the next frame doesnt write to the previous one
	void EndFrame();

	/// Draws the profiler to the performance window
	/// 
	/// This checks if the graph is live
	/// Then calls the DrawSample() of the frame root
	void DrawGUI();

private:
	/// Stores the instance of the Profiler
	static Profiler* instance;
	/// stores the current sample
	profileSample* currentSample;

	/// stores a list of frame roots
	vector<profileSample*> frames; //stores the root of each frame

	/// stores if the flame graph is live
	bool liveFrameGraph = true;
	/// stores the selected frame for the flame graph
	int selectedFrame = 0;

	/// stores the frame offset for a slider
	/// @note this is only used for the slider and has no other use
	int frameOffset = 0;
};

/// This is the storage of a sample of the profiler
struct profileSample
{
	/// name of sample
	string name;
	/// the time the sample started
	/// stored in milliseconds
	int startTime;
	/// the time the sample ended
	/// stored in milliseconds
	int endTime;
	/// the time the sample took to complete
	/// stored in milliseconds
	int sampleDuration;
	/// the parenet of the sample 
	/// (the sample running around this one)
	profileSample* parent;
	/// the storage of subSamples
	/// any samples taken while this sample was running
	vector<profileSample*> subSamples;

	/// <summary>
	/// Creates the profileSample
	/// 
	/// This takes the time it as created as the time the sample should start
	/// the parent is set to the curentSample
	/// This sample is set to be the currentSample
	/// </summary>
	/// <param name="name_"></param>
	profileSample(string name_) {
		name = name_;
		startTime = 1000 * (Time::GetInstance()->currentTime())/CLOCKS_PER_SEC;
		parent = Profiler::GetInstance()->GetCurrentSample();
		if (parent != nullptr)
			parent->subSamples.push_back(this);
		Profiler::GetInstance()->SetCurrentSample(this);
	}

	/// <summary>
	/// This ends the sample
	/// 
	/// This gets the time wehn it was called
	/// it calculates the duration the sample too to be ended
	/// it sets the currentSample to be its parent
	/// </summary>
	void EndSample() {
		endTime = (1000 * (Time::GetInstance()->currentTime())) / CLOCKS_PER_SEC;
		sampleDuration = endTime - startTime;
		Profiler::GetInstance()->SetCurrentSample(parent);
	}

	/// This Draws the flame graph to an ImGui window
	/// 
	/// First it works out the width of the current sample (based on its duration)
	/// it then draws the sample to the screen
	/// then it will recursively call DrawSample for each of its subSamples until all samples have been drawn
	/// once complete it will check if the mouse is over the sample to add a tooltip to the mouse with information of the selected sample
	/// @note the depth should be left to default when ran as it will start at a depth of 0 for the root and build from there (it is used for y spacing of the flame graph)
	/// 
	/// <param name="root">the root of the frame
	/// This is used to be the total time the frame took to complete</param>
	/// <param name="startPos"> the positon that the flame graph should be drawn from</param>
	/// <param name="canvasRegion"> the size of the window for the graph to be drawn within</param>
	/// <param name="drawlist">the function to draw custom rectangles in ImGui</param>
	/// <param name="depth">the current depth into the tree structure</param>
	/// <returns></returns>
	void DrawSample(profileSample* root, const ImVec2 startPos, ImVec2 canvasRegion, ImDrawList* drawlist, int depth = 0);

	
};