#ifndef CameraAction_hpp
#define CameraAction_hpp

#include "Action.hpp"

class CameraAction : virtual public Action
{
public:
	CameraAction () : Action() {}
	virtual ~CameraAction () {}

	/// Action
	virtual void Perform () = 0;
	void SetSource (GameObject* pGo);

	inline void SetCamera (GameObject* pGo) { SetSource(pGo); } // convenience function
};

#endif