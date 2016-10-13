#include "SDLManager.hpp"
#include "Game.hpp"

#include "LocomotionSystem.hpp"

int main (int argc, char** argv)
{	
	// Initialize SDL. Singleton destruction must be explicitly stated
	SDLManager* pSDLMgr = SDLManager::Instance("Naval Engagements 2.0", SDL_INIT_VIDEO);
	int init = pSDLMgr->InitializeManagers();
	if (init) {
		// Error reporting is taken care of in the SDL manager
		return init;
	}

	// Prepare managers
	RenderManager* pRM = pSDLMgr->GetRenderManager();

	// Initialize and run the game
	Game game;
	game.RegisterSystem(new LocomotionSystem());
	game.SetRenderer(pRM);
	int rc = game.Run();

	// Destroy managers/singletons and other resources
	SDLManager::Destroy();

	return rc;
}