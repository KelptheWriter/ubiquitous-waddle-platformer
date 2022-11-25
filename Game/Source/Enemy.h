#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class Enemy : public Entity
{
public:

	Enemy();

	virtual ~Enemy();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	bool CanJump = true;
	bool CanDoubleJump = true;

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);


private:

	//L02: DONE 1: Declare player parameters
	SDL_Texture* texture;
	const char* texturePath;

	// L07 DONE 5: Add physics to the player - declare a Physics body
	PhysBody* pbody;


};

#endif
