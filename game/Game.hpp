#ifndef Game_HPP
#define Game_HPP

#include <memory>
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

	void SetScreenWidth (float width) { m_screenWidth = width; }
	void SetScreenHeight (float height) { m_screenHeight = height; }

	/// Performed once normally at the beginning of each frame
	bool ProcessEvents ();

	/// Performed once normally at the end of each frame
	void DrawWorld (float dt); // dt => normalized lag, i.e. how far into the next frame update cycle the game loop is currently in

private:
	GameObjectFactory m_factory;

	typedef std::vector< std::pair<int, std::unique_ptr<ISystem>> > SystemListType;
	SystemListType m_systems;

	size_t m_targetFrameRate; // FPS
	size_t m_fixedUpdateTimeStep; // milliseconds, normally synced to target frame rate

	RenderManager* m_pRenderer;

	World m_world;

	GameObject* m_pCamera;

	// TODO: these should update as the window is resized. I should probably implement
	// the Observer pattern in due time...
	float m_screenWidth;
	float m_screenHeight;
};

#endif