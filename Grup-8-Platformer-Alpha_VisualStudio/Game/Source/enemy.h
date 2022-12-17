#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_rect.h"
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

	void BotUpdate();

	void OnCollision(PhysBody* physA, PhysBody* physB);

public:

	Animation* EnemyAnimation = nullptr;

	Animation idle_r;
	Animation idle_l;

	Animation run_r;
	Animation run_l;

	Animation death;



	enum BotState
	{
		None = 0,
		MoveTo,

	}currentStep = BotState::None;

	void ChangeState(BotState newState)
	{
		currentStep = newState;
	}


	bool isPicked = false;

	bool pathmade = true;

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