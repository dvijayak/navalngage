#ifndef ActionReplay_hpp
#define ActionReplay_hpp 1

#include "global.hpp"

#include <string>
#include <vector>

class Action;
struct RecorderImpl;

class ActionReplay
{
public:
	~ActionReplay ();

	/// If true, then the game is currently in replay mode
	bool IsActive () const;

	/// A replay file is provided as input. If it is
	/// successfully processed, the game enters replay mode.
	/// CANIMPROVE: for simplicity, we have no concept of
	/// deactivation; the game can only be either in replay
	/// mode or in normal play mode.
	bool Activate (std::string const&); 

	/// Plays through all recorded actions
	void Replay ();

	/// Records the given action into the internally determined
	/// storage medium. This is only done when in normal mode,
	/// i.e. not in action replay mode.
	void RecordAction (Action const&);

	/// Singleton
	static ActionReplay& Instance ();
	static void Destroy ();
	
private:
	ActionReplay ();

	void ProcessReplayFileLine (std::string&);

	bool m_bActive;
	std::string m_filename;
	RecorderImpl* m_pRecorder; // hide implementation detail in cpp file

	typedef std::vector<Action*> ActionsType;
	ActionsType m_recordedActions;

	static ActionReplay* s_pInstance;
};

inline bool ActionReplay::IsActive () const
{
	return m_bActive;
}

#endif