#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "FadeToBlack.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Animation.h"


#include <windows.h>
#include <time.h>

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
	LOG("Create Player");

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

	//kneel_l animation
	kneel_l.PushBack({ 64 * 5, 320, 64, 64 });
	kneel_l.PushBack({ 64 * 4, 320, 64, 64 });
	kneel_l.PushBack({ 64 * 3, 320, 64, 64 });
	kneel_l.PushBack({ 64 * 2, 320, 64, 64 });
	kneel_l.loop = false;
	kneel_l.speed = 0.15f;

	//     UP
	//kneelup_r animation
	kneelup_r.PushBack({ 64 * 3, 256, 64, 64 });
	kneelup_r.PushBack({ 64 * 4, 256, 64, 64 });
	kneelup_r.PushBack({ 64 * 5, 256, 64, 64 });
	kneelup_r.PushBack({ 64 * 0, 256, 64, 64 });
	kneelup_r.loop = false;
	kneelup_r.speed = 0.09f;

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


	//death animation
	atac_r.PushBack({ 64 * 0, 640, 64, 64 });
	atac_r.PushBack({ 64 * 1, 640, 64, 64 });
	atac_r.PushBack({ 64 * 2, 640, 64, 64 });
	atac_r.PushBack({ 64 * 3, 640, 64, 64 });
	atac_r.PushBack({ 64 * 4, 640, 64, 64 });
	atac_r.PushBack({ 64 * 5, 640, 64, 64 });
	atac_r.PushBack({ 64 * 6, 640, 64, 64 });
	atac_r.PushBack({ 64 * 7, 640, 64, 64 });
	atac_r.loop = false;
	atac_r.speed = 0.09f;

	atac_l.PushBack({ 64 * 7, 704, 64, 64 });
	atac_l.PushBack({ 64 * 6, 704, 64, 64 });
	atac_l.PushBack({ 64 * 5, 704, 64, 64 });
	atac_l.PushBack({ 64 * 4, 704, 64, 64 });
	atac_l.PushBack({ 64 * 3, 704, 64, 64 });
	atac_l.PushBack({ 64 * 2, 704, 64, 64 });
	atac_l.PushBack({ 64 * 1, 704, 64, 64 });
	atac_l.PushBack({ 64 * 0, 704, 64, 64 });
	atac_l.loop = false;
	atac_l.speed = 0.09f;

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

	int speed = 7;
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y + 3);

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

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();

	salto = false;
	posy = position.y;

	return true;
}

bool Player::Update()
{

	// L07 DONE 5: Add physics to the player - updated player position using physics
	
	
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y + 3);
	 

	if (hit == true) {	

		if (currentAnimation != &death)
		{
			death.Reset();
			currentAnimation = &death;
		}
	}
	if (currentAnimation == &death) {
		if (currentAnimation->HasFinished()) {
			death.Reset();
			hit = false;
			app->fade->StartFadeToBlack((Module*)app->scene, (Module*)app->sceneEnding, 10);
		}

	}


	if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {
		if (currentAnimation != &atac_r) {
			atac_r.Reset();
			currentAnimation = &atac_r;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN) {
		if (currentAnimation != &atac_l) {
			atac_l.Reset();
			currentAnimation = &atac_l;
		}
	}
	

	//L02: DONE 4: modify the position of the player using arrow keys and render the texture
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		//
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && !hit) {

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

		
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !hit) {
		position.x = position.x-7;
		vel = b2Vec2(-speed, -GRAVITY_Y);
		derecha = false;
		if (salto == false && usalto == false /*&& currentAnimation != &atac_r && currentAnimation != &atac_l*/) {
			currentAnimation = &run_l;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !hit) {
		position.x = position.x + 7;
		vel = b2Vec2(speed, -GRAVITY_Y);
		derecha = true;
		if (salto == false && usalto == false /*&& currentAnimation != &atac_r && currentAnimation != &atac_l*/) {
			currentAnimation = &run_r;
		}

	}



	cam = true;
	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		
		cam = false;
		pbody->body->SetTransform({ PIXEL_TO_METERS(150),PIXEL_TO_METERS(586) }, 0);
		app->render->camera.x = 0;
		app->render->camera.y = 0;

	}

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		godmode = !godmode;

	}
	if (godmode)
	{
		usalto2 = true;
		salto2 = 1;
		posy = position.y;
	}

	if (position.y > posy+10)
	{
		usalto2 = false;
	}

	

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && usalto == false && usalto2 == true && !hit || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && salto2 == 1 && !hit) {
		salto = true;
		i = 0;
		usalto = true;
		j = 0;
		salto2++;
		
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
	if (position.x <= 1024 / 2)
	{
		app->render->camera.x = 0;
	}

	if (position.x > 1024/2 && position.x < (2048*2)- 1024 / 2 && cam)
	{	
		app->render->camera.x = -position.x + 1024- 1024/2;
	}

	

	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;


	if (hit)
	{
		vel = b2Vec2(0, -GRAVITY_Y);
	}

	//Animacnion kneelup

	if (app->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_UP && !hit) {

		if (derecha == true) {
			printf("_Animation_");
			kneelup_r.Reset();
			currentAnimation = &kneelup_r;
		}
		if (derecha == false) {
			printf("_Animation_");
			kneelup_l.Reset();
			currentAnimation = &kneelup_l;
		}
		if (currentAnimation->HasFinished() && (currentAnimation == &kneelup_r || currentAnimation == &kneelup_l)) {
			kneelup_l.Reset();
			kneelup_r.Reset();
		}
	}
	if (currentAnimation->HasFinished() && (currentAnimation == &kneelup_r || currentAnimation == &kneelup_l)) {
		printf("_HasFinished_");
		currentAnimation = &idle_r;
	}

	//comprovar si esta en idle
	if (app->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_T) == KeyState::KEY_IDLE
		&& (currentAnimation != &kneelup_l && currentAnimation != &kneelup_r && currentAnimation != &atac_r && currentAnimation != &atac_l)
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

	LOG("Destroy Player");

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
			//usalto = false;
			posy = position.y;
			break;
		case ColliderType::DEATH:
			LOG("Collision DEATH");
			if (!godmode)
			{
				hit = true;
				app->audio->PlayFx(deathsound);
			}
			salto = false;
			usalto = false;
			usalto2 = true;
			posy = position.y;
		case ColliderType::ENEMY:
			LOG("Collision DEATH");

			break;
		case ColliderType::PLATFORM:
			LOG("Collision PLATFORM");
			salto = false;
			usalto = false;
			usalto2 = true;
			salto2 = 0;
			posy = position.y;
			break;
		case ColliderType::LIMIT:
			LOG("Collision PLATFORM");
			salto = false;
			usalto = false;
			usalto2 = true;
			salto2 = 0;
			posy = position.y;
			break;
	}
	
}

void Player::LoadPosition(int x,int y) {

	cam = false;
	pbody->body->SetTransform({ PIXEL_TO_METERS(x),PIXEL_TO_METERS(y) }, 0);
	
}


