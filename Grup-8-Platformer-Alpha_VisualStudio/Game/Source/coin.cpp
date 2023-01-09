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
	idle_r.PushBack({ 0, 0, 129, 129 });
	idle_r.PushBack({ 129*1, 0, 129, 129 });
	idle_r.loop = true;
	idle_r.speed = 0.1f;


	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Coin::Start() {

	int speed = 1;
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y + 3);

	//initilize textures
	texture = app->tex->Load(texturePath);
	EnemyAnimation = &idle_l;


	// Texture to show path origin 
	originTex = app->tex->Load("Assets/Textures/Coins.png");
	
	// L07 DONE 4: Add a physics to an item - initialize the physics body
	pbody = app->physics->CreateCircle(position.x, position.y, 16, bodyType::DYNAMIC);

	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this;

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::ENEMY;



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



	EnemyAnimation->Update();
	SDL_Rect rect = EnemyAnimation->GetCurrentFrame();


	if (hit == true) {
		//app->render->DrawTexture(texture, position.x - 60, position.y - 80, &rect);
		//if (death_colision = false) {
		//	pbody = app->physics->CreateRectangle(position.x + 16, position.y + 16, 30, 2, bodyType::DYNAMIC);
		//	death_colision = true;
		//}
		if (EnemyAnimation != &death) {
			death.Reset();
			EnemyAnimation = &death;
		}
		pbody->body->SetActive(false);
		pbody->body->SetAwake(false);
		pbody->ctype = ColliderType::PLATFORM;
	}

	app->render->DrawTexture(texture, position.x - 60, position.y - 54, &rect);

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

	case ColliderType::DEATH:
		LOG("Collision DEATH");
		hit = true;
		break;
	case ColliderType::PLAYER:
		LOG("Collision PLAYER");

		break;

	case ColliderType::TERRAIN:
		LOG("Collision TERRAIN");
		break;

	case ColliderType::UNKNOWN:
		LOG("Collision BALA");
		hit = true;
		break;
	}

}

void Coin::LoadPosition(int x, int y, bool death) {

	pbody->body->SetTransform({ PIXEL_TO_METERS(x),PIXEL_TO_METERS(y) }, 0);
	hit = death;
}