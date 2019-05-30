#ifndef MouseKeyHandler_HPP
#define MouseKeyHandler_HPP

#include "IEventHandler.hpp"

#include <memory>
#include <set>

class Action;

class MouseKeyHandler : virtual public IEventHandler
{
public:
	~MouseKeyHandler () {}

	/// IEventHandler
	bool TranslateToAction (SDL_Event const&, GameObjectFactory const&, IEventHandler::ResultType&);

	/// Constructs actions that are to be performed every frame
	bool TranslateToActionPerFrame (GameObjectFactory const&, IEventHandler::ResultType&);

	/// Singleton
	static MouseKeyHandler& Instance ();
	static void Destroy ();

private:	
	MouseKeyHandler ();

	/// Called once when a key has been pressed down (and has not
	/// yet been released). The boolean out parameter indicates
	/// whether the key press needs to be tracked for hold/long-
	/// press behaviour.
	void HandleKeyPressed (int key, GameObjectFactory const&, IEventHandler::ResultType&, bool&);

	/// Called continuously (normally once per frame) while the
	/// given key is being held (long-press).
	void HandleKeyHeld (int key, GameObjectFactory const&, IEventHandler::ResultType&);

	/// Called once when a key that was pressed (whether long-press
	/// or a normal one-shot press) is then released.
	void HandleKeyReleased (int key, GameObjectFactory const&, IEventHandler::ResultType&);

	typedef std::set<int> KeyTrackerType;
	/// Tracks what keys are being held. Useful for implementing
	/// per frame actions that are performed based on the currently
	/// held keys. Note that some actions assume that the press and
	/// release events for a particular key occur in different frames.
	/// Future improvements: track how long the key has been pressed for.
	KeyTrackerType m_keyTracker;

	bool KeyIsBeingHeld (int) const;

	static std::unique_ptr<MouseKeyHandler> s_pInstance;
};

inline bool MouseKeyHandler::KeyIsBeingHeld (int key) const 
{
	return m_keyTracker.find(key) != m_keyTracker.end();
}

#endif