#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "FadeToBlack.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"
#include "Player.h"
#include "Animation.h"
#include "PathFinding.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	checkpoint1 = (Checkpoint*)app->entityManager->CreateEntity(EntityType::CHECK_POINT);
	checkpoint1->parameters = config.child("checkpoint1");
	checkpoint2 = (Checkpoint*)app->entityManager->CreateEntity(EntityType::CHECK_POINT);
	checkpoint2->parameters = config.child("checkpoint2");
	checkpoint3 = (Checkpoint*)app->entityManager->CreateEntity(EntityType::CHECK_POINT);
	checkpoint3->parameters = config.child("checkpoint3");

	// iterate all objects in the scene
	// Check https://pugixml.org/docs/quickstart.html#access
	//for (pugi::xml_node itemNode = config.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	//{
	//	Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
	//	item->parameters = itemNode;

	//}

	enemy1 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	enemy1->parameters = config.child("enemy1");

	enemy2 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	enemy2->parameters = config.child("enemy2");

	enemy3 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	enemy3->parameters = config.child("enemy3");

	enemy4 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	enemy4->parameters = config.child("enemy4");

	enemy5 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	enemy5->parameters = config.child("enemy5");

	enemy6 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	enemy6->parameters = config.child("enemy6");

	enemy7 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	enemy7->parameters = config.child("enemy7");

	enemyaire1 = (EnemyAire*)app->entityManager->CreateEntity(EntityType::ENEMY_AIRE);
	enemyaire1->parameters = config.child("enemyaire1");

	enemyaire2 = (EnemyAire*)app->entityManager->CreateEntity(EntityType::ENEMY_AIRE);
	enemyaire2->parameters = config.child("enemyaire2");

	coin1 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin1->parameters = config.child("coin1");
	coin2 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin2->parameters = config.child("coin2");
	coin3 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin3->parameters = config.child("coin3");
	coin4 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin4->parameters = config.child("coin4");
	coin5 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin5->parameters = config.child("coin5");
	coin6 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin6->parameters = config.child("coin6");
	coin7 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin7->parameters = config.child("coin7");
	coin8 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin8->parameters = config.child("coin8");
	coin9 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin9->parameters = config.child("coin9");
	coin10 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin10->parameters = config.child("coin10");
	coin11 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin11->parameters = config.child("coin11");
	coin12 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin12->parameters = config.child("coin12");
	coin13 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin13->parameters = config.child("coin13");
	coin14 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin14->parameters = config.child("coin14");
	coin15 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin15->parameters = config.child("coin15");
	coin16 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin16->parameters = config.child("coin16");
	coin17 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin17->parameters = config.child("coin17");
	coin18 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin18->parameters = config.child("coin18");
	coin19 = (Coin*)app->entityManager->CreateEntity(EntityType::COIN);
	coin19->parameters = config.child("coin19");



	//L02: DONE 3: Instantiate the player using the entity manager
	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	player->parameters = config.child("player");

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	//img = app->tex->Load("Assets/Textures/test.png");
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");
	LOG("Start Scene");

	ShowPathfinding = true;

	app->map->Enable();

	if (FirstScene != true) {
		//Checkpoints 
		app->entityManager->AddEntity(checkpoint1);
		checkpoint1->position.x = 2592;
		checkpoint1->position.y = 576;
		app->entityManager->AddEntity(checkpoint2);
		checkpoint2->position.x = 5440;
		checkpoint2->position.y = 480;
		app->entityManager->AddEntity(checkpoint3);
		checkpoint3->position.x = 7872;
		checkpoint3->position.y = 480;
		//Player
		app->entityManager->AddEntity(player);
		player->position.x = 118;
		player->position.y = 586;

		//Enemies
		app->entityManager->AddEntity(enemy1);
		enemy1->position.x = 416;
		enemy1->position.y = 547; 
		app->entityManager->AddEntity(enemy2);
		enemy2->position.x = 928;
		enemy2->position.y = 512;
		app->entityManager->AddEntity(enemy3);
		enemy3->position.x = 1728;
		enemy3->position.y = 256;
		app->entityManager->AddEntity(enemy4);
		enemy4->position.x = 2496;
		enemy4->position.y = 544;
		app->entityManager->AddEntity(enemy5);
		enemy5->position.x = 4000;
		enemy5->position.y = 512;
		app->entityManager->AddEntity(enemy6);
		enemy6->position.x = 5536;
		enemy6->position.y = 384;
		app->entityManager->AddEntity(enemy7);
		enemy7->position.x = 6304;
		enemy7->position.y = 288;

		//enemies aire
		app->entityManager->AddEntity(enemyaire1);
		enemyaire1->position.x = 1472;
		enemyaire1->position.y = 544;
		app->entityManager->AddEntity(enemyaire2);
		enemyaire2->position.x = 3264;
		enemyaire2->position.y = 256;
		// coins 
		app->entityManager->AddEntity(coin1);
		coin1->position.x = 1248;
		coin1->position.y = 448;
		app->entityManager->AddEntity(coin2);
		coin2->position.x = 1280;
		coin2->position.y = 448;
		app->entityManager->AddEntity(coin3);
		coin3->position.x = 1312;
		coin3->position.y = 448;

		app->entityManager->AddEntity(coin4);
		coin4->position.x = 3328;
		coin4->position.y = 512;
		app->entityManager->AddEntity(coin5);
		coin5->position.x = 3360;
		coin5->position.y = 512;
		app->entityManager->AddEntity(coin6);
		coin6->position.x = 3392;
		coin6->position.y = 512;

		app->entityManager->AddEntity(coin7);
		coin7->position.x = 4208;
		coin7->position.y = 240;
		app->entityManager->AddEntity(coin8);
		coin8->position.x = 4240;
		coin8->position.y = 240;
		app->entityManager->AddEntity(coin9);
		coin9->position.x = 4272;
		coin9->position.y = 240;
		app->entityManager->AddEntity(coin10);
		coin10->position.x = 4304;
		coin10->position.y = 208;
		app->entityManager->AddEntity(coin11);
		coin11->position.x = 4336;
		coin11->position.y = 208;

		app->entityManager->AddEntity(coin12);
		coin12->position.x = 4624;
		coin12->position.y = 416;
		app->entityManager->AddEntity(coin13);
		coin13->position.x = 4688;
		coin13->position.y = 416;
		app->entityManager->AddEntity(coin14);
		coin14->position.x = 4880;
		coin14->position.y = 224;
		app->entityManager->AddEntity(coin15);
		coin15->position.x = 4944;
		coin15->position.y = 224;
		app->entityManager->AddEntity(coin16);
		coin16->position.x = 7024;
		coin16->position.y = 256;
		app->entityManager->AddEntity(coin17);
		coin17->position.x = 7088;
		coin17->position.y = 256;
		app->entityManager->AddEntity(coin18);
		coin18->position.x = 7344;
		coin18->position.y = 384;
		app->entityManager->AddEntity(coin19);
		coin19->position.x = 7408;
		coin19->position.y = 384;


	}
	
	app->pathfinding->Enable();

	app->physics->Enable();

	app->entityManager->Enable();

	// L03: DONE: Load map
	bool retLoad = app->map->Load();

	// L12 Create walkability map
	if (retLoad) {
		int w, h;
		uchar* data = NULL;

		bool retWalkMap = app->map->CreateWalkabilityMap(w, h, &data);
		if (retWalkMap) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

	}

	//L04: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width,
		app->map->mapData.height,
		app->map->mapData.tileWidth,
		app->map->mapData.tileHeight,
		app->map->mapData.tilesets.Count());

	app->win->SetTitle(title.GetString());

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	// Texture to show path origin 
	originTex = app->tex->Load("Assets/Maps/x.png");

	// Texture to highligh mouse position 
	mouseTileTex = app->tex->Load("Assets/Maps/path.png");


	app->map->colisiones = false;



	bool ret = true;

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		app->fade->StartFadeToBlack(this, (Module*)app->scene, 40);
	}

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		ShowPathfinding = !ShowPathfinding;

		
	
	// L03: DONE 3: Request App to Load / Save when pressing the keys F5 (save) / F6 (load)
	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	//if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	//	app->render->camera.y += 7;

	//if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	//	app->render->camera.y -= 7;

	//if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	//	app->render->camera.x += 7;

	//if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	//	app->render->camera.x -= 7;



	// L08: DONE 3: Test World to map method
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint mouseTile = app->map->WorldToMap(mouseX - app->render->camera.x - app->map->mapData.tileWidth/ 2 + 14,
											mouseY - app->render->camera.y - app->map->mapData.tileHeight/2 + 14);
	// Draw map
	app->map->Draw();

	// L12: Get the latest calculated path and draw

	//if (ShowPathfinding) {
	//	//Convert again the tile coordinates to world coordinates to render the texture of the tile
	//	iPoint highlightedTileWorld = app->map->MapToWorld(mouseTile.x, mouseTile.y);
	//	app->render->DrawTexture(mouseTileTex, highlightedTileWorld.x, highlightedTileWorld.y);

	//	//Test compute path function
	//	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	//	{
	//		if (originSelected == true)
	//		{
	//			app->pathfinding->CreatePath(origin, mouseTile);
	//			originSelected = false;
	//		}
	//		else
	//		{
	//			origin = mouseTile;
	//			originSelected = true;
	//			app->pathfinding->ClearLastPath();
	//		}
	//	}
	//	const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

	//	for (uint i = 0; i < path->Count(); ++i)
	//	{
	//		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
	//		app->render->DrawTexture(mouseTileTex, pos.x, pos.y);
	//	}

	//	// L12: Debug pathfinding
	//	iPoint originScreen = app->map->MapToWorld(origin.x, origin.y);
	//	app->render->DrawTexture(originTex, originScreen.x, originScreen.y);
	//}




	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{

	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->pathfinding->Disable();
	app->physics->Disable();
	app->entityManager->Disable();
	app->map->Disable();

	FirstScene = false;

	return true;
}
