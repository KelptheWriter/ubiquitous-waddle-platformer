#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Item.h"
#include "GuiButton.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void SetGodmode();

	bool GetGodmode();

	bool godmode = false;

	bool Quit = false;
	bool ShowCredits = false;
	bool ShowSettings = false;
	bool ShowMenu = true;

	bool OnGuiMouseClickEvent(GuiControl* control);

public:

	//L02: DONE 3: Declare a Player attribute 
	Player* player;

private:
	SDL_Texture* img;

	GuiButton* button1;
	GuiButton* button2;
	GuiButton* button3;
	GuiButton* button4;

	GuiButton* button5;
	GuiButton* button6;

};

#endif // __SCENE_H__