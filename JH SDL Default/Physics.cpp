#include "Physics.h"
#include "Sprite.h"
#include "Transform.h"
#include "Time.h"

Physics::Physics(BaseObject* owner_, PhysicsType physType_, OverlapType overlapType_)
{
	owner = owner_;
	physType = physType_;
	type = PHYSICS;
	overlapType = overlapType_;

	if (owner->GetComponent(SPRITE) == nullptr) { //check there is a sprite component to get collider bounds from
		delete(this);
	}

	UpdateColliderBounds();
}

void Physics::UpdateColliderBounds()
{
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	Sprite* sprite = (Sprite*)(owner->GetComponent(SPRITE));

	topLeft = transfrom->GetGlobalPos(); //position is from the top left

	left = topLeft.x;
	top = topLeft.y;
	float width = sprite->GetWidth();
	float height = sprite->GetHeight();
	bottom = topLeft.y + sprite->GetHeight();
	right = topLeft.x + sprite->GetWidth();

	topRight = Vector2f(right, top);
	bottomLeft = Vector2f(left, bottom);
	bottomRight = Vector2f(right, bottom);

	centre = topLeft + Vector2f(sprite->GetWidth() / 2, sprite->GetHeight() / 2);
	
}

void Physics::Update()
{
	if (physType == DYNAMIC) {
		forces.y = forces.y + gravity * Time::GetInstance()->GetDeltaTime();//add gravity


		Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));

		transfrom->SetXPosition(transfrom->GetLocalPosition().x + forces.x);
		//check for collisions in x
		for (BaseObject* object : CheckForCollisions()) {
			Physics* objPhysics = (Physics*)(object->GetComponent(PHYSICS));
			if (!owner->HasTag("Platform") && object->HasTag("Platform")) {
				Vector2f objCentre = objPhysics->GetCentre();
				if (centre.x > objCentre.x) //object to the right of the collision
					SetLeft(objPhysics->GetRight());
				else
					SetRight(objPhysics->GetLeft());
				forces.x = 0;
			}
		}


		transfrom->SetYPosition(transfrom->GetLocalPosition().y + forces.y);
		//check for collisions in y
		for (BaseObject* object : CheckForCollisions()) {
			Physics* objPhysics = (Physics*)(object->GetComponent(PHYSICS));
			if (!owner->HasTag("Platform") && object->HasTag("Platform")) {
				Vector2f objCentre = objPhysics->GetCentre();
				if (centre.y > objCentre.y) //lower then other object
					SetTop(objPhysics->GetBottom());
				else 
					SetBottom(objPhysics->GetTop());
				forces.y = 0;
			}
		}
	}

	
}


/// <summary>
///  if tag is set to "" it will return all overlapping objects
/// </summary>
/// <param name="tag"></param>
/// <returns></returns>
vector <BaseObject*> Physics::CheckForOverlaps(string tag)
{
	UpdateColliderBounds();
	vector <BaseObject*> overlappingObjects;
	for (BaseObject* object : ObjectManager::GetInstance()->GetObjects()) {
		Physics* objPhysics = (Physics*)(object->GetComponent(PHYSICS));
		Sprite* objSprite = (Sprite*)(object->GetComponent(SPRITE));
		if (object == owner || objPhysics == nullptr || objSprite == nullptr || objPhysics->GetOverlapType() == COLLIDE || !objSprite->GetVisability())
			continue;

		objPhysics->UpdateColliderBounds();

		bool overlapping = false;
		//checks if the objcts are overlapping by proof of contradiction
		if (!( (left > objPhysics->GetRight()) || (right < objPhysics->GetLeft()) ||
			   ( top > objPhysics->GetBottom()  ) || ( bottom < objPhysics->GetTop()  ) ))
			overlapping = true;

		if (overlapping) {
			if (tag != "") {
				if (object->HasTag(tag))
					overlappingObjects.push_back(object);
			}
			else
				overlappingObjects.push_back(object);
		}
	}
	return overlappingObjects;
}

vector<BaseObject*> Physics::CheckForCollisions(string tag)
{
	UpdateColliderBounds();
	vector <BaseObject*> collidingObjects;
	for (BaseObject* object : ObjectManager::GetInstance()->GetObjects()) {
		Physics* objPhysics = (Physics*)(object->GetComponent(PHYSICS));
		Sprite* objSprite = (Sprite*)(object->GetComponent(SPRITE));
		if (object == owner || objPhysics == nullptr || objSprite == nullptr || objPhysics->GetOverlapType() == OVERLAP || !objSprite->GetVisability())
			continue;

		objPhysics->UpdateColliderBounds();

		bool overlapping = false;
		//checks if the objcts are overlapping by proof of contradiction
		if (!((left >= objPhysics->GetRight()) || (right <= objPhysics->GetLeft()) ||
			(top >= objPhysics->GetBottom()) || (bottom <= objPhysics->GetTop())))
			overlapping = true;

		if (overlapping) {
			if (tag != "") {
				if (object->HasTag(tag))
					collidingObjects.push_back(object);
			}
			else
				collidingObjects.push_back(object);
		}
	}
	return collidingObjects;
}

void Physics::DrawGui()
{
	ImGui::Text(("Forces: X: " + to_string(forces.x) + " Y: " + to_string(forces.y)).c_str());

	ImGui::Text("Physics Type");
	ImGui::SameLine();
	if (physType == DYNAMIC)
		ImGui::Text("Dynamic");
	else
		ImGui::Text("Static");

	ImGui::Text("Collision Type: ");
	ImGui::SameLine(); 
	if (overlapType == COLLIDE)
		ImGui::Text("Collide");
	else
		ImGui::Text("Overlap");
}



void Physics::SetLeft(float value)
{
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	float change = value + bufferDistance - left;
	Vector2f currentPos = transfrom->GetLocalPosition();
	transfrom->SetPosition(currentPos.x + change, currentPos.y);
}

void Physics::SetRight(float value)
{
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	Sprite* sprite = (Sprite*)(owner->GetComponent(SPRITE));
	float change = value - bufferDistance - right;
	Vector2f currentPos = transfrom->GetLocalPosition();
	transfrom->SetPosition(currentPos.x + change, currentPos.y);
}

void Physics::SetTop(float value)
{
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	float change = value + bufferDistance - top;
	Vector2f currentPos = transfrom->GetLocalPosition();
	transfrom->SetPosition(currentPos.x, currentPos.y + change);
}

void Physics::SetBottom(float value)
{
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	Sprite* sprite = (Sprite*)(owner->GetComponent(SPRITE));
	float change = value - bufferDistance - bottom;
	Vector2f currentPos = transfrom->GetLocalPosition();
	transfrom->SetPosition(currentPos.x, currentPos.y + change);
}
