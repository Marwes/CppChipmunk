/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/19/12 14:10:01.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"

namespace cp {

class SegmentShape : public Shape {
protected:
	cpSegmentShape* segmentshape;
public:
	cpSegmentShape* get();
/// Allocate and initialize a segment shape.
	SegmentShape(cp::Body *body,cp::Vect a,cp::Vect b,cpFloat radius);
	void setNeighbors(cp::Vect prev,cp::Vect next);
	cp::Vect getA(void);
	cp::Vect getB(void);
	cp::Vect getNormal(void);
	cpFloat getRadius(void);

};
};//namespace cp
