#include "Transform.h"



Transform::Transform(Vector2f pos, BaseObject* owner_)
{
	position = pos;
	owner = owner_;
	type = TRANSFORM;
}

void Transform::Update()
{
}



void Transform::DrawGui()
{
	if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
		static bool showStepButtons = true;
		const float stepCount = 1.0f;

		ImGui::Text("X");
		ImGui::SameLine(); ImGui::InputFloat("", &position.x, 0.1f, 1.0f);
		ImGui::Text("Y");
		ImGui::SameLine(); ImGui::InputFloat(" ", &position.y, 0.1f, 0.0f);
		//add rotation
		//add scale
		ImGui::TreePop();
	}
}

Vector2f Transform::GetGlobalPos()
{
	if (owner->GetParent() != nullptr)
		return ((Transform*)owner->GetParent()->GetComponent(TRANSFORM))->GetGlobalPos() + position;
	else
		return position;
}

void Transform::SetPosition(int x_, int y_) {
	position.x = x_;
	position.y = y_;
}

void Transform::SetPosition(Vector2f newPos)
{
	position = newPos;
}
