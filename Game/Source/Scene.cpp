#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"
#include "Player.h"
#include "Pathfinding.h"
#include "Enemy.h"
#include "GuiManager.h"


#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	// iterate all objects in the scene
	// Check https://pugixml.org/docs/quickstart.html#access
	for (pugi::xml_node itemNode = config.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	{
		Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
		item->parameters = itemNode;
	}
	for (pugi::xml_node itemNode = config.child("enemy"); itemNode; itemNode = itemNode.next_sibling("enemy"))
	{
		Enemy* enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
		enemy->parameters = itemNode;
	}

	//L02: DONE 3: Instantiate the player using the entity manager
	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	player->parameters = config.child("player");

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	//img = app->tex->Load("Assets/Textures/test.png");
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");

	// L03: DONE: Load map
	bool retLoad = app->map->Load();

	// L04: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width,
		app->map->mapData.height,
		app->map->mapData.tileWidth,
		app->map->mapData.tileHeight,
		app->map->mapData.tilesets.Count());

	app->win->SetTitle(title.GetString());

//<<<<<<< Updated upstream
//=======
	//note: find where 'data' should come from

	if (retLoad) {
		int w, h;
		uchar* data = NULL;

		bool retWalkMap = app->map->CreateWalkabilityMap(w, h, &data);

		if (retWalkMap) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

	}

//>>>>>>> Stashed changes

	uint w, h;
	app->win->GetWindowSize(w, h);
	button1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Play     ", { (int)w / 2 - 300,(int)h / 2 - 30,100,20 }, this);
	button2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Settings", { (int)w / 2 - 300,(int)h / 2,100,20 }, this);
	button3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Credits  ", { (int)w / 2 - 300,(int)h / 2 + 30,100,20 }, this);
	button4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Exit       ", { (int)w / 2 - 300,(int)h / 2 + 60,100,20 }, this);

	button5 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Credits X: ", { (int)w / 2 + 100,(int)h / 2 - 200,100,20 }, this);
	button6 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Settingss X:", { (int)w / 2 + 100,(int)h / 2 - 50,100,20 }, this);
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	//Godmode currently is just bool var inside player, change things accordingly afterward
	
	

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {

		SetGodmode();
		button1->bounds.h = 0;
		button1->bounds.w = 0;

	}

	// L03: DONE 3: Request App to Load / Save when pressing the keys F5 (save) / F6 (load)


	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		app->physics->SetDebug();

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y += 10;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y -= 10;

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x += 10;

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x -= 10;



	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map
	app->map->Draw();


	if (ShowMenu)
	{
		SDL_Rect rect;
		rect.h = 10000;
		rect.w = 10000;
		rect.x = -20;
		rect.y = -20;

		app->render->DrawRectangle(rect, 0, 0, 0, 255, true, true);

		app->guiManager->Draw();

		if (ShowCredits)
		{
			app->render->DrawText("created by Kaede Sato and Sergio Garriguez under MIT licence", 500, 220, 350, 30, { 255,255,255 });
			button5->bounds.w = 100;
			button5->bounds.h = 20;
		}
		else
		{
			button5->bounds.w = 0;
			button5->bounds.h = 0;
		}
		if (ShowSettings)
		{

			button6->bounds.w = 100;
			button6->bounds.h = 20;
		}
		else
		{
			button6->bounds.w = 0;
			button6->bounds.h = 0;
		}

	}
	else
	{
		button1->bounds.w = 0;
		button1->bounds.h = 0;
		button2->bounds.w = 0;
		button2->bounds.h = 0;
		button3->bounds.w = 0;
		button3->bounds.h = 0;
		button4->bounds.w = 0;
		button4->bounds.h = 0;
		button5->bounds.w = 0;
		button5->bounds.h = 0;
		button6->bounds.w = 0;
		button6->bounds.h = 0;
	}
	
	//app->render->DrawText("created by Kaede Sato and Sergio Garriguez under MIT licence", 500, 220, 350, 30, { 255,255,255 });

	return true;
}

bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{
	// L15: DONE 5: Implement the OnGuiMouseClickEvent method
	LOG("Event by %d ", control->id);

	switch (control->id)
	{
	case 1:
		LOG("Button 1 click");
		ShowMenu = false;
		break;
	case 2:
		LOG("Button 2 click");
		ShowSettings = true;
		break;
	case 3:
		ShowCredits = true;
		break;
	case 4:
		Quit = true;
		break;
	case 5:
		ShowCredits = false;
		break;
	case 6:
		ShowSettings = false;
		break;
	}

	return true;
}
// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	else if (Quit)
	{
		ret = false;
	}

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool Scene::GetGodmode()
{
	return godmode;
}

void Scene::SetGodmode()
{
	if (godmode)
	{
		godmode = false;
	}
	else
	{
		godmode = true;
	}
}
