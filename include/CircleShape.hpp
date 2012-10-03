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

class CircleShape : public Shape {
protected:
	cpCircleShape* circleshape;
public:
	cpCircleShape* get();
/// Allocate and initialize a circle shape.
	CircleShape(cp::Body *body,cpFloat radius,cp::Vect offset);
	cp::Vect getOffset(void);
	cpFloat getRadius(void);

};
};//namespace cp
