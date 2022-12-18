#include "Enemy.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Pathfinding.h"

Enemy::Enemy() : Entity(EntityType::ENEMY)
{
	name.Create("Enemy");
}

Enemy::~Enemy() {

}

bool Enemy::Awake(EnemyType* type) {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	this->type = type;

	return true;
}

bool Enemy::Start() {

	texture = app->tex->Load(texturePath);

	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->listener = this;
	return true;
	pbody->body->SetFixedRotation(true);
}

bool Enemy::Update()
{

	int speed = 10;
	int jumpspeed = 25;
	b2Vec2 vel = pbody->body->GetLinearVelocity();
	vel.x = 0;

	if (vel.y > 1)
	{
		CanJump = false;
	}

	pbody->body->SetLinearVelocity(vel);

	app->pathfinding->CreatePath(position, app->scene->player->position);

	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	app->render->DrawTexture(texture, position.x, position.y);

	return true;
}

void Enemy::OnCollision(PhysBody* physA, PhysBody* physB)
{



	switch (physB->ctype)
	{
	case ColliderType::PLATFORM:

		if (METERS_TO_PIXELS(physB->body->GetTransform().p.y) > position.y)
		{

			CanJump = true;
			CanDoubleJump = true;
		}
		break;
	case ColliderType::DANGER:



		break;

	case ColliderType::WIN:




		break;
	default:
		break;
	}




}

bool Enemy::LoadState(pugi::xml_node& data)
{
	//position.x = data.child("position").attribute("x").as_int();
	//position.y = data.child("position").attribute("y").as_int();

	//pbody->body->SetTransform(b2Vec2(position.x, position.y), 0);

	return true;
}

bool Enemy::SaveState(pugi::xml_node& data)
{
	pugi::xml_node nme = data.append_child("position");

	nme.append_attribute("x") = position.x;
	nme.append_attribute("y") = position.y;



	return true;
}


bool Enemy::CleanUp()
{

	return true;
}
