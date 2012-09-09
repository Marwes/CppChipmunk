#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

class SegmentShape : public Shape {
protected:
	cpSegmentShape* segmentshape;
public:
	cpSegmentShape* get();
	SegmentShape(cp::Body *body,cp::Vect a,cp::Vect b,cpFloat radius);
	void setNeighbors(cp::Vect prev,cp::Vect next);
	cp::Vect getA(void);
	cp::Vect getB(void);
	cp::Vect getNormal(void);
	cpFloat getRadius(void);

};
};//namespace cp
