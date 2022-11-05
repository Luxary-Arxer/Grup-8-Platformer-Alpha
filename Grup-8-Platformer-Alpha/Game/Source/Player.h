#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"

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

	// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
	void OnCollision(PhysBody* physA, PhysBody* physB);


public:

	Animation* currentAnimation = nullptr;


	Animation idle_r;
	Animation idle_l;

	Animation walk_r;
	Animation walk_l;

	Animation run_r;
	Animation run_l;

	Animation kneel_r;
	Animation kneelup_r;
	Animation kneel_l;
	Animation kneelup_l;

	Animation jump_up;
	Animation jump_down;
	Animation death;

	Animation test;


private:

	//L02: DONE 1: Declare player parameters
	SDL_Texture* texture;
	const char* texturePath;

	// L07 DONE 5: Add physics to the player - declare a Physics body
	PhysBody* pbody;

	int pickCoinFxId;
	int deathsound;

	bool salto = false;
	bool usalto = false;
	bool hit = false;
	int i;

	bool derecha = true;



};

#endif // __PLAYER_H__