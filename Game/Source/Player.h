#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "Timer.h"
#include "PerfTimer.h"

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();

	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	bool CanJump = true;
	bool CanDoubleJump = true;
	bool isWalking = false;

	bool is_alive = true;

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	iPoint GetPPos();
	
	int coins = 0;


	Animation* currentAnimation = nullptr;
	Animation idleAnim;
	Animation walkRightAnim;
	Animation jumpAnim;
	Animation dieAnim;


private:

	//L02: DONE 1: Declare player parameters
	SDL_Texture* texture;
	const char* texturePath;

	Timer stime;

	// L07 DONE 5: Add physics to the player - declare a Physics body
	PhysBody* pbody;


};

#endif // __PLAYER_H__