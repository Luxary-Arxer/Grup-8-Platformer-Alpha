#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"

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

public:

	Animation* EnemyAnimation = nullptr;

	Animation idle_r;
	Animation idle_l;

	Animation run_r;
	Animation run_l;

	Animation death;


	bool isPicked = false;

private:

	SDL_Texture* texture;
	const char* texturePath;

	int speed = 2;

	//DONE 4: Add a physics to an item
	PhysBody* pbody;

	bool derecha = true;
	bool hit = false;
	bool load = false;


	SDL_Texture* mouseTileTex = nullptr;
	SDL_Texture* originTex = nullptr;
	// L12: Debug pathfing
	iPoint origin;
	bool originSelected = false;
};

#endif // __ITEM_H__