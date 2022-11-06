#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "TitleScreen.h"
#include "FadeToBlack.h"
#include "Scene.h"


#include "Defs.h"
#include "Log.h"

TitleScreen::TitleScreen() : Module()
{
	name.Create("titlescreen");
}

// Destructor
TitleScreen::~TitleScreen()
{}

// Called before render is available
bool TitleScreen::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;


	return ret;
}

// Called before the first frame
bool TitleScreen::Start()
{
	img = app->tex->Load("Assets/Textures/Platformer Logo.png");

	return true;
}

// Called each loop iteration
bool TitleScreen::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool TitleScreen::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		app->fadetoblack->FadetoBlack(this, app->scene);


	app->render->DrawTexture(img, 300, 150);

	return true;
}

// Called each loop iteration
bool TitleScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool TitleScreen::CleanUp()
{
	LOG("Freeing scene");

	return true;
}