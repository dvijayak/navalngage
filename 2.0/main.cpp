#include <cmath>

#include "SDLManager.hpp"
#include "Color.hpp"

#include "Polygon.hpp"

constexpr float PI = 3.14159265358979323846;

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
	RenderManager* pRM = pSDLMgr->GetRenderManager();

	Polygon3F* pTestPoly = Polygon3FFactory::CreateQuad(
		Point3F(0.2, 0.3),
		Point3F(0.8, 0.15),
		Point3F(0.6, 0.7),
		Point3F(0.27, 0.75)
		);
	Polygon3F* pTestPoly2 = Polygon3FFactory::CreateQuad(
		Point3F(0.1, 0.675),
		Point3F(0.19, 0.235),
		Point3F(0.75, 0.290),
		Point3F(0.81, 0.89)
		);
	constexpr float poly_r = 2;

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

		// For now, just animate the polygons
		for (auto& seg : pTestPoly->edges)
		{
			seg.start.x += 0.01;
			seg.end.x += 0.01;
		}
		for (auto& seg : pTestPoly2->edges)
		{
			seg.start.x -= 0.01;
			seg.end.x -= 0.01;
		}

		// Render screen
		pRM->FillScreenBackground();

		// pRM->DrawLine(0.2, 0.2, 0.6, 0.6, Color::Yellow);
		// pRM->DrawLine(0.2, 0.2, 0.6, 0.2345, Color::Yellow);
		// pRM->DrawLine(0.2, 0.2, 0.6, 0.21, Color::Yellow);
		// pRM->DrawLine(0.1124, 0.2345, 0.567, 0.6123, Color::Red);
		// pRM->DrawLine(0.1124, 0.2345, 0.567, 0.7123, Color::Red);
		// pRM->DrawLine(0.1124, 0.2345, 0.1124, 0.7345, Color::Red);
		// pRM->DrawLine(0.2, 0.2, 0.6, 0.6, Color::Orange);
		// pRM->DrawLine(0.8, 0.8, 0.4, 0.4, Color::Pink);
		// pRM->DrawLine(0.2, 0.8, 0.8, 0.2, Color::Cyan);
		// pRM->DrawLine(0.8, 0.4, 0.4, 0.8, Color::Red);
		pRM->DrawPolygon(*pTestPoly, Color::Green);
		pRM->DrawPolygon(*pTestPoly2, Color::Pink);

		pRM->Render();

		// Sleep!
		Uint32 current = SDL_GetTicks();
		SDL_Delay(16);
		Uint32 elapsed = SDL_GetTicks() - current;
		console("elapsed: " << elapsed);
	}
	delete pTestPoly;
	delete pTestPoly2;

	// Destroy managers/singletons and other resources
	SDLManager::Destroy();

	return 0;
}