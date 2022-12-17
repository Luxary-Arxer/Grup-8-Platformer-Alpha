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

	// iterate all objects in the scene
	// Check https://pugixml.org/docs/quickstart.html#access
	for (pugi::xml_node itemNode = config.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	{
		Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
		item->parameters = itemNode;

	}

	enemy1 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	enemy1->parameters = config.child("enemy1");

	enemy2 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	enemy2->parameters = config.child("enemy2");

	//enemy3 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	//enemy3->parameters = config.child("enemy3");

	//enemy4 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	//enemy4->parameters = config.child("enemy4");

	//enemy5 = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	//enemy5->parameters = config.child("enemy5");

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
		//Player
		app->entityManager->AddEntity(player);
		player->position.x = 256;
		player->position.y = 586;

		//Enemies
		app->entityManager->AddEntity(enemy1);
		enemy1->position.x = 416;
		enemy1->position.y = 547; 
		app->entityManager->AddEntity(enemy2);
		enemy2->position.x = 928;
		enemy2->position.y = 512;
		//app->entityManager->AddEntity(enemy3);
		//enemy3->position.x = 1728;
		//enemy3->position.y = 256;
		//app->entityManager->AddEntity(enemy4);
		//enemy4->position.x = 2496;
		//enemy4->position.y = 544;
		//app->entityManager->AddEntity(enemy5);
		//enemy5->position.x = 4000;
		//enemy5->position.y = 512;
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

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y += 7;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y -= 7;

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x += 7;

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x -= 7;



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

	app->entityManager->DestroyEntity(player);
	app->entityManager->DestroyEntity(enemy1);
	app->entityManager->DestroyEntity(enemy2);

	app->pathfinding->Disable();
	app->physics->Disable();
	app->entityManager->Disable();
	app->map->Disable();

	FirstScene = false;

	return true;
}
