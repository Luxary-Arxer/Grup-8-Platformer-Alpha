#include "App.h"
#include "Window.h"
#include "Render.h"
#include "Player.h"
#include "Scene.h"
#include "EntityManager.h"

#include "Defs.h"
#include "Log.h"

#define VSYNC true

Render::Render(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("renderer");
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
}

// Destructor
Render::~Render()
{}

// Called before render is available
bool Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;

	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if (config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(app->win->window, -1, flags);

	if(renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		camera.w = app->win->screenSurface->w;
		camera.h = app->win->screenSurface->h;
		camera.x = 0;
		camera.y = 0;
	}

	return ret;
}

// Called before the first frame
bool Render::Start()
{
	LOG("render start");
	// back background
	SDL_RenderGetViewport(renderer, &viewport);
	return true;
}

// Called each loop iteration
bool Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool Render::Update(float dt)
{
	return true;
}

bool Render::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}

// Called before quitting
bool Render::CleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

void Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

void Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

// Blit to screen
bool Render::DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, double angle, int pivotX, int pivotY) const
{
	bool ret = true;
	uint scale = app->win->GetScale();

	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * scale;
	rect.y = (int)(camera.y * speed) + y * scale;

	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= scale;
	rect.h *= scale;

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if(pivotX != INT_MAX && pivotY != INT_MAX)
	{
		pivot.x = pivotX;
		pivot.y = pivotY;
		p = &pivot;
	}

	if(SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled, bool use_camera) const
{
	bool ret = true;
	uint scale = app->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if(use_camera)
	{
		rec.x = (int)(camera.x + rect.x * scale);
		rec.y = (int)(camera.y + rect.y * scale);
		rec.w *= scale;
		rec.h *= scale;
	}

	int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = app->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;

	if(use_camera)
		result = SDL_RenderDrawLine(renderer, camera.x + x1 * scale, camera.y + y1 * scale, camera.x + x2 * scale, camera.y + y2 * scale);
	else
		result = SDL_RenderDrawLine(renderer, x1 * scale, y1 * scale, x2 * scale, y2 * scale);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = app->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;
	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	for(uint i = 0; i < 360; ++i)
	{
		points[i].x = (int)(camera.x + x + radius * cos(i * factor));
		points[i].y = (int)(camera.y + y + radius * sin(i * factor));
	}

	result = SDL_RenderDrawPoints(renderer, points, 360);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

// L03: DONE 6: Implement a method to load the state
// for now load camera's x and y
bool Render::LoadState(pugi::xml_node& data)
{
	app->scene->player->cam = false;
	camera.x = data.child("camera").attribute("x").as_int();
	camera.y = data.child("camera").attribute("y").as_int();
	int x;
	int y;
	bool death;
	x = data.child("position").attribute("x").as_int();
	y = data.child("position").attribute("y").as_int();
	app->scene->player->LoadPosition(x,y);

	//Enemies
	x = data.child("enemy1").attribute("x").as_int();
	y = data.child("enemy1").attribute("y").as_int();
	death = data.child("enemy1").attribute("death").as_bool();
	app->scene->enemy1->LoadPosition(x, y, death);

	x = data.child("enemy2").attribute("x").as_int();
	y = data.child("enemy2").attribute("y").as_int();
	death = data.child("enemy2").attribute("death").as_bool();
	app->scene->enemy2->LoadPosition(x, y, death);

	x = data.child("enemy3").attribute("x").as_int();
	y = data.child("enemy3").attribute("y").as_int();
	death = data.child("enemy3").attribute("death").as_bool();
	app->scene->enemy3->LoadPosition(x, y, death);

	x = data.child("enemy4").attribute("x").as_int();
	y = data.child("enemy4").attribute("y").as_int();
	death = data.child("enemy4").attribute("death").as_bool();
	app->scene->enemy4->LoadPosition(x, y, death);

	x = data.child("enemy5").attribute("x").as_int();
	y = data.child("enemy5").attribute("y").as_int();
	death = data.child("enemy5").attribute("death").as_bool();
	app->scene->enemy5->LoadPosition(x, y, death);
	
	x = data.child("enemy6").attribute("x").as_int();
	y = data.child("enemy6").attribute("y").as_int();
	death = data.child("enemy6").attribute("death").as_bool();
	app->scene->enemy6->LoadPosition(x, y, death);

	x = data.child("enemy7").attribute("x").as_int();
	y = data.child("enemy7").attribute("y").as_int();
	death = data.child("enemy7").attribute("death").as_bool();
	app->scene->enemy7->LoadPosition(x, y, death);

	//Enemies air
	x = data.child("enemy1_aire").attribute("x").as_int();
	y = data.child("enemy1_aire").attribute("y").as_int();
	death = data.child("enemy1_aire").attribute("death").as_bool();
	app->scene->enemyaire1->LoadPosition(x, y, death);

	x = data.child("enemy2_aire").attribute("x").as_int();
	y = data.child("enemy2_aire").attribute("y").as_int();
	death = data.child("enemy2_aire").attribute("death").as_bool();
	app->scene->enemyaire2->LoadPosition(x, y, death);
	//Coins 
	death = data.child("coin1").attribute("death").as_bool();
	app->scene->coin1->LoadPosition(death);
	death = data.child("coin2").attribute("death").as_bool();
	app->scene->coin2->LoadPosition(death);
	death = data.child("coin3").attribute("death").as_bool();
	app->scene->coin3->LoadPosition(death);
	death = data.child("coin4").attribute("death").as_bool();
	app->scene->coin4->LoadPosition(death);
	death = data.child("coin5").attribute("death").as_bool();
	app->scene->coin5->LoadPosition(death);
	death = data.child("coin6").attribute("death").as_bool();
	app->scene->coin6->LoadPosition(death);
	death = data.child("coin7").attribute("death").as_bool();
	app->scene->coin7->LoadPosition(death);
	death = data.child("coin8").attribute("death").as_bool();
	app->scene->coin8->LoadPosition(death);
	death = data.child("coin9").attribute("death").as_bool();
	app->scene->coin9->LoadPosition(death);
	death = data.child("coin10").attribute("death").as_bool();
	app->scene->coin10->LoadPosition(death);
	death = data.child("coin11").attribute("death").as_bool();
	app->scene->coin11->LoadPosition(death);
	death = data.child("coin12").attribute("death").as_bool();
	app->scene->coin12->LoadPosition(death);
	death = data.child("coin13").attribute("death").as_bool();
	app->scene->coin13->LoadPosition(death);
	death = data.child("coin14").attribute("death").as_bool();
	app->scene->coin14->LoadPosition(death);
	death = data.child("coin15").attribute("death").as_bool();
	app->scene->coin15->LoadPosition(death);
	death = data.child("coin16").attribute("death").as_bool();
	app->scene->coin16->LoadPosition(death);
	death = data.child("coin17").attribute("death").as_bool();
	app->scene->coin17->LoadPosition(death);
	death = data.child("coin18").attribute("death").as_bool();
	app->scene->coin18->LoadPosition(death);
	death = data.child("coin19").attribute("death").as_bool();
	app->scene->coin19->LoadPosition(death);
	//Checkpoint
	death = data.child("checkpoint1").attribute("death").as_bool();
	app->scene->checkpoint1->LoadPosition(death);

	death = data.child("checkpoint2").attribute("death").as_bool();
	app->scene->checkpoint2->LoadPosition(death);

	death = data.child("checkpoint3").attribute("death").as_bool();
	app->scene->checkpoint3->LoadPosition(death);
	
	return true;
}

// L03: DONE 8: Create a method to save the state of the renderer
// using append_child and append_attribute
bool Render::SaveState(pugi::xml_node& data)
{
	pugi::xml_node cam = data.append_child("camera");

	cam.append_attribute("x") = camera.x;
	cam.append_attribute("y") = camera.y;

	pugi::xml_node pos = data.append_child("position");

	pos.append_attribute("x") = app->scene->player->position.x;
	pos.append_attribute("y") = app->scene->player->position.y;

	//Enemies
	pugi::xml_node en1 = data.append_child("enemy1");

	en1.append_attribute("x") = app->scene->enemy1->position.x;
	en1.append_attribute("y") = app->scene->enemy1->position.y;
	en1.append_attribute("death") = app->scene->enemy1->hit;

	pugi::xml_node en2 = data.append_child("enemy2");

	en2.append_attribute("x") = app->scene->enemy2->position.x;
	en2.append_attribute("y") = app->scene->enemy2->position.y;
	en2.append_attribute("death") = app->scene->enemy2->hit;

	pugi::xml_node en3 = data.append_child("enemy3");

	en3.append_attribute("x") = app->scene->enemy3->position.x;
	en3.append_attribute("y") = app->scene->enemy3->position.y;
	en3.append_attribute("death") = app->scene->enemy3->hit;

	pugi::xml_node en4 = data.append_child("enemy4");

	en4.append_attribute("x") = app->scene->enemy4->position.x;
	en4.append_attribute("y") = app->scene->enemy4->position.y;
	en4.append_attribute("death") = app->scene->enemy4->hit;

	pugi::xml_node en5 = data.append_child("enemy5");

	en5.append_attribute("x") = app->scene->enemy5->position.x;
	en5.append_attribute("y") = app->scene->enemy5->position.y;
	en5.append_attribute("death") = app->scene->enemy5->hit;

	pugi::xml_node en6 = data.append_child("enemy6");

	en6.append_attribute("x") = app->scene->enemy6->position.x;
	en6.append_attribute("y") = app->scene->enemy6->position.y;
	en6.append_attribute("death") = app->scene->enemy6->hit;

	pugi::xml_node en7 = data.append_child("enemy7");

	en7.append_attribute("x") = app->scene->enemy7->position.x;
	en7.append_attribute("y") = app->scene->enemy7->position.y;
	en7.append_attribute("death") = app->scene->enemy7->hit;

	//Enemies air
	pugi::xml_node en1_air = data.append_child("enemy1_aire");

	en1_air.append_attribute("x") = app->scene->enemyaire1->position.x;
	en1_air.append_attribute("y") = app->scene->enemyaire1->position.y;
	en1_air.append_attribute("death") = app->scene->enemyaire1->hit;

	pugi::xml_node en2_air = data.append_child("enemy2_aire");

	en2_air.append_attribute("x") = app->scene->enemyaire2->position.x;
	en2_air.append_attribute("y") = app->scene->enemyaire2->position.y;
	en2_air.append_attribute("death") = app->scene->enemyaire2->hit;

	//Coins 
	pugi::xml_node coin1 = data.append_child("coin1");
	coin1.append_attribute("death") = app->scene->coin1->hit;
	pugi::xml_node coin2 = data.append_child("coin2");
	coin2.append_attribute("death") = app->scene->coin2->hit;
	pugi::xml_node coin3 = data.append_child("coin3");
	coin3.append_attribute("death") = app->scene->coin3->hit;
	pugi::xml_node coin4 = data.append_child("coin4");
	coin4.append_attribute("death") = app->scene->coin4->hit;
	pugi::xml_node coin5 = data.append_child("coin5");
	coin5.append_attribute("death") = app->scene->coin5->hit;
	pugi::xml_node coin6 = data.append_child("coin6");
	coin6.append_attribute("death") = app->scene->coin6->hit;
	pugi::xml_node coin7 = data.append_child("coin7");
	coin7.append_attribute("death") = app->scene->coin7->hit;
	pugi::xml_node coin8 = data.append_child("coin8");
	coin8.append_attribute("death") = app->scene->coin8->hit;
	pugi::xml_node coin9 = data.append_child("coin9");
	coin9.append_attribute("death") = app->scene->coin9->hit;
	pugi::xml_node coin10 = data.append_child("coin10");
	coin10.append_attribute("death") = app->scene->coin10->hit;
	pugi::xml_node coin11 = data.append_child("coin11");
	coin11.append_attribute("death") = app->scene->coin11->hit;
	pugi::xml_node coin12 = data.append_child("coin12");
	coin12.append_attribute("death") = app->scene->coin12->hit;
	pugi::xml_node coin13 = data.append_child("coin13");
	coin13.append_attribute("death") = app->scene->coin13->hit;
	pugi::xml_node coin14 = data.append_child("coin14");
	coin14.append_attribute("death") = app->scene->coin14->hit;
	pugi::xml_node coin15 = data.append_child("coin15");
	coin15.append_attribute("death") = app->scene->coin15->hit;
	pugi::xml_node coin16 = data.append_child("coin16");
	coin16.append_attribute("death") = app->scene->coin16->hit;
	pugi::xml_node coin17 = data.append_child("coin17");
	coin17.append_attribute("death") = app->scene->coin17->hit;
	pugi::xml_node coin18 = data.append_child("coin18");
	coin18.append_attribute("death") = app->scene->coin18->hit;
	pugi::xml_node coin19 = data.append_child("coin19");
	coin19.append_attribute("death") = app->scene->coin19->hit;

	//Checkpoint
	pugi::xml_node checkpoint1 = data.append_child("checkpoint1");
	checkpoint1.append_attribute("death") = app->scene->checkpoint1->hit;

	pugi::xml_node checkpoint2 = data.append_child("checkpoint2");
	checkpoint2.append_attribute("death") = app->scene->checkpoint2->hit;

	pugi::xml_node checkpoint3 = data.append_child("checkpoint3");
	checkpoint3.append_attribute("death") = app->scene->checkpoint3->hit;

	return true;
}
