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

	return true;
}

bool Player::Update()
{

	// L07 DONE 5: Add physics to the player - updated player position using physics

	int speed = 7; 
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y); 

	//L02: DONE 4: modify the position of the player using arrow keys and render the texture
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		//
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		//
		if (derecha == true) {
			currentAnimation = &kneel_r;
		}
		if (derecha == false) {
			currentAnimation = &kneel_l;
		}
	}
		
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		position.x = position.x-7;
		vel = b2Vec2(-speed, -GRAVITY_Y);
		derecha = false;
		currentAnimation = &run_l;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		position.x = position.x + 7;
		vel = b2Vec2(speed, -GRAVITY_Y);
		derecha = true;
		currentAnimation = &run_r;
	}

	
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		salto = true;
		i = 0;





	}

	if (salto == true)
	{
		if (i > 20)
		{
			salto = false;
		}
		vel = b2Vec2(vel.x, GRAVITY_Y);

		i++;
	}

	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;


	//comprovar si esta en idle
	if (app->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_IDLE) {
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
		case ColliderType::PLATFORM:
			LOG("Collision PLATFORM");

			break;
		case ColliderType::WATER:
			LOG("Collision WATER");
			app->audio->PlayFx(deathsound);
			break;
		case ColliderType::UNKNOWN:
			LOG("Collision UNKNOWN");
			break;
	}
	


}
