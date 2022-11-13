#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneLogo.h"
#include "FadeToBlack.h"
#include "Defs.h"
#include "Log.h"

SceneLogo::SceneLogo(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("sceneLogo");
}

// Destructor
SceneLogo::~SceneLogo()
{}

// Called before render is available
bool SceneLogo::Awake()
{
	LOG("Loading Logo Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneLogo::Start()
{
	// Textures
	count = 0;
	logo = app->tex->Load("Assets/textures/IntroUPC.png");
	

	return true;
}

// Called each loop iteration
bool SceneLogo::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneLogo::Update(float dt)
{
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		app->fade->StartFadeToBlack(this, (Module*)app->sceneTitle, 30);
	}
	if (count > 300) {
		app->fade->StartFadeToBlack(this, (Module*)app->sceneTitle, 10);
	}
	else {
		count++;
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) {
		return false;
	}

	return true;

}

// Called each loop iteration
bool SceneLogo::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(logo, 0, 0);


	return ret;
}

// Called before quitting
bool SceneLogo::CleanUp()
{
	LOG("SceneLogo");

	app->tex->UnLoad(logo);

	return true;
}