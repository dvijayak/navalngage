#ifndef Game_HPP
#define Game_HPP

#include <utility> // for std::pair
#include <vector>

#include "RenderManager.hpp"

#include "GameObjectFactory.hpp"
#include "ISystem.hpp"

#include "World.hpp"
#include "Geometry.hpp"

class Game
{
public:
	enum SystemUpdateOrder
	{
		MIDDLE = 0,
		FIRST,
		LAST
	};

	enum GameErrorCode
	{
		OK = 0,
		FAIL_UNKNOWN
	};

	Game ();
	~Game ();

	/// Set the FPS. Also resynchronizes the update time-step
	void SetTargetFrameRate (size_t);

	/// Register a game system.
	/// We are responsible for freeing all registered systems upon shutdown
	/// Currently, there is no way to unregister a system.
	bool RegisterSystem (ISystem*, int = SystemUpdateOrder::MIDDLE);

	/// Game loop. Expected to be called only once at the beginning of the game.
	int Run ();

	void SetRenderer (RenderManager* pRM) { m_pRenderer = pRM; }

private:
	GameObjectFactory m_factory;

	typedef std::vector< std::pair<int, ISystem*> > SystemListType;
	SystemListType m_systems;

	size_t m_targetFrameRate; // FPS
	size_t m_fixedUpdateTimeStep; // milliseconds, normally synced to target frame rate

	RenderManager* m_pRenderer;

	World m_world;
	PolygonF m_viewPort; // the same dimensions as the display area/screen
};

#endif