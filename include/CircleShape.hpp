/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 22:41:26.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"

namespace cp {

class CircleShape : public Shape {
protected:
	cpCircleShape* circleshape;
public:
	cpCircleShape* get(){
		return circleshape;
}
/// Set the radius of a circle shape.
	void setRadius(cpFloat radius);
/// Set the offset of a circle shape.
	void setOffset(cpVect offset);
/// Allocate and initialize a circle shape.
	CircleShape(cpBody *body,cpFloat radius,cpVect offset);
	cp::Vect getOffset(void);
	cpFloat getRadius(void);

};
};//namespace cp
