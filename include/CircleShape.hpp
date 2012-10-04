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

class CircleShape : public Shape {
protected:
	cpCircleShape* circleshape;
public:
	cpCircleShape* get(){
		return circleshape;
}
/// Allocate and initialize a circle shape.
	CircleShape(cpBody *body,cpFloat radius,cpVect offset);
	cp::Vect getOffset(void);
	cpFloat getRadius(void);

};
};//namespace cp
