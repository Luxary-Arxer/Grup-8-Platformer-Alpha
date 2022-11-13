#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneTitle.h"
#include "FadeToBlack.h"
#include "Defs.h"
#include "Log.h"

SceneTitle::SceneTitle(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("SceneTitle");
}

// Destructor
SceneTitle::~SceneTitle()
{}

// Called before render is available
bool SceneTitle::Awake()
{
	LOG("Loading Logo Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneTitle::Start()
{
	// Textures
	count = 0;
	logo = app->tex->Load("Assets/textures/SceneTitle.png");
	

	return true;
}

// Called each loop iteration
bool SceneTitle::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneTitle::Update(float dt)
{
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		app->fade->StartFadeToBlack(this, (Module*)app->scene, 20);
	}
	//if (count > 200) {
	//	app->fade->StartFadeToBlack(this, (Module*)app->scene, 90);
	//}
	//else {
	//	count++;
	//}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) {
		return false;
	}

	return true;

}

// Called each loop iteration
bool SceneTitle::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(logo, 0, 0);


	return ret;
}

// Called before quitting
bool SceneTitle::CleanUp()
{
	LOG("SceneTitle");

	app->tex->UnLoad(logo);

	return true;
}