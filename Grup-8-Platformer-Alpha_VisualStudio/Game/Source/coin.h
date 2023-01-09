#ifndef __COIN_H__
#define __COIN_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_rect.h"
#include "Animation.h"

struct SDL_Texture;

class Coin : public Entity
{
public:

	Coin();

	virtual ~Coin();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void BotUpdate();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	void LoadPosition(int x, int y, bool death);

public:

	Animation* CoinAnimation = nullptr;

	Animation idle;

	Animation death;

	bool hit = false;

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


private:

	SDL_Texture* texture;
	const char* texturePath;

	int speed = 0;

	//DONE 4: Add a physics to an item
	PhysBody* pbody;

	bool load = false;

	bool death_colision = false;

	float Gravity = -0.2;

	SDL_Texture* mouseTileTex = nullptr;
	SDL_Texture* originTex = nullptr;

};

#endif // __ITEM_H__