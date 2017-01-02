#include "global.hpp"

#include <string>
#include <sstream>
#include <fstream>

#include "SDLManager.hpp"
#include "Game.hpp"
#include "ActionReplay.hpp"

#include "LocomotionSystem.hpp"
#include "CameraSystem.hpp"


int main (int argc, char** argv)
{
	INITIALIZE_BASIC_LOGGERS(4096)

	// TODO: Proper handling of command-line arguments
	if (argc > 1)
	{
		if (!ActionReplay::Instance().Activate(argv[1]))
		{
			console("Failed to activate action replay mode. Reverting to normal play mode."); // TODO: remove console statement once finished development/debugging
			errlog("Failed to activate action replay mode. Reverting to normal play mode.");
		}
	}

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
	// The block ensures that game-related resources are released as soon as the game
	// finishes running. This is done via RAII.
	int rc;
	{
		Game game;

		// System registration (order is significant!)
		game.RegisterSystem(new LocomotionSystem());
		game.RegisterSystem(new CameraSystem());

		// Configuration
		game.SetRenderer(pRM);
		game.SetScreenWidth(pSDLMgr->GetWindowManager()->GetWidth());
		game.SetScreenHeight(pSDLMgr->GetWindowManager()->GetHeight());

		// Go!
		rc = game.Run();
	}

	// Destroy managers/singletons and other resources
	SDLManager::Destroy();

	spdlog::drop_all(); 	// in Windows, this must be called before main finishes to workaround a known VS issue

	return rc;
}