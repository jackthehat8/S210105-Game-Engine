#include "Profiler.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <imgui_sdl.h>
#include <imgui_internal.h>

Profiler* Profiler::instance = NULL;

Profiler::Profiler()
{
}

Profiler* Profiler::GetInstance()
{
	//creates a new Screen Manager class if ones does not exist to be referenced to
	if (instance == NULL)
		instance = new Profiler();
	return instance;
}

void Profiler::StartFrame()
{
	if (currentFrame > -1 && frames[currentFrame]->endTime == 0) { //checks the previous frame has been ended before starting a new one (does not want to happen first frame)
		EndFrame();
	}
	currentFrame++;
	profileSample* root = new profileSample("Main Loop");
	frames.push_back(root);
	currentSample = root;
}

void Profiler::EndFrame()
{
	while (currentSample != frames[currentFrame]) {
		currentSample->EndSample();
	}
	frames[currentFrame]->EndSample();
	bool hello = true;
}

void Profiler::DrawGUI()
{
	ImGui::BeginChild("Profiler");
	ImGui::Checkbox("Life Flame Graph", &liveFrameGraph);
	if (liveFrameGraph)
		selectedFrame = frames.size() - 1; // get last frame
	else {
		ImGui::SliderInt("frames", &selectedFrame, 0, frames.size());
	}

	vector<int> data;
	frames[selectedFrame]->GetFrameData(data);


	ImGui::EndChild();
}


