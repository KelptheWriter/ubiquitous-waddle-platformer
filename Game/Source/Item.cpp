#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "EntityManager.h"

Item::Item() : Entity(EntityType::ITEM)
{
	name.Create("item");
}

Item::~Item() {}

bool Item::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Item::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);
	
	
	// L07 DONE 4: Add a physics to an item - initialize the physics body
	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::ITEM;
	pbody->listener = this;

	return true;
}

bool Item::Update()
{
	if (!app->scene->ShowMenu && is_alive)
	{
		//app->physics->world->DestroyBody(pbody->body);
	//pbody->~PhysBody();
	//app->entityManager->DestroyEntity(this);

	// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  
		position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
		position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

		app->render->DrawTexture(texture, position.x, position.y);
	}
	
	if (!hasBeenDestroyed && !is_alive)
	{
		
		{
			app->physics->world->DestroyBody(pbody->body);
			pbody->~PhysBody();
			app->entityManager->DestroyEntity(this);


			hasBeenDestroyed = true;
		}



	}
	

	return true;
}

void Item::OnCollision(PhysBody* physA, PhysBody* physB)
{
	switch (physB->ctype)
	{
	case ColliderType::PLAYER:

		is_alive = false;

		break;
	case ColliderType::DANGER:

		

		break;

	case ColliderType::WIN:




		break;
	default:
		break;
	}
}

bool Item::CleanUp()
{
	return true;
}