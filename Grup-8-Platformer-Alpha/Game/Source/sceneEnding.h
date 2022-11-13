#ifndef __SceneEnding_H__
#define __SceneEnding_H__

#include "Module.h"

struct SDL_Texture;

class SceneEnding : public Module
{
public:

	SceneEnding(App* application, bool start_enabled = true);

	// Destructor
	virtual ~SceneEnding();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:

	// Texture
	SDL_Texture* logo;

	int count;

};

#endif // __SceneEnding_H__