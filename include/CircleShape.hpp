/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 11/12/12 01:02:18.
 */
#pragma once

#include <utility>
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"

namespace cp {

class CircleShape : public Shape {
protected:
	cpCircleShape* circleshape;
public:
	inline cpCircleShape* get(){
		return circleshape;
}
/// Allocate and initialize a circle shape.
	CircleShape(cp::Body *body,cpFloat radius,cp::Vect offset);
	cp::Vect getOffset(void);
	cpFloat getRadius(void);
	CircleShape(CircleShape&&o);
private:
//Hiding copy constructor and assignmentCircleShape(const CircleShape&);
CircleShape& operator=(const CircleShape&);

};
};//namespace cp
