#ifndef SDLMANAGER_H
#define SDLMANAGER_H

#include "global.hpp"

#include "WindowManager.hpp"
#include "RenderManager.hpp"

const int MAX_WIDTH = 1024;
const int MAX_HEIGHT = 768;

class SDLManager
{
public:
	static SDLManager* Instance (const std::string& title="Untitled", Uint32 flags=0);
	~SDLManager();
	static void Destroy ();

	int InitializeManagers ();

	WindowManager* GetWindowManager ();	
	RenderManager* GetRenderManager ();	

private:
	SDLManager () {};
	SDLManager (const std::string& title="Untitled", Uint32 flags=0);	
	static SDLManager* s_pInstance;

	std::string m_title;

	// We possess ownership of all managers 
	WindowManager* m_pWindowManager;
	RenderManager* m_pRenderManager;	
};

inline void SDLManager::Destroy ()
{
	if (s_pInstance)
	{
		delete s_pInstance;
	}
}

#endif
