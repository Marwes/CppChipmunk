#pragma once

#include "chipmunk.h"
#include "Vect.hpp"
#include "Shape.hpp"

namespace cp {


class CircleShape : public Shape{
protected:
	cpCircleShape*circleshape;
public:

	cpCircleShape* get() const
	{
		return circleshape;
	}

	operator cpCircleShape*() const
	{
		return circleshape;
	}

	inline cp::Vect getOffset(void)
	{
		return cpCircleShapeGetOffset(shape);
	}

	inline cpFloat getRadius(void)
	{
		return cpCircleShapeGetRadius(shape);
	}

	CircleShape(cpBody *body,cpFloat radius,cpVect offset)
	 : Shape(cpCircleShapeNew(body,radius,offset))
	{
		shape->data = this;
	}

};
}//namespace cp
