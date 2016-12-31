#ifndef MouseKeyHandler_HPP
#define MouseKeyHandler_HPP

#include "IEventHandler.hpp"

class Action;

class MouseKeyHandler : virtual public IEventHandler
{
public:
	~MouseKeyHandler () {}

	/// IEventHandler
	bool TranslateToAction (SDL_Event const&, GameObjectFactory const&, std::vector<Action*>&);

	/// Singleton
	static MouseKeyHandler& Instance ();
	static void Destroy ();

private:	
	MouseKeyHandler ();

	static MouseKeyHandler* s_pInstance;
};

#endif