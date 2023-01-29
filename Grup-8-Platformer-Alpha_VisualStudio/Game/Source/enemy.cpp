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

#include "Pathfinding.h"
#include "Map.h"

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

	idle_l.PushBack({ 129 * 7, 129, 129, 129 });
	idle_l.PushBack({ 129 * 6, 129, 129, 129 });
	idle_l.PushBack({ 129 * 5, 129, 129, 129 });
	idle_l.PushBack({ 129 * 4, 129, 129, 129 });
	idle_l.PushBack({ 129 * 3, 129, 129, 129 });
	idle_l.PushBack({ 129 * 2, 129, 129, 129 });
	idle_l.PushBack({ 129 * 1, 129, 129, 129 });
	idle_l.PushBack({ 129 * 0, 129, 129, 129 });
	idle_l.loop = true;
	idle_l.speed = 0.1f;

	run_r.PushBack({ 129 * 0, 129 * 2, 129, 129 });
	run_r.PushBack({ 129 * 1, 129 * 2, 129, 129 });
	run_r.PushBack({ 129 * 2, 129 * 2, 129, 129 });
	run_r.PushBack({ 129 * 3, 129 * 2, 129, 129 });
	run_r.PushBack({ 129 * 4, 129 * 2, 129, 129 });
	run_r.PushBack({ 129 * 5, 129 * 2, 129, 129 });
	run_r.PushBack({ 129 * 6, 129 * 2, 129, 129 });
	run_r.PushBack({ 129 * 7, 129 * 2, 129, 129 });
	run_r.loop = true;
	run_r.speed = 0.1f;

	run_l.PushBack({ 129 * 7, 129 * 3, 129, 129 });
	run_l.PushBack({ 129 * 6, 129 * 3, 129, 129 });
	run_l.PushBack({ 129 * 5, 129 * 3, 129, 129 });
	run_l.PushBack({ 129 * 4, 129 * 3, 129, 129 });
	run_l.PushBack({ 129 * 3, 129 * 3, 129, 129 });
	run_l.PushBack({ 129 * 2, 129 * 3, 129, 129 });
	run_l.PushBack({ 129 * 1, 129 * 3, 129, 129 });
	run_l.PushBack({ 129 * 0, 129 * 3, 129, 129 });
	run_l.loop = true;
	run_l.speed = 0.1f;


	death.PushBack({ 0, 129 * 7, 129, 129 });
	death.PushBack({ 129 * 1, 129 * 7, 129, 129 });
	death.PushBack({ 129 * 2, 129 * 7, 129, 129 });
	death.PushBack({ 129 * 3, 129 * 7, 129, 129 });
	death.PushBack({ 129 * 4, 129 * 7, 129, 129 });
	death.PushBack({ 129 * 5, 129 * 7, 129, 129 });
	death.PushBack({ 129 * 6, 129 * 7, 129, 129 });
	death.PushBack({ 129 * 7, 129 * 7, 129, 129 });
	death.loop = false;
	death.speed = 0.15f;

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	origin.x = parameters.attribute("origin x").as_int();
	origin.y = parameters.attribute("origin y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Enemy::Start() {

	int speed = 1;
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y + 3);

	//initilize textures
	texture = app->tex->Load(texturePath);
	EnemyAnimation = &idle_l;

	mouseTileTex = app->tex->Load("Assets/Maps/path_enemigos tierra.png");

	// Texture to show path origin 
	originTex = app->tex->Load("Assets/Maps/x.png");
	
	// L07 DONE 4: Add a physics to an item - initialize the physics body
	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 30, bodyType::DYNAMIC);

	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this;

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::ENEMY;



	hit = false;
	death_colision = false;
	

	return true;
}

bool Enemy::Update()
{
	// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y + 3);

	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_F8) == KEY_REPEAT) {
		hit = true;
	}

	if (app->scene->player->position.x-position.x > -544 && app->scene->player->position.x - position.x < 544) {
		rango_jugador = true;
	}
	else{
		rango_jugador = false;
	}

	//-------------------------------------


	if (hit == false && rango_jugador == true) {
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);
		mouseX = app->scene->player->position.x;
		mouseY = (app->scene->player->position.y + 32);
		iPoint mouseTile = app->map->WorldToMap(mouseX, mouseY);
		//Convert again the tile coordinates to world coordinates to render the texture of the tile
		iPoint highlightedTileWorld = app->map->MapToWorld(mouseTile.x, mouseTile.y);
		if (showpath == true) {
			app->render->DrawTexture(mouseTileTex, highlightedTileWorld.x, highlightedTileWorld.y);
		}

		//Test compute path function
		if (true)
		{
			if (originSelected == true)
			{
				EnemyAnimation = &idle_l;
				LOG("posenemy: %f", PIXEL_TO_METERS(origin.x));
				app->pathfinding->CreatePath(origin, mouseTile);
				originSelected = false;
			}
			else
			{
				origin = mouseTile;
				originSelected = true;

				app->pathfinding->ClearLastPath();
			}
		}

		const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

		for (uint i = 0; i < path->Count(); ++i)
		{

			if (showpath == true) {
				iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				app->render->DrawTexture(mouseTileTex, pos.x, pos.y);
			}

			if (i+1 < path->Count())
			{
				if (path->At(0)->x > path->At(1)->x)
				{
					position.x = position.x - 1;
					vel = b2Vec2(-speed, -GRAVITY_Y);
					EnemyAnimation = &run_l;
				}
				if (path->At(0)->x < path->At(1)->x)
				{
					position.x = position.x + 1;
					vel = b2Vec2(speed, -GRAVITY_Y);
					EnemyAnimation = &run_r;
				}
			}
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		showpath = !showpath;

	//Set the velocity of the pbody of the enemy
	pbody->body->SetLinearVelocity(vel);

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	origin.x = (position.x + 4)/32;
	origin.y = (position.y + 6)/32;


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
		hit = true;
		break;
	case ColliderType::PLAYER:
		LOG("Collision PLAYER");

		break;

	case ColliderType::TERRAIN:
		LOG("Collision TERRAIN");
		break;

	case ColliderType::BALA:
		LOG("Collision BALA");
		hit = true;
		break;
	}

}

void Enemy::LoadPosition(int x, int y, bool death) {

	pbody->body->SetTransform({ PIXEL_TO_METERS(x),PIXEL_TO_METERS(y) }, 0);
	hit = death;
}