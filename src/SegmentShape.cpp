/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 22:41:26.
 */
#include "SegmentShape.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Vect.hpp"

namespace cp {

void SegmentShape::setEndpoints(cpVect a,cpVect b)
{
		cpSegmentShapeSetEndpoints(Shape::get(),a,b);
}
void SegmentShape::setRadius(cpFloat radius)
{
		cpSegmentShapeSetRadius(Shape::get(),radius);
}
SegmentShape::SegmentShape(cpBody *body,cpVect a,cpVect b,cpFloat radius)
	: Shape(cpSegmentShapeNew(body ? body->get() : 0,a,b,radius))
{
		shape->data = this;
}
void SegmentShape::setNeighbors(cpVect prev,cpVect next)
{
		cpSegmentShapeSetNeighbors(Shape::get(),prev,next);
}
cp::Vect SegmentShape::getA(void)
{
		return cpSegmentShapeGetA(shape);
}
cp::Vect SegmentShape::getB(void)
{
		return cpSegmentShapeGetB(shape);
}
cp::Vect SegmentShape::getNormal(void)
{
		return cpSegmentShapeGetNormal(shape);
}
cpFloat SegmentShape::getRadius(void)
{
		return cpSegmentShapeGetRadius(shape);
}
};//namespace cp
