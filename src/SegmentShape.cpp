/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 11/12/12 01:17:41.
 */
#include "SegmentShape.hpp"
#include <utility>
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

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
SegmentShape::SegmentShape(SegmentShape&&o)
	: segmentshape(o.segmentshape),
	  Shape(std::move(o))
{
				o.segmentshape = 0;
}
};//namespace cp
