#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

class CircleShape : public Shape {
protected:
	cpCircleShape* circleshape;
public:
	cpCircleShape* get();
	CircleShape(cp::Body *body,cpFloat radius,cp::Vect offset);
	cp::Vect getOffset(void);
	cpFloat getRadius(void);

};
};//namespace cp
