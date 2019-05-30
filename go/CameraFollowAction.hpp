#ifndef CameraFollowAction_hpp
#define CameraFollowAction_hpp

#include "CameraAction.hpp"

class CameraFollowAction : virtual public CameraAction
{
public:
	CameraFollowAction () : CameraAction() {}
	virtual ~CameraFollowAction () {}

	/// Action
	void Perform ();
	std::string str () const;
	void SetTarget (GameObject* pGo);
};

#endif