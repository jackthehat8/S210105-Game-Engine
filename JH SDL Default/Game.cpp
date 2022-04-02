#include "Game.h"
#include "Sprite.h"
#include "Transform.h"
#include "Vector.h"
#include "Player.h"
#include "CameraMovement.h"
#include "EventManager.h";
#include <iostream>

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

	EventManager* eventManager = EventManager::GetInstance();

	monster = new BaseObject("monster", 100, 100);
	monster->AddComponent(new Sprite("assets/monster.bmp", monster, 3));
	monster->AddComponent(new Physics(monster, DYNAMIC, COLLIDE));

	monsterTrans = new BaseObject("monster purple", 150, 100);
	monsterTrans->AddComponent(new Sprite("assets/monsterTrans.bmp", monsterTrans, 0));

	monsterTransKeyed = new BaseObject("monster transparent", 125, 50);
	monsterTransKeyed->AddComponent(new Sprite("assets/monsterTrans.bmp", monsterTransKeyed, 2, true));
	monsterTransKeyed->AddComponent(new Physics(monsterTransKeyed, DYNAMIC, COLLIDE));
	monsterTransKeyed->AddComponent(new Player(monsterTransKeyed));
	eventManager->AddListener("Left", monsterTransKeyed);
	eventManager->AddListener("Right", monsterTransKeyed);
	eventManager->AddListener("Up", monsterTransKeyed);

	BaseObject* camera = new BaseObject("Camera", ((Physics*)monsterTransKeyed->GetComponent(PHYSICS))->GetCentre().x, ScreenHeight/2);
	camera->AddComponent(new CameraMovement(camera, true, false));
	camera->SetParent(monsterTransKeyed);

	floor = new BaseObject("floor", 0, ScreenHeight-10);
	floor->AddComponent(new Sprite("assets/floor.bmp", floor, 1));
	floor->AddComponent(new Physics(floor));
	floor->AddTag("Platform");

	startWall = new BaseObject("startWall", -90,0);
	startWall->AddComponent(new Sprite("assets/wall.bmp", startWall, 1));
	startWall->AddComponent(new Physics(startWall));
	startWall->AddTag("Platform");

	endWall = new BaseObject("endWall", ScreenWidth-10, 0);
	endWall->AddComponent(new Sprite("assets/wall.bmp", endWall, 1));
	endWall->AddComponent(new Physics(endWall));
	endWall->AddTag("Platform");



	//Transform* temp = (Transform*)monsterTrans->GetComponent(TRANSFORM);
	monsterTrans->SetParent(monster);

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
	/*m_pSmallFont = resourceManager->LoadFont("assets/DejaVuSans.ttf", 15);
	m_pBigFont = resourceManager->LoadFont("assets/DejaVuSans.ttf", 50);*/
}

Game::~Game()
{
	TTF_CloseFont(m_pBigFont);
	TTF_CloseFont(m_pSmallFont);

	if (monsterTransKeyed) {
		delete monsterTransKeyed;
	}
	if (monsterTrans) {
		delete monsterTrans;
	}
	if (monster) {
		delete monster;
	}
	if (mainSystem) {
		mainSystem->~System();
		delete screen;
	}
};

void Game::Update(void) {
	Time::GetInstance()->StartFrame();
	SDL_RenderClear(m_renderer);
	ImGui::NewFrame();
	ImGui_ImplSDL2_NewFrame(screen->getWindow());
	EventManager::GetInstance()->FireEvents(); //fires all the events of the previous

	//((Transform*)monster->GetComponent(TRANSFORM))->SetPosition(((Transform*)monster->GetComponent(TRANSFORM))->GetLocalPosition() + Vector2f(0.1, 0));
	//((Physics*)monster->GetComponent(PHYSICS))->AddForce(Vector2f(0.1, 0));
	updates->Update();

	mainSystem->GetInputManager()->Update();

	ImGui::Begin("Hide Gui");
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
		ObjectManager::GetInstance()->GetSceneRoot()->DrawHierarchy(nodeFlags);
		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());

	/*UpdateText("Small Red", 50, 10, m_pSmallFont, { 255,0,0 });
	UpdateText("Small Blue", 50, 40, m_pSmallFont, { 0,0,255 });

	char char_array[] = "Big White";
	UpdateText(char_array, 50, 140, m_pBigFont, { 255,255,255 });

	string myString = "Big Green";
	UpdateText(myString, 50, 70, m_pBigFont, { 0,255,0 });

	int testNumber = 1234;
	string testString = "Test Number: ";
	testString += to_string(testNumber);
	UpdateText(testString, 50, 210, m_pBigFont, { 255,255,255 });*/

	SDL_RenderPresent(m_renderer);
	Delay(16);
	int i = 0;
	Time::GetInstance()->EndFrame();
	frames.pushFrame(Time::GetInstance()->GetDeltaTime());
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


void Game::UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour) {
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	int texW = 0;
	int texH = 0;

	surface = TTF_RenderText_Solid(font, msg.c_str(), colour);

	if (!surface) {
		printf("SURFACE for font not loaded! \n");
		printf("%s\n", SDL_GetError());
	}
	else {
		texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		if (!texture) {
			printf("SURFACE for font not loaded! \n");
			printf("%s\n", SDL_GetError());
		}
		else {
			SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
			SDL_Rect textRect = { x, y, texW, texH };
			
			SDL_RenderCopy(m_renderer, texture, NULL, &textRect);
		}
	}
	if (texture)
		SDL_DestroyTexture(texture);
	if (surface)
		SDL_FreeSurface(surface);
}