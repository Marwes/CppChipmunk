/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 20:19:55.
 */
#include "CircleShape.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

CircleShape::CircleShape(cp::Body *body,cpFloat radius,cp::Vect offset)
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
