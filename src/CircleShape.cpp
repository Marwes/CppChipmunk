/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:40:05.
 */
#include "CircleShape.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Vect.hpp"

namespace cp {

CircleShape::CircleShape(cpBody *body,cpFloat radius,cpVect offset)
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
};//namespace cp
