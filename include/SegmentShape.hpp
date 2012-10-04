/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:40:05.
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
	cpSegmentShape* get(){
		return segmentshape;
}
/// Allocate and initialize a segment shape.
	SegmentShape(cpBody *body,cpVect a,cpVect b,cpFloat radius);
	void setNeighbors(cpVect prev,cpVect next);
	cp::Vect getA(void);
	cp::Vect getB(void);
	cp::Vect getNormal(void);
	cpFloat getRadius(void);

};
};//namespace cp
