/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
 */
#include "SegmentShape.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

cpSegmentShape* SegmentShape::get()
{
		return segmentshape;
}
SegmentShape::SegmentShape(cp::Body *body,cp::Vect a,cp::Vect b,cpFloat radius)
	: Shape(cpSegmentShapeNew(body ? body->get() : 0,a,b,radius))
{
		shape->data = this;
}
void SegmentShape::setNeighbors(cp::Vect prev,cp::Vect next)
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
