#ifndef IEventHandler_HPP
#define IEventHandler_HPP

#include <vector>
#include <SDL2/SDL.h>

class Action;
class GameObjectFactory;


class IEventHandler
{
public:
	IEventHandler () {}
	virtual ~IEventHandler () {}

	/// Given an event, returns 0 or more corresponding actions. No game object state is
	/// normally changed here.
	/// ATTN: Caller is responsible for freeing all actions.
	/// @param [out] - resultant vector of actions
	/// @return bool - was at least 1 action returned?
	typedef std::vector<Action*> ResultType;
	virtual bool TranslateToAction (SDL_Event const&, GameObjectFactory const&, ResultType&) = 0;
};

#endif