//#include "GameObject.h"
//#include "ResourceManager.h"
//#include <imgui.h>
//#include <backends/imgui_impl_sdl.h>
//#include <imgui_sdl.h>
//#include <imgui_internal.h>
//
//GameObject::GameObject(const char* name_, ObjectManager* updates, ResourceManager* resourceManager_, SDL_Renderer* renderer, std::string fileName, bool addToUpdateCall , RenderLayers newLayer, bool useTransparency, GameObject* parent_)
//{
//	name = (char*)name_;
//	parent = parent_;
//	resourceManager = resourceManager_;
//	m_Renderer = renderer;
//	screenLayer = newLayer;
//
//	m_pbitmapSurface = resourceManager->LoadImage(fileName);
//	if (!m_pbitmapSurface) {
//		printf("SURFACE fro bitmap %s not loaded\n", fileName.c_str());
//		printf("%s\n", SDL_GetError());
//	}
//	else {
//		if (useTransparency) {
//			Uint32 colourKey = SDL_MapRGB(m_pbitmapSurface->format, 255, 0, 255);
//			SDL_SetColorKey(m_pbitmapSurface, SDL_TRUE, colourKey);
//		}
//
//		m_pbitmapTexture = SDL_CreateTextureFromSurface(m_Renderer, m_pbitmapSurface);
//		if (!m_pbitmapTexture) {
//			printf("TEXTURE for bitmap %s not loaded\n", fileName.c_str());
//			printf("%s\n", SDL_GetError());
//		}
//	}
//
//	if(addToUpdateCall)
//		updates->AddObjects(this);
//}
//
//GameObject::~GameObject() 
//{
//	if (m_pbitmapTexture)
//		SDL_DestroyTexture(m_pbitmapTexture);
//}
//
//void GameObject::SetPosition(int x_, int y_) {
//	position.x = x_;
//	position.y = y_;
//}
//
//void GameObject::SetPosition(Vector2f newPos)
//{
//	position = newPos;
//}
//
//void GameObject::PreRender()
//{
//}
//
//void GameObject::Render()
//{
//	if (m_pbitmapTexture && m_pbitmapSurface) {
//		Vector2f temp = GetGlobalPos();
//		SDL_Rect destRect = { temp.x,temp.y,m_pbitmapSurface->w,m_pbitmapSurface->h };
//		SDL_RenderCopy(m_Renderer, m_pbitmapTexture, NULL, &destRect);
//	}
//}
//
//void GameObject::PostRender()
//{
//}
//
//bool GameObject::CheckIfClicked()
//{
//	SDL_Point mousePos;
//	mousePos.x = ImGui::GetIO().MousePos.x;
//	mousePos.y = ImGui::GetIO().MousePos.y;
//	SDL_Rect spriteShape = { GetGlobalPos().x, GetGlobalPos().y, m_pbitmapSurface->w,m_pbitmapSurface->h };
//
//	if (SDL_PointInRect(&mousePos, &spriteShape) && ImGui::GetIO().MouseClicked[0]) {
//		ObjectManager::GetInstance()->SetSelectedObject(this);
//		ObjectManager::GetInstance()->SetHeldObject(this);
//		return true;
//	}
//
//	return false;
//}
//
//void GameObject::OnMouseDown() 
//{
//
//}
//
//void GameObject::OnMouseHeld() 
//{
//	if (parent == nullptr) {
//		position.x += ImGui::GetIO().MouseDelta.x;
//		position.y += ImGui::GetIO().MouseDelta.y;
//	}
//	else {
//		Vector2f globalPos = GetGlobalPos();
//		globalPos.x += ImGui::GetIO().MouseDelta.x;
//		globalPos.y += ImGui::GetIO().MouseDelta.y;
//
//		position = globalPos - parent->GetGlobalPos();
//	}
//
//}
//
//void GameObject::OnMouseUp() 
//{
//	
//}
//
//void GameObject::DrawGui()
//{
//	//draw gui stuff
//	ImGui::Begin("Inspector");
//	ImGui::InputText("Name", name, IM_ARRAYSIZE(name));
//	if (ImGui::TreeNode("Transform")) {
//		static bool showStepButtons = true;
//		const float stepCount = 1.0f;
//
//		ImGui::Text("X");
//		ImGui::SameLine(); ImGui::InputFloat("", &position.x, 0.1f, 1.0f);
//		ImGui::Text("Y");
//		ImGui::SameLine(); ImGui::InputFloat(" ", &position.y, 0.1f, 0.0f);
//		//add rotation
//		//add scale
//		ImGui::TreePop();
//	}
//	if (ImGui::TreeNode("RenderLayer")) {
//		const char* layers[LAYERS_NUM] = { "Background","Platforms","Enemies","Player","Ui" };
//		const char* combo_preview_value = layers[screenLayer];  // Pass in the preview value visible before opening the combo (it could be anything)
//		if (ImGui::BeginCombo("   ", combo_preview_value))
//		{
//			for (int n = 0; n < IM_ARRAYSIZE(layers); n++)
//			{
//				const bool is_selected = (screenLayer == n);
//				if (ImGui::Selectable(layers[n], is_selected))
//					screenLayer = (RenderLayers)n;
//				if (is_selected)
//					ImGui::SetItemDefaultFocus();
//			}
//			ImGui::EndCombo();
//		}
//		ImGui::TreePop();
//	}
//	ImGui::End();
//}
//
//void GameObject::HandleEvent(BaseEvent* event)
//{
//}
//
//
//
