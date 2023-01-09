#include "Coin.h"
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

#include "Pathfinding.h"
#include "Map.h"

Coin::Coin() : Entity(EntityType::COIN)
{
	name.Create("Coin");
}

Coin::~Coin() {}

bool Coin::Awake() {

	//Idle_r animation
	idle.PushBack({ 0 * 16, 0, 16, 16 });
	idle.PushBack({ 1 * 16, 0, 16, 16 });
	idle.PushBack({ 2 * 16, 0, 16, 16 });
	idle.PushBack({ 3 * 16, 0, 16, 16 });
	idle.PushBack({ 4 * 16, 0, 16, 16 });
	idle.PushBack({ 5 * 16, 0, 16, 16 });
	idle.loop = true;
	idle.speed = 0.1f;

	death.PushBack({ 0 * 16, 3 * 16, 16, 16 });
	death.PushBack({ 1 * 16, 3 * 16, 16, 16 });
	death.PushBack({ 2 * 16, 3 * 16, 16, 16 });
	death.PushBack({ 3 * 16, 3 * 16, 16, 16 });
	death.PushBack({ 4 * 16, 3 * 16, 16, 16 });
	death.PushBack({ 5 * 16, 3 * 16, 16, 16 });
	death.loop = false;
	death.speed = 0.1f;

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Coin::Start() {

	int speed = 7;
	b2Vec2 vel = b2Vec2(0, 0);

	//initilize textures
	texture = app->tex->Load(texturePath);
	CoinAnimation = &idle;


	// Texture to show path origin 
	originTex = app->tex->Load("Assets/Textures/Coins.png");
	
	// L07 DONE 4: Add a physics to an item - initialize the physics body
	pbody = app->physics->CreateRectangleSensor(position.x, position.y,16,16, bodyType::STATIC);

	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this;

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::COIN;

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();

	hit = false;
	death_colision = false;
	

	return true;
}

bool Coin::Update()
{
	// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  
	b2Vec2 vel = b2Vec2(0, Gravity);

	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_F8) == KEY_REPEAT) {
		hit = true; 
	}

	CoinAnimation->Update();
	SDL_Rect rect = CoinAnimation->GetCurrentFrame();

	if (hit == true) {

		if (CoinAnimation != &death) {
			death.Reset();
			CoinAnimation = &death;
		}
		pbody->body->SetActive(false);
		pbody->body->SetAwake(false);
		pbody->ctype = ColliderType::PLATFORM;
	}

	app->render->DrawTexture(texture, position.x - 16/2, position.y - 16 / 2, &rect);

	return true;
}

bool Coin::CleanUp()
{


	return true;
}



void Coin::OnCollision(PhysBody* physA, PhysBody* physB) {

	// L07 DONE 7: Detect the type of collision

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		LOG("Collision PLAYER");
		hit = true;
		break;
	}

}

void Coin::LoadPosition(int x, int y, bool death) {

	pbody->body->SetTransform({ PIXEL_TO_METERS(x),PIXEL_TO_METERS(y) }, 0);
	hit = death;
}