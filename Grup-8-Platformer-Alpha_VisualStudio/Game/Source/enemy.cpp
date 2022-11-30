#include "Enemy.h"
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

Enemy::Enemy() : Entity(EntityType::ENEMY)
{
	name.Create("Enemy");
}

Enemy::~Enemy() {}

bool Enemy::Awake() {

	//Idle_r animation
	idle_r.PushBack({ 0, 0, 129, 129 });
	idle_r.PushBack({ 129*1, 0, 129, 129 });
	idle_r.PushBack({ 129 * 2, 0, 129, 129 });
	idle_r.PushBack({ 129 * 3, 0, 129, 129 });
	idle_r.PushBack({ 129 * 4, 0, 129, 129 });
	idle_r.PushBack({ 129 * 5, 0, 129, 129 });
	idle_r.PushBack({ 129 * 6, 0, 129, 129 });
	idle_r.PushBack({ 129 * 7, 0, 129, 129 });
	idle_r.loop = true;
	idle_r.speed = 0.1f;

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Enemy::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);
	EnemyAnimation = &idle_r;
	
	// L07 DONE 4: Add a physics to an item - initialize the physics body
	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 32, bodyType::DYNAMIC);

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::ENEMY;
	
	return true;
}

bool Enemy::Update()
{
	// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	EnemyAnimation = &idle_r;

	EnemyAnimation->Update();
	SDL_Rect rect = EnemyAnimation->GetCurrentFrame();

	app->render->DrawTexture(texture, position.x-60, position.y-50, & rect);

	return true;
}

bool Enemy::CleanUp()
{
	return true;
}

void Enemy::OnCollision(PhysBody* physA, PhysBody* physB) {

	// L07 DONE 7: Detect the type of collision

	switch (physB->ctype)
	{

	case ColliderType::DEATH:
		LOG("Collision DEATH");
		//DestroyBody(pbody);
		// = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
		break;
	case ColliderType::PLAYER:
		LOG("Collision PLAYER");

		break;
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");

		break;

	case ColliderType::TERRAIN:
		LOG("Collision TERRAIN");
		break;
	}

}