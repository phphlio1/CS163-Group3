#include "Component.hpp"

using namespace Frontend;

Component::Component()
	: is_visible_(1)
{
	
}

bool Component::isVisible() const
{
	return is_visible_;
}

void Component::setVisibility(bool n_is_visible)
{
	is_visible_ = n_is_visible;
}
