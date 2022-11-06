#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "TitleScreen.h"
#include "LogoScreen.h"
#include "FadeToBlack.h"
#include "Scene.h"


#include "Defs.h"
#include "Log.h"

LogoScreen::LogoScreen() : Module()
{
	name.Create("logoscreen");
}

// Destructor
LogoScreen::~LogoScreen()
{}

// Called before render is available
bool LogoScreen::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool LogoScreen::Start()
{
	img = app->tex->Load("Assets/Textures/Ubiquitous Waddle Logo.png");

	return true;
}

// Called each loop iteration
bool LogoScreen::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool LogoScreen::Update(float dt)
{

	app->render->DrawTexture(img, 300, 150);

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	//	app->fadetoblack->FadetoBlack(this, app->titleScreen);

	return true;
}

// Called each loop iteration
bool LogoScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool LogoScreen::CleanUp()
{
	LOG("Freeing scene");

	return true;
}