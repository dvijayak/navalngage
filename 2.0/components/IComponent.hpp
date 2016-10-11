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

#endif