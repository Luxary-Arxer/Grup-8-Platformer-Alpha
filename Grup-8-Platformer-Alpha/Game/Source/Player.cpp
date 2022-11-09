#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Animation.h"


#include <windows.h>
#include <time.h>

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");

}

Player::~Player() {

}

bool Player::Awake() {

	//Idle_r animation
	idle_r.PushBack({ 0, 0, 64, 64 });
	idle_r.PushBack({ 64, 0, 64, 64 });
	idle_r.PushBack({ 0, 0, 64, 64 });
	idle_r.PushBack({ 64, 0, 64, 64 });
	idle_r.PushBack({ 0, 0, 64, 64 });
	idle_r.PushBack({ 64, 0, 64, 64 });
	idle_r.PushBack({ 64*2, 0, 64, 64 });
	idle_r.PushBack({ 64*3, 0, 64, 64 });
	idle_r.loop = true;
	idle_r.speed = 0.04f;

	//Idle_l animation
	idle_l.PushBack({ 64*7, 0, 64, 64 });
	idle_l.PushBack({ 64 * 6, 0, 64, 64 });
	idle_l.PushBack({ 64 * 7, 0, 64, 64 });
	idle_l.PushBack({ 64 * 6, 0, 64, 64 });
	idle_l.PushBack({ 64 * 7, 0, 64, 64 });
	idle_l.PushBack({ 64 * 6, 0, 64, 64 });
	idle_l.PushBack({ 64 * 5, 0, 64, 64 });
	idle_l.PushBack({ 64 * 4, 0, 64, 64 });
	idle_l.loop = true;
	idle_l.speed = 0.04f;

	//Run_r animation
	run_r.PushBack({ 64 * 0, 192, 64, 64 });
	run_r.PushBack({ 64 * 1, 192, 64, 64 });
	run_r.PushBack({ 64 * 2, 192, 64, 64 });
	run_r.PushBack({ 64 * 3, 192, 64, 64 });
	run_r.PushBack({ 64 * 4, 192, 64, 64 });
	run_r.PushBack({ 64 * 5, 192, 64, 64 });
	run_r.PushBack({ 64 * 6, 192, 64, 64 });
	run_r.PushBack({ 64 * 7, 192, 64, 64 });
	run_r.loop = true;
	run_r.speed = 0.09f;

	//Run_l animation
	run_l.PushBack({ 64 * 7, 128, 64, 64 });
	run_l.PushBack({ 64 * 6, 128, 64, 64 });
	run_l.PushBack({ 64 * 5, 128, 64, 64 });
	run_l.PushBack({ 64 * 4, 128, 64, 64 });
	run_l.PushBack({ 64 * 3, 128, 64, 64 });
	run_l.PushBack({ 64 * 2, 128, 64, 64 });
	run_l.PushBack({ 64 * 1, 128, 64, 64 });
	run_l.PushBack({ 64 * 0, 128, 64, 64 });
	run_l.loop = true;
	run_l.speed = 0.09f;

	//kneel_r animation
	kneel_r.PushBack({ 64 * 0, 256, 64, 64 });
	kneel_r.PushBack({ 64 * 1, 256, 64, 64 });
	kneel_r.PushBack({ 64 * 2, 256, 64, 64 });
	kneel_r.PushBack({ 64 * 3, 256, 64, 64 });
	kneel_r.loop = false;
	kneel_r.speed = 0.15f;

	//kneelup_r animation
	kneelup_r.PushBack({ 64 * 3, 256, 64, 64 });
	kneelup_r.PushBack({ 64 * 4, 256, 64, 64 });
	kneelup_r.PushBack({ 64 * 5, 256, 64, 64 });
	kneelup_r.PushBack({ 64 * 0, 256, 64, 64 });
	kneelup_r.loop = false;
	kneelup_r.speed = 0.09f;



	//kneel_l animation
	kneel_l.PushBack({ 64 * 5, 320, 64, 64 });
	kneel_l.PushBack({ 64 * 4, 320, 64, 64 });
	kneel_l.PushBack({ 64 * 3, 320, 64, 64 });
	kneel_l.PushBack({ 64 * 2, 320, 64, 64 });
	kneel_l.loop = false;
	kneel_l.speed = 0.15f;

	//kneelup_l animation
	kneelup_l.PushBack({ 64 * 2, 320, 64, 64 });
	kneelup_l.PushBack({ 64 * 1, 320, 64, 64 });
	kneelup_l.PushBack({ 64 * 0, 320, 64, 64 });
	kneelup_l.PushBack({ 64 * 5, 320, 64, 64 });
	kneelup_l.loop = false;
	kneelup_l.speed = 0.09f;


	//death animation
	death.PushBack({ 64 * 0, 576, 64, 64 });
	death.PushBack({ 64 * 1, 576, 64, 64 });
	death.PushBack({ 64 * 2, 576, 64, 64 });
	death.PushBack({ 64 * 3, 576, 64, 64 });
	death.PushBack({ 64 * 4, 576, 64, 64 });
	death.PushBack({ 64 * 5, 576, 64, 64 });
	death.PushBack({ 64 * 6, 576, 64, 64 });
	death.PushBack({ 64 * 7, 576, 64, 64 });
	death.loop = false;
	death.speed = 0.09f;

	//jump animation
	jump_up_r.PushBack({ 64 * 0, 384, 64, 64 });
	jump_up_r.PushBack({ 64 * 1, 384, 64, 64 });
	jump_up_r.PushBack({ 64 * 2, 384, 64, 64 });
	jump_up_r.PushBack({ 64 * 3, 384, 64, 64 });
	jump_up_r.loop = false;
	jump_up_r.speed = 0.15f;

	jump_down_r.PushBack({ 64 * 4, 384, 64, 64 });
	jump_down_r.PushBack({ 64 * 5, 384, 64, 64 });
	jump_down_r.PushBack({ 64 * 6, 384, 64, 64 });
	jump_down_r.PushBack({ 64 * 7, 384, 64, 64 });
	jump_down_r.loop = true;
	jump_down_r.speed = 0.09f;


	jump_up_l.PushBack({ 64 * 7, 448, 64, 64 });
	jump_up_l.PushBack({ 64 * 6, 448, 64, 64 });
	jump_up_l.PushBack({ 64 * 5, 448, 64, 64 });
	jump_up_l.PushBack({ 64 * 4, 448, 64, 64 });
	jump_up_l.loop = false;
	jump_up_l.speed = 0.15;

	jump_down_l.PushBack({ 64 * 3, 448, 64, 64 });
	jump_down_l.PushBack({ 64 * 2, 448, 64, 64 });
	jump_down_l.PushBack({ 64 * 1, 448, 64, 64 });
	jump_down_l.PushBack({ 64 * 0, 448, 64, 64 });
	jump_down_l.loop = true;
	jump_down_l.speed = 0.09f;

	test.PushBack({ 64 * 6, 256, 64, 64 });
	test.loop = true;
	test.speed = 0.09f;

	//L02: DONE 1: Initialize Player parameters
	//pos = position;
	//texturePath = "Assets/Textures/player/idle1.png";

	//L02: DONE 5: Get Player parameters from XML
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Player::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);
	currentAnimation = &idle_r;



	// L07 DONE 5: Add physics to the player - initialize physics body
	pbody = app->physics->CreateCircle(position.x+16, position.y+16, 30, bodyType::DYNAMIC);

	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this; 

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::PLAYER;

	//initialize audio effect - !! Path is hardcoded, should be loaded from config.xml
	pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");
	deathsound = app->audio->LoadFx("Assets/Audio/Fx/Death-sound-in-Minecraft.ogg");

	salto = false;
	posy = position.y;

	return true;
}

bool Player::Update()
{
	// contador 



	// L07 DONE 5: Add physics to the player - updated player position using physics
	

	int speed = 7; 
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y + 3); 

	if (hit == true) {
		printf("_Death_");
		if (currentAnimation != &death)
		{
			death.Reset();
			currentAnimation = &death;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {
		if (currentAnimation != &jump_down_r)
		{
			jump_down_r.Reset();
			currentAnimation = &jump_down_r;
		}
	}


	//L02: DONE 4: modify the position of the player using arrow keys and render the texture
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		//
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {

		if (derecha == true) {
			if (currentAnimation != &kneel_r)
			{
				kneel_r.Reset();
				currentAnimation = &kneel_r;
			}
		}
		if (derecha == false) {
			if (currentAnimation != &kneel_l)
			{
				kneel_l.Reset();
				currentAnimation = &kneel_l;
			}
		}
	}

		
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		position.x = position.x-7;
		vel = b2Vec2(-speed, -GRAVITY_Y);
		derecha = false;
		if (salto == false && usalto == false) {
			currentAnimation = &run_l;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		position.x = position.x + 7;
		vel = b2Vec2(speed, -GRAVITY_Y);
		derecha = true;
		if (salto == false && usalto == false) {
			currentAnimation = &run_r;
		}

	}

	if (position.y > posy+10)
	{
		usalto2 = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && usalto == false && usalto2 == true) {
		salto = true;
		i = 0;
		usalto = true;
		j = 0;


		// Animacniones Salto Arriba
		if (derecha == true) {
			if (currentAnimation != &jump_up_r)
			{
				jump_up_r.Reset();
				currentAnimation = &jump_up_r;

			}
		}
		if (derecha == false) {
			if (currentAnimation != &jump_up_l)
			{
				jump_up_l.Reset();
				currentAnimation = &jump_up_l;

			}
		}
	}

	if (salto == true && usalto == true)
	{

		if (i > 30)
		{
			salto = false;


		}
		if (i == 25)
		{
			if (derecha == true) {
				if (currentAnimation != &jump_down_r)
				{
					jump_down_r.Reset();
					currentAnimation = &jump_down_r;

				}
			}
			if (derecha == false) {
				if (currentAnimation != &jump_down_l)
				{
					jump_down_l.Reset();
					currentAnimation = &jump_down_l;

				}
			}
		}
		// Animacniones Salto Abajo
		/*
		if (vel.x > 0)
		{
			vel = b2Vec2(vel.x - 2, -10.0f + j);
		}

		if (vel.x < 0)
		{
			vel = b2Vec2(vel.x + 2, -20.0f + j);
		}*/

		vel = b2Vec2(vel.x, -20.0f + j);

		i++;
		j += 0.8f;
	}

	// La camara sigue al jugador
	if (position.x > 1024/2 && position.x < 2048- 1024 / 2)
	{
		app->render->camera.x = -position.x + 1024- 1024/2;
	}


	

	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	//comprovar si esta en idle
	if (app->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_UP ) {

		if (currentAnimation != &kneelup_r) {
			if (derecha == true) {
				if (currentAnimation != &kneelup_r)
				{
					kneelup_r.Reset();
					currentAnimation = &kneelup_r;

				}
			}
			if (derecha == false) {
				if (currentAnimation != &kneelup_l)
				{
					kneelup_l.Reset();
					currentAnimation = &kneelup_l;
				}
			}
		}
		//if (derecha == true) {

		//	currentAnimation = &idle_r;
		//}
		//if (derecha == false) {
		//	currentAnimation = &idle_l;
		//}
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_T) == KeyState::KEY_IDLE
		&& currentAnimation != &kneelup_l
		&& currentAnimation != &kneelup_r
		&& salto == false
		&& usalto == false
		&& hit == false) {

		if (derecha == true) {
			currentAnimation = &idle_r;
		}
		if (derecha == false) {
			currentAnimation = &idle_l;
		}

	}



	currentAnimation->Update();
	SDL_Rect rect = currentAnimation->GetCurrentFrame();



	app->render->DrawTexture(texture, position.x-16, position.y-16, &rect);


	return true;
}

bool Player::CleanUp()
{
	return true;
}

// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	// L07 DONE 7: Detect the type of collision

	switch (physB->ctype)
	{
		case ColliderType::ITEM:
			LOG("Collision ITEM");
			//app->audio->PlayFx(pickCoinFxId);
			break;
		case ColliderType::TERRAIN:
			LOG("Collision TERRAIN");
			hit = false;
			//usalto = false;
			posy = position.y;
			break;
		case ColliderType::WATER:
			LOG("Collision WATER");
			hit = true;
			app->audio->PlayFx(deathsound);
			usalto = false;
			usalto2 = true;
			posy = position.y;
			break;
		case ColliderType::PLATFORM:
			LOG("Collision PLATFORM");
			hit = false;
			salto = false;
			usalto = false;
			usalto2 = true;
			posy = position.y;
			break;
	}
	


}


