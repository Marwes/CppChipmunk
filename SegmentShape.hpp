#pragma once

#include "chipmunk.h"
#include "Vect.hpp"
#include "Shape.hpp"

namespace cp {


class SegmentShape : public Shape{
protected:
	cpSegmentShape*segmentshape;
public:

	cpSegmentShape* get() const
	{
		return segmentshape;
	}

	operator cpSegmentShape*() const
	{
		return segmentshape;
	}

	inline void setNeighbors(cpVect prev,cpVect next)
	{
		cpSegmentShapeSetNeighbors(shape,prev,next);
	}

	inline cp::Vect getA(void)
	{
		return cpSegmentShapeGetA(shape);
	}

	inline cp::Vect getB(void)
	{
		return cpSegmentShapeGetB(shape);
	}

	inline cp::Vect getNormal(void)
	{
		return cpSegmentShapeGetNormal(shape);
	}

	inline cpFloat getRadius(void)
	{
		return cpSegmentShapeGetRadius(shape);
	}

	SegmentShape(cpBody *body,cpVect a,cpVect b,cpFloat radius)
	 : Shape(cpSegmentShapeNew(body,a,b,radius))
	{
		shape->data = this;
	}

};
}//namespace cp
