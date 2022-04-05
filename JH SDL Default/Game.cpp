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
	mainSystem = System::GetInstance();

	screen = mainSystem->GetScreenManager();
	m_window = screen->getWindow();
	m_renderer = screen->getRenderer();
	updates = mainSystem->GetObjectManager();
	updates->AddRenderer(m_renderer);

	resourceManager = mainSystem->GetResourceManager();
	//main menu
	{
		BaseObject* TitleText = new BaseObject("title text", 350, 75, 0);
		TitleText->AddComponent(new Text("assets/DejaVuSans.ttf", 100, TitleText, "Game Engine Game", { 255,255,255 }));

		BaseObject* playButton = new BaseObject("play button", 550, 275, 0);
		playButton->AddComponent(new Sprite("assets/ButtonBackground.bmp", playButton, 0));
		playButton->AddComponent(new Text("assets/DejaVuSans.ttf", 100, playButton, "PLAY", { 0,0,0 }, {125,50}));
		playButton->AddComponent(new PlayButton(playButton));

		BaseObject* quitButton = new BaseObject("quit button", 550, 550, 0);
		quitButton->AddComponent(new Sprite("assets/ButtonBackground.bmp", quitButton, 0));
		quitButton->AddComponent(new Text("assets/DejaVuSans.ttf", 100, quitButton, "QUIT", { 0,0,0 }, {125,50}));
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

	//main menu
	{
		BaseObject* winText = new BaseObject("win text", 425, 75, 2);
		winText->AddComponent(new Text("assets/DejaVuSans.ttf", 100, winText, "Level Complete", { 255,255,255 }));

		BaseObject* quitButton = new BaseObject("quit button", 550, 550, 2);
		quitButton->AddComponent(new Sprite("assets/ButtonBackground.bmp", quitButton, 0));
		quitButton->AddComponent(new Text("assets/DejaVuSans.ttf", 100, quitButton, "QUIT", { 0,0,0 }, { 125,50 }));
		quitButton->AddComponent(new QuitButton(quitButton));
	}

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

	BaseObject* temp = new BaseObject("temp", 0, 0, 1);
}

Game::~Game()
{

	if (mainSystem) {
		mainSystem->~System();
		delete screen;
	}
};

bool Game::Update(void) {
	Time::GetInstance()->StartFrame();
	Profiler::GetInstance()->StartFrame();
	SDL_RenderClear(m_renderer);
	ImGui::NewFrame();
	ImGui_ImplSDL2_NewFrame(screen->getWindow());

	profileSample* input = new profileSample("poll inputs");
	mainSystem->GetInputManager()->Update();
	input->EndSample();

	profileSample* events = new profileSample("fire events");
	EventManager::GetInstance()->FireEvents(); //fires all the events of the previous
	events->EndSample();

	updates->Update();

	profileSample* ImguiSample = new profileSample("Imgui");
	ImGui::Begin("Show Tools");
	ImGui::Checkbox("", &GUIVisable);
	ImGui::End();

	if (GUIVisable)
	{
		ImGui::ShowDemoWindow(nullptr);

		ImGui::Begin("Performance");
		if (ImGui::TreeNode("Frame Rate")) {
			float* queueTemp = &frames.queue[0];
			ImGui::PlotLines("", queueTemp, frames.queue.size(), 1.0f, "", 0.0f, 0.2f, ImVec2(0, 80.0f));
			char buffer[40];
			snprintf(buffer, sizeof(buffer), "Average Frames: %F seconds", frames.GetAverage());
			ImGui::Text(buffer);
			ImGui::TreePop();
		}
		ImGui::End();

		ImGui::Begin("Editor");
		if (ImGui::Button("Refresh"))
			SearchDirectory();

		ImGui::BeginChild("Content Window", ImVec2(), true);
		for (int i = 0; i < directoryContent.size(); i++)
		{
			ImGui::PushID(directoryContent[i]->name.c_str());

			ImGui::ImageButton((ImTextureID)directoryContent[i]->sprite->GetTexture(), { 100,100 });

			ImGui::PopID();
			if ((i + 1) % 5 != 0)
				ImGui::SameLine();
		}
		ImGui::EndChild();
		ImGui::End();


		ImGui::Begin("Scene Hirarcy", 0);
		ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;
		ObjectManager::GetInstance()->GetSceneRoots()[ObjectManager::GetInstance()->currentScene]->DrawHierarchy(nodeFlags);
		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImguiSample->EndSample();

	SDL_RenderPresent(m_renderer);
	Delay(16);
	int i = 0;
	Profiler::GetInstance()->EndFrame();
	Time::GetInstance()->EndFrame();
	frames.pushFrame(Time::GetInstance()->GetDeltaTime());

	return quit;
}

void Game::Delay(Uint32 ms) {
	SDL_Delay(ms); //takes ms
}

void Game::SearchDirectory()
{
	for (IMGUISprite* object : directoryContent)
	{
		delete(object);
	}
	directoryContent.clear();
	string DirectoryPath = "assets";
	for (const auto& entry : filesystem::directory_iterator(DirectoryPath)) {
		if (entry.path().extension() == ".bmp") {
			IMGUISprite* Asset = new IMGUISprite(entry.path().string().c_str(), new Sprite(entry.path().string().c_str(), nullptr));
			directoryContent.push_back(Asset);
		}
		else if (entry.is_directory()) {
			cout << "dir " << entry << endl;
		}
		cout << entry.path() << endl;
	}
}

ScreenManager* Game::GetScreenManager()
{
	return screen;
}

Game* Game::GetInstance()
{
	//creates a new objectManager class if ones does not exist to be referenced to
	if (instance == NULL)
		instance = new Game();
	return instance;
}


