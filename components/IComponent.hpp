#ifndef IComponent_HPP
#define IComponent_HPP

#include <string>

class IComponent
{
public:
	virtual ~IComponent () {};

	typedef std::string Name;
	virtual Name GetName () const = 0;
   virtual Name GetScriptName () const = 0; // used in scripting interfaces
};


/// These templates/macros offer a number of conveniences:
/// 1. inheritance from IComponent
/// 2. typedef for less verbose component type names
///    For example:
///    BodyComponent => CBody
///    go.Get<CBody>() is the same as go.Get<BodyComponent>()
/// 3. Automatic uniquely identifying name definition

template <class C>
struct ComponentMeta {};

#define DEFINE_COMPONENT(x) \
typedef class x##Component C##x; \
template <> struct ComponentMeta<x##Component> \
{ \
   static constexpr char const * Name = #x "Component"; \
   static constexpr char const * ScriptName = #x; \
}; \
class x##Component \
	: virtual public IComponent

#define DEFINE_COMPONENT_ESSENTIALS(x) \
public: \
   IComponent::Name GetName () const { return ComponentMeta<x##Component>::Name; } \
   IComponent::Name GetScriptName () const { return ComponentMeta<x##Component>::ScriptName; }


#endif