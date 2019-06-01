#ifndef IComponent_HPP
#define IComponent_HPP

#include <string>

class IComponent
{
public:
	virtual ~IComponent () {};

	typedef std::string Name;
	virtual Name GetName () const = 0;
};

/// This macro offers a few conveniences:
/// 1. inheritance from IComponent
/// 2. typedef for less verbose component type names
/// 	 For example:
/// 	 BodyComponent => CBody
///    go.Get<CBody>() is the same as go.Get<BodyComponent>()
#define DEFINE_COMPONENT(x) \
typedef class x##Component C##x; \
class x##Component \
	: virtual public IComponent

#define DEFINE_COMPONENT_ESSENTIALS(x) \
public: \
   static const IComponent::Name NAME; \
   IComponent::Name GetName () const { return NAME; } \


#endif