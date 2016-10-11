#include "SDLManager.hpp"
#include "Color.hpp"

#include "GameObjectFactory.hpp"
#include "PositionComponent.hpp"
#include "MassComponent.hpp"
#include "RotationComponent.hpp"
#include "ShipComponent.hpp"
#include "MovementComponent.hpp"

int main (int argc, char** argv)
{	
	// Initialize SDL. Singleton destruction must be explicitly stated
	SDLManager* pSDLMgr = SDLManager::Instance("Naval Engagements 2.0", SDL_INIT_VIDEO);
	int init = pSDLMgr->InitializeManagers();
	if (init) {
		// ??
		return init;
	}

	// Prepare managers
	RenderManager* p_rm = pSDLMgr->GetRenderManager();

	// TEST:
	GameObjectFactory& factory = GameObjectFactory::Instance();
	GameObject& go = factory.Create();
	go.AddComponent(new PositionComponent(0.8, 0.234));
	go.AddComponent(new MassComponent(0.5));
	go.AddComponent(new MovementComponent(1.0, 280.23));
	go.AddComponent(new RotationComponent(0.2));
	go.AddComponent(new ShipComponent(3));

	PositionComponent* pPos = go.GetComponent<PositionComponent>();
	console(pPos->x << "\t" << pPos->y);

	MassComponent* pMass = go.GetComponent<MassComponent>();
	console(pMass->mass);

	MovementComponent* pMove = go.GetComponent<MovementComponent>();
	console(pMove->speed << "\t" << pMove->heading);

	RotationComponent* pRot = go.GetComponent<RotationComponent>();
	console(pRot->angular_speed);

	ShipComponent* pShip = go.GetComponent<ShipComponent>();
	console(pShip->ship_class);

	// Game loop
	bool bExit = false; // Changing this flag performs a 'lazy' quit. Use bExitImmediately and break to exit the loop immediately
	bool bExitImmediately = false;
	while (!bExit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				bExitImmediately = true;
				break;
			}
			else if (event.type == SDL_KEYUP)
			{
				// if ((event.key.keysym.mod == KMOD_LCTRL || event.key.keysym.mod == KMOD_RCTRL)
				// 	&& event.key.keysym.sym == SDLK_q)
				if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE)
				{
					bExit = true;
				}
			}
		}
		if (bExitImmediately) break;

		// TODO: Run all systems (drawing system should be the last one)

		// Render screen
		p_rm->FillScreenBackground();
		p_rm->Render();
	}

	// Destroy managers/singletons and other resources
	SDLManager::Destroy();

	return 0;
}