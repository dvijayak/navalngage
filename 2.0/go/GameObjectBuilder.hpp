#ifndef GameObjectBuilder_hpp
#define GameObjectBuilder_hpp

#include <vector>
#include "GameObject.hpp"

class GameObjectBuilder
{
public:
	virtual ~GameObjectBuilder () {}

	/// The GO is constructed using default settings as defined by the 
	/// implementing concrete builder
	virtual void MakeDefault () = 0;

	/// Complete the construction of a GO. Can be called for
	/// different GOs. Such builder reuse is in fact encouraged.
	virtual void GetResult (GameObject& go);

	/// Clears the state of the builder such that it is as good
	/// as a brand new builder. This is provided as a convenience
	/// permitting reuse of the same builder object within some scope.
	virtual void Reset ();

protected:
	typedef std::vector<IComponent*> ComponentContainerType;
	ComponentContainerType m_components;
};

#endif