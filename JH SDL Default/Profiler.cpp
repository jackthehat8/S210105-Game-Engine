#include "Profiler.h"
#include <SDL.h>
#include <string>

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
	currentSample = nullptr;
}

void Profiler::DrawGUI()
{
	if (frames.size() > 2) {
		ImGui::Checkbox("Live Flame Graph", &liveFrameGraph);
		if (liveFrameGraph)
			selectedFrame = frames.size() - 2; // get last frame (before this frame)
		else {
			ImGui::SliderInt("frames", &frameOffset, 0, frames.size() - 2 - 100);
			//ImGui::SameLine();
			ImGui::Text(("Frames " + to_string(frameOffset) + " - " + to_string(frameOffset + 100)).c_str());
			ImGui::SliderInt("sampleFrames", &selectedFrame, frameOffset, frameOffset + 100);
		}

		ImDrawList* drawlist = ImGui::GetCurrentWindow()->DrawList;

		ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
		ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
		if (canvas_sz.x < 50.0f)
			canvas_sz.x = 50.0f;
		if (canvas_sz.y)
			canvas_sz.y = 50.0f;
		ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

		frames[selectedFrame]->DrawSample(frames[selectedFrame], canvas_p0, canvas_sz, drawlist);

	}
}

void profileSample::DrawSample(profileSample* root, const ImVec2 startPos , ImVec2 canvasRegion, ImDrawList* drawlist, int depth)
{
	float blockStart = (startTime - root->startTime);
	float blockEnd = (blockStart + sampleDuration+1)/root->sampleDuration;
	blockStart /= root->sampleDuration; //done after block end so that its math works properly
	
	ImVec2 recMin = { startPos.x + blockStart * canvasRegion.x,startPos.y + canvasRegion.y-50+30*depth };
	ImVec2 recMax = { startPos.x + blockEnd * canvasRegion.x,recMin.y+30 };
	
	drawlist->AddRectFilled(recMin, recMax, ImGui::GetColorU32(ImGuiCol_PlotHistogram) & 0x77FFFFFF, GImGui->Style.FrameRounding);

	drawlist->AddRect(recMin, recMax, ImGui::GetColorU32(ImGuiCol_PlotHistogram) & 0x7FFFFFFF);

	///ImGui::RenderText(ImVec2(recMin.x + 5, recMin.y + 5), name.c_str());

	depth++;
	for (auto sample : subSamples) {
		sample->DrawSample(root, startPos, canvasRegion, drawlist, depth);
	}
	depth--;

	SDL_Point mousePos;
	mousePos.x = ImGui::GetIO().MousePos.x;
	mousePos.y = ImGui::GetIO().MousePos.y;

	if (!(recMin.x > mousePos.x || recMax.x < mousePos.x ||
		recMin.y > mousePos.y || recMax.y < mousePos.y))
	{
		ImGui::SetTooltip((name + "\n" + to_string(sampleDuration) + "ms").c_str());
	}
}
