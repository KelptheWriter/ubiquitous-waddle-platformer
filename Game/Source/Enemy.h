#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"

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

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);


private:

	SDL_Texture* texture;
	const char* texturePath;
	EnemyType* type;

	PhysBody* pbody;


};

#endif
