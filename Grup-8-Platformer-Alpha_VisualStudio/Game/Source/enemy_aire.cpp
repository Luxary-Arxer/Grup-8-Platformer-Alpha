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

EnemyAire::EnemyAire() : Entity(EntityType::ENEMY_AIRE)
{
	name.Create("EnemyAire");
}

EnemyAire::~EnemyAire() {}

bool EnemyAire::Awake() {

	//Idle_r animation

	idle_r.PushBack({ 64*0, 0, 64, 64 });
	idle_r.PushBack({ 64 * 1, 0, 64, 64 });
	idle_r.PushBack({ 64 * 2, 0, 64, 64 });
	idle_r.PushBack({ 64 * 3, 0, 64, 64 });
	idle_r.loop = true;
	idle_r.speed = 0.1f;

	idle_l.PushBack({ 64 * 0, 0, 64, 64 });
	idle_l.PushBack({ 64 * 1, 0, 64, 64 });
	idle_l.PushBack({ 64 * 2, 0, 64, 64 });
	idle_l.PushBack({ 64 * 3, 0, 64, 64 });
	idle_l.loop = true;
	idle_l.speed = 0.1f;

	run_r.PushBack({ 64 * 0, 64 * 2, 64, 64 });
	run_r.PushBack({ 64 * 1, 64 * 2, 64, 64 });
	run_r.PushBack({ 64 * 2, 64 * 2, 64, 64 });
	run_r.PushBack({ 64 * 3, 64 * 2, 64, 64 });

	run_r.loop = true;
	run_r.speed = 0.1f;

	run_l.PushBack({ 64 * 0, 64 * 1, 64, 64 });
	run_l.PushBack({ 64 * 1, 64 * 1, 64, 64 });
	run_l.PushBack({ 64 * 2, 64 * 1, 64, 64 });
	run_l.PushBack({ 64 * 3, 64 * 1, 64, 64 });
	run_l.loop = true;
	run_l.speed = 0.1f;


	death.PushBack({ 64 * 0, 64 * 4, 64, 64 });
	death.PushBack({ 64 * 1, 64 * 4, 64, 64 });
	death.PushBack({ 64 * 2, 64 * 4, 64, 64 });
	death.PushBack({ 64 * 3, 64 * 4, 64, 64 });
	death.loop = false;
	death.speed = 0.1f;

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	origin.x = parameters.attribute("origin x").as_int();
	origin.y = parameters.attribute("origin y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool EnemyAire::Start() {

	int speed = 1;
	b2Vec2 vel = b2Vec2(0, Gravity);

	//initilize textures
	texture = app->tex->Load(texturePath);
	EnemyAnimation = &idle_l;

	mouseTileTex = app->tex->Load("Assets/Maps/path_enemigos tierra.png");

	// Texture to show path origin 
	originTex = app->tex->Load("Assets/Maps/x.png");
	
	// L07 DONE 4: Add a physics to an item - initialize the physics body
	pbody = app->physics->CreateCircle(position.x, position.y, 30, bodyType::DYNAMIC);

	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this;

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::ENEMY;

	hit = false;
	suelo = false;

	return true;
}

bool EnemyAire::Update()
{
	// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  
	b2Vec2 vel = b2Vec2(0, Gravity);

	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_F8) == KEY_REPEAT) {
		hit = true;
	}
	if (hit == true) {
		if (EnemyAnimation != &death) {
			death.Reset();
			EnemyAnimation = &death;
		}
		vel = b2Vec2(0, -GRAVITY_Y);

		if (suelo== true) {
			pbody->body->SetActive(false);
			pbody->body->SetAwake(false);
		}
	}
	if (app->scene->player->position.x-position.x > -544 && app->scene->player->position.x - position.x < 544) {
		rango_jugador = true;
	}
	else{
		rango_jugador = false;
	}

	//-------------------------------------
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	mouseX = app->scene->player->position.x;
	mouseY = (app->scene->player->position.y+32);
	iPoint mouseTile = app->map->WorldToMap(mouseX,mouseY);

	if (hit == false && rango_jugador == true) {
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
					vel = b2Vec2(-speed, Gravity);
					EnemyAnimation = &run_l;
				}
				if (path->At(0)->x < path->At(1)->x)
				{
					position.x = position.x + 1;
					vel = b2Vec2(speed, Gravity);
					EnemyAnimation = &run_r;
				}
				if (path->At(0)->y > path->At(1)->y)
				{
					position.y = position.y - 1;
					vel = b2Vec2(0, -speed);
				}
				if (path->At(0)->y < path->At(1)->y)
				{
					position.y = position.y + 1;
					vel = b2Vec2(0, speed);
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

	origin.x = (position.x)/32;
	origin.y = (position.y)/32;


	EnemyAnimation->Update();
	SDL_Rect rect = EnemyAnimation->GetCurrentFrame();

	app->render->DrawTexture(texture, position.x-15, position.y-15, & rect);

	return true;
}

bool EnemyAire::CleanUp()
{


	return true;
}



void EnemyAire::OnCollision(PhysBody* physA, PhysBody* physB) {

	// L07 DONE 7: Detect the type of collision

	switch (physB->ctype)
	{

	case ColliderType::DEATH:
		LOG("Collision DEATH");
		hit = true;
		suelo = true;
		break;
	case ColliderType::PLAYER:
		LOG("Collision PLAYER");

		break;
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		suelo = true;
		break;
	}

}


void EnemyAire::LoadPosition(int x, int y, bool death) {

	pbody->body->SetTransform({ PIXEL_TO_METERS(x),PIXEL_TO_METERS(y) }, 0);
	hit = death;
}