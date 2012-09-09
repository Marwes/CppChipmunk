/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
 */
#include "CircleShape.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

cpCircleShape* CircleShape::get()
{
		return circleshape;
}
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
