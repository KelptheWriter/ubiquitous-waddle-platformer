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
#include "EntityManager.h"

Enemy::Enemy() : Entity(EntityType::ENEMY)
{
	name.Create("Enemy");

	idleAnim.PushBack({ 0, 0, 75, 37});
	idleAnim.PushBack({ 75, 0, 75, 37 });

	idleAnim.speed = 0.1f;

	dieAnim.PushBack({ 75 * 2, 0, 75, 37 });
	dieAnim.PushBack({ 75 * 2, 0, 75, 37 });
	dieAnim.PushBack({ 75 * 2, 0, 75, 37 });

	dieAnim.speed = 0.1f;
	dieAnim.loop = false;
}

Enemy::~Enemy() {

}

bool Enemy::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	flying = parameters.attribute("flying").as_bool();
	texturePath = parameters.attribute("texturepath").as_string();
	//this->type = type;

	return true;
}

bool Enemy::Start() {

	texture = app->tex->Load(texturePath);
	currentAnimation = &idleAnim;

	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::ENEMY;
	pbody->body->SetFixedRotation(true);

	is_alive = true;

	return true;
}

bool Enemy::Update()
{
	//LOG("I am here %d", position.x);

	int speed = 10;
	int jumpspeed = 25;
	b2Vec2 vel = pbody->body->GetLinearVelocity();
	vel.x = 0;

	if (vel.y > 1)
	{
		CanJump = false;
	}

	pbody->body->SetLinearVelocity(vel);

	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	app->pathfinding->CreatePath(position, app->scene->player->position);

	const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

	int i = 0;

	while (position != app->scene->player->position) {

		position.x = path->At(i)->x;
		position.y = path->At(i)->y;

	}

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x - 20, position.y, &rect);
	currentAnimation->Update();

	return true;
}

void Enemy::OnCollision(PhysBody* physA, PhysBody* physB)
{

	LOG(" I AM A TOASTER");

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

	case ColliderType::PLAYER:

		if (METERS_TO_PIXELS((physB->body->GetTransform().p.y) < METERS_TO_PIXELS(physA->body->GetTransform().p.y) - 20) && is_alive)
		{
			LOG("DEAD");
			is_alive = false;

			currentAnimation = &dieAnim;
			currentAnimation->Reset();
		}

		//physB->body->GetTransform().p.y < physA->body->GetTransform().p.y
		

		break;
	default:
		break;
	}




}

bool Enemy::LoadState(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	pbody->body->SetTransform(b2Vec2(position.x, position.y), 0);

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
