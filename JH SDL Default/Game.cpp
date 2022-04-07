#include "Game.h"
#include "Sprite.h"
#include "Transform.h"
#include "Vector.h"
#include "Player.h"
#include "CameraMovement.h"
#include "EventManager.h";
#include <iostream>
#include "Enemy.h"
#include "Text.h"
#include "QuitButton.h"
#include "PlayButton.h"
#include "Profiler.h"

Game* Game::instance = NULL;

Game::Game() {
	instance = this;
	//create a main system (this makes sure one has created)
	System* mainSystem = System::GetInstance();

	ScreenManager* screen = mainSystem->GetScreenManager();
	
	LoadLevels();

	//initalise imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiSDL::Initialize(screen->getRenderer(), ScreenWidth, ScreenHeight);

	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(screen->getWindow(), nullptr);

	SearchDirectory();
}

Game::~Game()
{
	//system will close all other singletons
	System::GetInstance()->~System();
};

bool Game::Update() {
	//starts the frame for the timer and the profiler
	Time::GetInstance()->StartFrame();
	Profiler::GetInstance()->StartFrame();
	//clears the last screen
	SDL_RenderClear(ScreenManager::GetInstance()->getRenderer());
	//starts a new frame of imgui
	ImGui::NewFrame();
	ImGui_ImplSDL2_NewFrame(ScreenManager::GetInstance()->getWindow());

	//runs inputs
	profileSample* input = new profileSample("poll inputs");
	System::GetInstance()->GetInputManager()->Update();
	input->EndSample();

	profileSample* events = new profileSample("fire events");
	EventManager::GetInstance()->FireEvents(); //fires all the events of the current frame
	events->EndSample();

	//updates all objects
	ObjectManager::GetInstance()->Update();

	//checks if the show tools button has been pressed to make the gui visable or invisable
	profileSample* ImguiSample = new profileSample("Imgui");
	ImGui::Begin("Show Tools", 0, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	if (GUIVisable) {
		if (ImGui::Button("Hide Tools"))
			GUIVisable = false;
	}
	else {
		if (ImGui::Button("Show Tools"))
			GUIVisable = true;
	}
	ImGui::End();

	//draws tools if set to visable
	if (GUIVisable)
	{
		//ImGui::ShowDemoWindow(nullptr);
		DrawPerformanceWindow();
		DrawEditorWindow();
		DrawHierarchyWindow();
	}
	//ends imgui frame
	ImGui::EndFrame();
	ImGui::Render();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImguiSample->EndSample();
	//renders frame
	SDL_RenderPresent(ScreenManager::GetInstance()->getRenderer());
	SDL_Delay(16);//delays
	//ends fame on profiler and timer
	Profiler::GetInstance()->EndFrame();
	Time::GetInstance()->EndFrame();
	frames.pushFrame(Time::GetInstance()->GetDeltaTime());

	return quit; //retuns the value of the bool quit (if true will close the loop)
}

void Game::SearchDirectory()
{
	//delete any already found sprites
	for (IMGUISprite* object : directoryContent)
	{
		delete(object);
	}
	directoryContent.clear();//clears the vector
	string DirectoryPath = "assets";
	//finds every asset in the directory and stores it as an imguiSprite (the fileDirectory and a copy of the surface)
	for (const auto& entry : filesystem::directory_iterator(DirectoryPath)) {
		if (entry.path().extension() == ".bmp") {
			IMGUISprite* Asset = new IMGUISprite(entry.path().string().c_str(), new Sprite(entry.path().string().c_str(), nullptr));
			directoryContent.push_back(Asset);
		}
		else if (entry.is_directory()) {
			cout << "dir " << entry << endl;
		}
	}
}

Game* Game::GetInstance()
{
	//creates a new objectManager class if ones does not exist to be referenced to
	if (instance == NULL)
		instance = new Game();
	return instance;
}

void Game::LoadLevels()
{
	//this constructs all the baseObjects used in the game
	

	//main menu
	{
		BaseObject* TitleText = new BaseObject("title text", 350, 75, 0);
		TitleText->AddComponent(new Text("assets/DejaVuSans.ttf", 100, TitleText, "Game Engine Game", { 255,255,255 }));

		BaseObject* playButton = new BaseObject("play button", 550, 275, 0);
		playButton->AddComponent(new Sprite("assets/ButtonBackground.bmp", playButton, 0));
		playButton->AddComponent(new Text("assets/DejaVuSans.ttf", 100, playButton, "PLAY", { 0,0,0 }, { 125,50 }));
		playButton->AddComponent(new PlayButton(playButton));

		BaseObject* quitButton = new BaseObject("quit button", 550, 550, 0);
		quitButton->AddComponent(new Sprite("assets/ButtonBackground.bmp", quitButton, 0));
		quitButton->AddComponent(new Text("assets/DejaVuSans.ttf", 100, quitButton, "QUIT", { 0,0,0 }, { 125,50 }));
		quitButton->AddComponent(new QuitButton(quitButton));
	}

	//level 1
	{
		BaseObject* camera = new BaseObject("Camera", ScreenWidth / 2, ScreenHeight / 2, 1);
		camera->AddComponent(new CameraMovement(camera, true, false));

		BaseObject* player = new BaseObject("player", 10, ScreenHeight - 124, 1);
		player->AddComponent(new Sprite("assets/Alien.bmp", player, 2, true));
		player->AddComponent(new Physics(player, DYNAMIC, COLLIDE));
		player->AddComponent(new Player(player));

		((Transform*)camera->GetComponent(TRANSFORM))->SetPosition(((Physics*)player->GetComponent(PHYSICS))->GetCentre().x, ScreenHeight / 2);
		camera->SetParent(player);

		BaseObject* startCheckpoint = new BaseObject("start checkpoint", 10, ScreenHeight - 124, 1);
		startCheckpoint->AddComponent(new Sprite("assets/checkpoint.bmp", startCheckpoint, 0, true));
		startCheckpoint->AddComponent(new Physics(startCheckpoint, STATIC, OVERLAP));
		startCheckpoint->AddTag("Checkpoint");

		BaseObject* endDoor = new BaseObject("End Door", ScreenWidth * 2 - 130, ScreenHeight - 200, 1);
		endDoor->AddComponent(new Sprite("assets/Door.bmp", endDoor, -1, true));
		endDoor->AddComponent(new Physics(endDoor, STATIC, OVERLAP));
		endDoor->AddTag("EndDoor");

		BaseObject* key = new BaseObject("key", 2085, 280, 1);
		key->AddComponent(new Sprite("assets/key.bmp", key, 5, true));
		key->AddComponent(new Physics(key, STATIC, OVERLAP));
		key->AddTag("Key");

		BaseObject* floor = new BaseObject("floor", 0, ScreenHeight - 10, 1);
		floor->AddComponent(new Sprite("assets/floor.bmp", floor, 1, true));
		floor->AddComponent(new Physics(floor));
		floor->AddTag("Platform");

		BaseObject* floor2 = new BaseObject("floor", ScreenWidth, ScreenHeight - 10, 1);
		floor2->AddComponent(new Sprite("assets/floor.bmp", floor2, 1, true));
		floor2->AddComponent(new Physics(floor2));
		floor2->AddTag("Platform");

		BaseObject* platform1 = new BaseObject("platform1", 525, 700, 1);
		platform1->AddComponent(new Sprite("assets/platform.bmp", platform1, 1, true));
		platform1->AddComponent(new Physics(platform1));
		platform1->AddTag("Platform");

		BaseObject* enemy1 = new BaseObject("monster", 525, ScreenHeight - 130, 1);
		enemy1->AddComponent(new Sprite("assets/enemy.bmp", enemy1, 3, true));
		enemy1->AddComponent(new Physics(enemy1, DYNAMIC, COLLIDE));
		enemy1->AddComponent(new Enemy(enemy1));

		BaseObject* platform2 = new BaseObject("platform2", 1250, 525, 1);
		platform2->AddComponent(new Sprite("assets/platform.bmp", platform2, 1, true));
		platform2->AddComponent(new Physics(platform2));
		platform2->AddTag("Platform");

		BaseObject* enemy2 = new BaseObject("monster", 1250, ScreenHeight - 130, 1);
		enemy2->AddComponent(new Sprite("assets/enemy.bmp", enemy2, 3, true));
		enemy2->AddComponent(new Physics(enemy2, DYNAMIC, COLLIDE));
		enemy2->AddComponent(new Enemy(enemy2));

		BaseObject* platform3 = new BaseObject("platform3", 1975, 350, 1);
		platform3->AddComponent(new Sprite("assets/platform.bmp", platform3, 1, true));
		platform3->AddComponent(new Physics(platform3));
		platform3->AddTag("Platform");

		BaseObject* enemy3 = new BaseObject("monster", 1975, ScreenHeight - 130, 1);
		enemy3->AddComponent(new Sprite("assets/enemy.bmp", enemy3, 3, true));
		enemy3->AddComponent(new Physics(enemy3, DYNAMIC, COLLIDE));
		enemy3->AddComponent(new Enemy(enemy3));

		BaseObject* startWall = new BaseObject("startWall", -90, 0, 1);
		startWall->AddComponent(new Sprite("assets/wall.bmp", startWall, 1));
		startWall->AddComponent(new Physics(startWall));
		startWall->AddTag("Platform");

		BaseObject* endWall = new BaseObject("endWall", ScreenWidth * 2 - 10, 0, 1);
		endWall->AddComponent(new Sprite("assets/wall.bmp", endWall, 1));
		endWall->AddComponent(new Physics(endWall));
		endWall->AddTag("Platform");
	}

	//complete menu
	{
		BaseObject* winText = new BaseObject("win text", 425, 75, 2);
		winText->AddComponent(new Text("assets/DejaVuSans.ttf", 100, winText, "Level Complete", { 255,255,255 }));

		BaseObject* quitButton = new BaseObject("quit button", 550, 550, 2);
		quitButton->AddComponent(new Sprite("assets/ButtonBackground.bmp", quitButton, 0));
		quitButton->AddComponent(new Text("assets/DejaVuSans.ttf", 100, quitButton, "QUIT", { 0,0,0 }, { 125,50 }));
		quitButton->AddComponent(new QuitButton(quitButton));
	}
}

void Game::DrawPerformanceWindow()
{
	//draws the performace window
	ImGui::Begin("Performance", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	if (ImGui::TreeNodeEx("Frame Rate", ImGuiTreeNodeFlags_DefaultOpen)) {
		//this takes the last 300 frames and displays them in a graph
		//this also outputs the average time it took to complete each frame
		if (frames.queue.size() > 0) {
			float* queueTemp = &frames.queue[0];
			ImGui::PlotLines("", queueTemp, frames.queue.size(), 1.0f, "", 0.0f, 0.2f, ImVec2(0, 80.0f));
			char buffer[40];
			snprintf(buffer, sizeof(buffer), "Average Frames: %F seconds", frames.GetAverage());
			ImGui::Text(buffer);
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Flame Graph", ImGuiTreeNodeFlags_DefaultOpen)) {
		Profiler::GetInstance()->DrawGUI();//this calls drawGui in the profiler to make a flame graph
		ImGui::TreePop();
	}
	ImGui::End();
}

void Game::DrawEditorWindow()
{
	ImGui::Begin("Editor", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	if (ImGui::Button("Refresh"))
		SearchDirectory();//allows for updating the asset list if a new item is added while it is running

	//this displays all assets found in the assets folder for the user to be able to drag into the game
	ImGui::BeginChild("Content Window", ImVec2(), true);
	for (int i = 0; i < directoryContent.size(); i++)
	{
		ImGui::PushID(directoryContent[i]->name.c_str());

		ImGui::ImageButton((ImTextureID)directoryContent[i]->sprite->GetTexture(), { 100,100 });

		//if item is dragged it is set as the content being dragged and is shown as an image next to the mouse
		if (ImGui::BeginDragDropSource()) {
			contentBeingDragged = directoryContent[i];
			ImGui::Image((ImTextureID)directoryContent[i]->sprite->GetTexture(), { 100,100 });
			ImGui::EndDragDropSource();
		}

		ImGui::PopID();
		if ((i + 1) % 10 != 0)
			ImGui::SameLine();
	}

	//if the item is let go of it is placed into the game at the position of the mouse
	if (contentBeingDragged != nullptr && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		BaseObject* newObject = new BaseObject(contentBeingDragged->name.c_str(), x, y, ObjectManager::GetInstance()->currentScene);
		newObject->AddComponent(new Sprite(contentBeingDragged->name.c_str(), newObject));
		contentBeingDragged = nullptr;
	}

	ImGui::EndChild();
	ImGui::End();
}

void Game::DrawHierarchyWindow()
{
	//draws the hierarchy to the screen
	ImGui::Begin("Scene Hirarcy", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;
	//calls drawHierarchy of each object of the current scene
	ObjectManager::GetInstance()->GetSceneRoots()[ObjectManager::GetInstance()->currentScene]->DrawHierarchy(nodeFlags);
	ImGui::End();
}


