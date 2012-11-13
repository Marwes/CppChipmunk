/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on Mon Nov 12 17:58:30 2012.
 */
#include "CircleShape.hpp"
#include <utility>
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

CircleShape::CircleShape(cp::Body *body,cpFloat radius,const cp::Vect& offset)
	: Shape(cpCircleShapeNew(body ? body->get() : 0,radius,offset))
{
		shape->data = this;
}
cp::Vect CircleShape::getOffset(void)
{
		return cpCircleShapeGetOffset(shape);
}
cpFloat CircleShape::getRadius(void)
{
		return cpCircleShapeGetRadius(shape);
}
CircleShape::CircleShape(CircleShape&&o)
	: circleshape(o.circleshape),
	  Shape(std::move(o))
{
				o.circleshape = 0;
}
};//namespace cp
