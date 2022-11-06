#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	//L02: DONE 1: Initialize Player parameters
	//pos = position;
	//texturePath = "Assets/Textures/player/idle1.png";

	//L02: DONE 5: Get Player parameters from XML
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Player::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);

	// L07 DONE 5: Add physics to the player - initialize physics body
	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->listener = this;
	return true;
	pbody->body->SetFixedRotation(true);
}

bool Player::Update()
{

	// L07 DONE 5: Add physics to the player - updated player position using physics

	int speed = 10;
	//Try different values to see which works best
	int jumpspeed = 25;
	//b2Vec2 vel = b2Vec2(0, -GRAVITY_Y); 
	b2Vec2 vel = pbody->body->GetLinearVelocity();
	vel.x = 0;

	if (vel.y > 1)
	{
		CanJump = false;
	}

	//L02: DONE 4: modify the position of the player using arrow keys and render the texture
	if (!app->scene->GetGodmode())
	{
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
			//vel = b2Vec2(0, GRAVITY_Y);

			//for (int i = 0; i < 5;++i)
			if (CanJump)
			{
				CanJump = false;
				pbody->body->ApplyForce(b2Vec2(0, -700), pbody->body->GetWorldCenter(), true);
			}
			else if (CanDoubleJump)
			{
				CanDoubleJump = false;
				vel.y = 0;
				pbody->body->ApplyForce(b2Vec2(0, -700), pbody->body->GetWorldCenter(), true);
			}
			LOG("SPEED %i", vel.y);
			

			//pbody->body->ApplyLinearImpulse(b2Vec2(0, -9999*9999), pbody->body->GetWorldCenter(), true);

		}
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			vel = b2Vec2(0, -(speed + GRAVITY_Y));
			//app->render->camera.y = 0;
			//app->render->camera.x = 0;
			app->render->camera.y += -20;
		}

		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			//vel = b2Vec2(-speed, -GRAVITY_Y);
			vel.x = -speed;
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			//vel = b2Vec2(speed, -GRAVITY_Y);
			vel.x = speed;
		}
	}
	else
	{
		vel.x = 0;
		vel.y = 0 - 0.333334;;
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			vel = b2Vec2(0, -speed);


		}
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			vel = b2Vec2(0, -(speed + GRAVITY_Y));
			app->render->camera.y = 0;
			app->render->camera.x = 0;
		}

		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			//vel = b2Vec2(-speed, -GRAVITY_Y);
			vel.x = -speed;
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			//vel = b2Vec2(speed, -GRAVITY_Y);
			vel.x = speed;
		}
	}


	if (app->physics->ReturnDebug() == false)
	{
		//app->render->camera.x = -position.x + app->render->camera.w / 2;
		//app->render->camera.y = -position.y + app->render->camera.h / 2;

		if (-app->render->camera.x + app->render->camera.w / 2 < position.x + 50)
			app->render->camera.x -= 5;

		if (-app->render->camera.x + app->render->camera.w / 2 > position.x - 50)
			app->render->camera.x += 5;

		//if (-app->render->camera.y + app->render->camera.h / 2 < position.y)
		//	app->render->camera.y -= 20;
		//
		//if (-app->render->camera.y + app->render->camera.h / 2 > position.y)
		//	app->render->camera.y += 20;
		app->render->camera.y = -position.y + app->render->camera.h / 2;
	}

	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	app->render->DrawTexture(texture, position.x, position.y);

	return true;
}

void Player::OnCollision(PhysBody* physA, PhysBody* physB)
{
	//LOG("hi!");
	//LOG(" colliding with: %i", METERS_TO_PIXELS( physB->body->GetTransform().p.y) );

	switch (physB->ctype)
	{
	case ColliderType::PLATFORM:
		//LOG(" colliding gjdsjflluidjfailurfjudi");
		if (METERS_TO_PIXELS(physB->body->GetTransform().p.y) > position.y)
		{
			//LOG(" colliding with: %i vs p: %i", METERS_TO_PIXELS(physB->body->GetTransform().p.y), position.y);
			CanJump = true;
			CanDoubleJump = true;
		}
		break;
	case ColliderType::DANGER:
		//LOG(" colliding gjdsjflluidjfailurfjudi");
		

		break;

	case ColliderType::WIN:
		//LOG(" colliding gjdsjflluidjfailurfjudi");
		


		break;
	default:
		break;
	}
		
		
		
	
}


bool Player::CleanUp()
{

	return true;
}

