#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneEnding.h"
#include "FadeToBlack.h"
#include "Defs.h"
#include "Log.h"

SceneEnding::SceneEnding(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("SceneEnding");
}

// Destructor
SceneEnding::~SceneEnding()
{}

// Called before render is available
bool SceneEnding::Awake()
{
	LOG("Loading Logo Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneEnding::Start()
{
	// Textures
	count = 0;
	logo = app->tex->Load("Assets/textures/SceneEnding.png");
	

	return true;
}

// Called each loop iteration
bool SceneEnding::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneEnding::Update(float dt)
{
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		app->fade->StartFadeToBlack(this, (Module*)app->sceneTitle, 10);
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
bool SceneEnding::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(logo, 0, 0);


	return ret;
}

// Called before quitting
bool SceneEnding::CleanUp()
{
	LOG("SceneEnding");

	app->tex->UnLoad(logo);

	return true;
}