#pragma once
#include <Aqua/Core/Types.hpp>


class Entity {
public:
	Entity();
	virtual ~Entity();
	
	vec2 position;
	float rotation;
	vec2 scale;

	int drawLayer;
private:

};
