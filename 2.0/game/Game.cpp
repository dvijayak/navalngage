#include "Game.hpp"

#include "Color.hpp"
#include "Polygon.hpp"

#include "ShipBuilder.hpp"

constexpr size_t MAX_FPS = 240;
constexpr size_t MIN_FPS = 15;

Game::Game ()
	: m_targetFrameRate(60)
	, m_fixedUpdateTimeStep(1000/m_targetFrameRate)
	, m_pRenderer(0)
{}

Game::~Game ()
{
	for (auto& p : m_systems)
	{
		delete p.second;
	}
}

void Game::SetTargetFrameRate (size_t fps)
{
	if (fps > MAX_FPS)
	{
		fps = MAX_FPS;
	}
	else if (fps < MIN_FPS)
	{
		fps = MIN_FPS;
	}

	m_targetFrameRate = fps;
	m_fixedUpdateTimeStep = m_targetFrameRate/1000;
}

bool Game::RegisterSystem (ISystem* pSystem, int order)
{
	if (!pSystem)
	{
		return false;
	}

	bool rc = true;

	switch (order)
	{
		case SystemUpdateOrder::FIRST:
		{
			// Make this system the new foremost system to be run
			m_systems.insert(m_systems.begin(), std::make_pair(order, pSystem));		
			break;
		}
		case SystemUpdateOrder::LAST:
		{
			// Make this system the new last-most system to be run
			m_systems.push_back(std::make_pair(order, pSystem));		
			break;
		}
		case SystemUpdateOrder::MIDDLE:
		{
			// We don't care about where this system is inserted so long as it is
			// done so after the last FIRST system and before the first LAST system.
			// Just insert before the first LAST system if such a system exists
			// and if not, simply append.
			for (SystemListType::iterator it = m_systems.begin();; ++it)
			{
				// first => order, second => system pointer
				if (it == m_systems.end() || it->first == SystemUpdateOrder::LAST)
				{
					m_systems.insert(it, std::make_pair(order, pSystem));				
					break;
				}
			}

			break;
		}
		default:
		{
			rc = false;
		}
	}

	return rc;
}

int Game::Run ()
{
	/// TEST Polygon drawing
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

	/// TEST GO
	ShipBuilder sb(m_factory);
	sb.MakeDefault();
	GameObject& go = m_factory.Create(sb);
	console(go);

	GameObject* pResolvedGO = m_factory.Resolve(1);
	assert(pResolvedGO);
	console(*pResolvedGO);
	m_factory.Destroy(1);
	pResolvedGO = m_factory.Resolve(1);
	assert(!pResolvedGO);

	//// Game loop ////

	bool bExit = false; // flag used to exit the game loop
	int rc = GameErrorCode::OK;

	// Used in computing time-step
	size_t previous = SDL_GetTicks();
	size_t current = 0;
	size_t elapsed = 0;
	size_t lag = 0;

	// Spin away!
	while (!bExit)
	{
		// Calculate elapsed time-step
		// (Courtesy of Game Programming Patterns by Robert Nystrom)
		current = SDL_GetTicks();
		elapsed = current - previous;
		lag += elapsed;
		previous = current;
		// console("elapsed = " << elapsed << "  lag = " << lag);

		// TODO: Process events
		SDL_Event event;
		while (!bExit && SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				bExit = true;
				break;
			}
			else if (event.type == SDL_KEYUP)
			{
				// if ((event.key.keysym.mod == KMOD_LCTRL || event.key.keysym.mod == KMOD_RCTRL)
				// 	&& event.key.keysym.sym == SDLK_q)
				if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE)
				{
					bExit = true;
					break;
				}
			}
		}
		if (bExit) break; // exit the game loop

		// Update all systems using a series of fixed time-steps
		while (lag >= m_fixedUpdateTimeStep)
		{
			for (auto& p : m_systems)
			{
				assert(p.second); // system pointer is expected to be valid
				p.second->Update(m_fixedUpdateTimeStep, m_factory);
			}

			lag -= m_fixedUpdateTimeStep;
		}

		// For now, have a fake system - just animate the polygons
		for (auto& seg : pTestPoly->edges)
		{
			seg.start.x += 0.001;
			seg.end.x += 0.001;
		}
		for (auto& seg : pTestPoly2->edges)
		{
			seg.start.x -= 0.01;
			seg.end.x -= 0.01;
		}

		// TODO: Pass the (normalized?) lag to the renderer and use it

		// Render screen
		m_pRenderer->FillScreenBackground();

		// m_pRenderer->DrawLine(0.2, 0.2, 0.6, 0.6, Color::Yellow);
		// m_pRenderer->DrawLine(0.2, 0.2, 0.6, 0.2345, Color::Yellow);
		// m_pRenderer->DrawLine(0.2, 0.2, 0.6, 0.21, Color::Yellow);
		// m_pRenderer->DrawLine(0.1124, 0.2345, 0.567, 0.6123, Color::Red);
		// m_pRenderer->DrawLine(0.1124, 0.2345, 0.567, 0.7123, Color::Red);
		// m_pRenderer->DrawLine(0.1124, 0.2345, 0.1124, 0.7345, Color::Red);
		// m_pRenderer->DrawLine(0.2, 0.2, 0.6, 0.6, Color::Orange);
		// m_pRenderer->DrawLine(0.8, 0.8, 0.4, 0.4, Color::Pink);
		// m_pRenderer->DrawLine(0.2, 0.8, 0.8, 0.2, Color::Cyan);
		// m_pRenderer->DrawLine(0.8, 0.4, 0.4, 0.8, Color::Red);
		m_pRenderer->DrawPolygon(*pTestPoly, Color::Green);
		m_pRenderer->DrawPolygon(*pTestPoly2, Color::Pink);

		m_pRenderer->Render();

		// Consider sleeping a bit after a cycle to save power.energy on the host platform
		// TODO: Make this a configurable setting
		// For now, just disable it
		// SDL_Delay(m_fixedUpdateTimeStep);
	}

	delete pTestPoly;
	delete pTestPoly2;

	return rc;
}