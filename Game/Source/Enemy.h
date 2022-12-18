#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"

enum class EnemyType {

	TERRESTRIAL,
	AERIAL

};

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
	bool is_alive;

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	Animation* currentAnimation = nullptr;
	Animation idleAnim;
	Animation dieAnim;


private:

	SDL_Texture* texture;
	const char* texturePath;
	EnemyType* type;
	bool isDead;
	bool flying;

	SDL_Texture* mouseTileTex = nullptr;
	SDL_Texture* originTex = nullptr;

	PhysBody* pbody;


};

#endif
