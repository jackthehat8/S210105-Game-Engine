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
	//gets the transform for position and sprite for sprite bounds
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	Sprite* sprite = (Sprite*)(owner->GetComponent(SPRITE));

	topLeft = transfrom->GetGlobalPos(); //position is from the top left

	//sets the extents of the box
	left = topLeft.x;
	top = topLeft.y;
	float width = sprite->GetWidth();
	float height = sprite->GetHeight();
	bottom = topLeft.y + sprite->GetHeight();
	right = topLeft.x + sprite->GetWidth();

	//sets corners based on it
	topRight = Vector2f(right, top);
	bottomLeft = Vector2f(left, bottom);
	bottomRight = Vector2f(right, bottom);

	centre = topLeft + Vector2f(sprite->GetWidth() / 2, sprite->GetHeight() / 2);
	
}

void Physics::Update()
{
	//will only try to move collide and move if the item is set to Dymanic
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

vector <BaseObject*> Physics::CheckForOverlaps(string tag)
{
	UpdateColliderBounds();
	vector <BaseObject*> overlappingObjects;
	for (BaseObject* object : ObjectManager::GetInstance()->GetObjects()) {
		Physics* objPhysics = (Physics*)(object->GetComponent(PHYSICS));
		Sprite* objSprite = (Sprite*)(object->GetComponent(SPRITE));
		//checks that a physics and sprite are on the object (if not move onto the next item)also check that the object is set to overlap 
		if (object == owner || objPhysics == nullptr || objSprite == nullptr || objPhysics->GetOverlapType() == COLLIDE || !objSprite->GetVisability())
			continue;

		objPhysics->UpdateColliderBounds();

		bool overlapping = false;
		//checks if the objcts are overlapping by proof of contradiction
		if (!( (left > objPhysics->GetRight()) || (right < objPhysics->GetLeft()) ||
			   ( top > objPhysics->GetBottom()  ) || ( bottom < objPhysics->GetTop()  ) ))
			overlapping = true;

		if (overlapping) {
			if (tag != "") {//if a tag has been input check that the object has the tag before continue
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
		//checks that a physics and sprite are on the object (if not move onto the next item) also check that the object is set to collide 
		if (object == owner || objPhysics == nullptr || objSprite == nullptr || objPhysics->GetOverlapType() == OVERLAP || !objSprite->GetVisability())
			continue;

		objPhysics->UpdateColliderBounds();

		bool overlapping = false;
		//checks if the objcts are overlapping by proof of contradiction
		if (!((left >= objPhysics->GetRight()) || (right <= objPhysics->GetLeft()) ||
			(top >= objPhysics->GetBottom()) || (bottom <= objPhysics->GetTop())))
			overlapping = true;

		if (overlapping) {
			if (tag != "") {//if a tag has been input check that the object has the tag before continue
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

	//show the forces, physics type and collision type of the object
	if (ImGui::TreeNodeEx("Physics", ImGuiTreeNodeFlags_DefaultOpen)) {
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

		ImGui::TreePop();
	}
}



void Physics::SetLeft(float value)
{
	//sets the left to a value 
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	//this gets the difference between the current left value and where it is getting changed to
	float change = value + bufferDistance - left;
	Vector2f currentPos = transfrom->GetLocalPosition();
	transfrom->SetPosition(currentPos.x + change, currentPos.y);
}

void Physics::SetRight(float value)
{
	//sets the right to a value 
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	Sprite* sprite = (Sprite*)(owner->GetComponent(SPRITE));
	//this gets the difference between the current right value and where it is getting changed to
	float change = value - bufferDistance - right;
	Vector2f currentPos = transfrom->GetLocalPosition();
	transfrom->SetPosition(currentPos.x + change, currentPos.y);
}

void Physics::SetTop(float value)
{
	//sets the top to a value 
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	//this gets the difference between the current top value and where it is getting changed to
	float change = value + bufferDistance - top;
	Vector2f currentPos = transfrom->GetLocalPosition();
	transfrom->SetPosition(currentPos.x, currentPos.y + change);
}

void Physics::SetBottom(float value)
{
	//sets the bottom to a value 
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	Sprite* sprite = (Sprite*)(owner->GetComponent(SPRITE));
	//this gets the difference between the current bottom value and where it is getting changed to
	float change = value - bufferDistance - bottom;
	Vector2f currentPos = transfrom->GetLocalPosition();
	transfrom->SetPosition(currentPos.x, currentPos.y + change);
}
