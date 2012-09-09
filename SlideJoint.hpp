#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

class SlideJoint : public Constraint {
protected:
	cpSlideJoint* slidejoint;
public:
	cpSlideJoint* get();
	const cpConstraintClass *getClass();
	SlideJoint(cp::Body *a,cp::Body *b,cp::Vect anchr1,cp::Vect anchr2,cpFloat min,cpFloat max);
	cp::Vect getAnchr1(void);
	void setAnchr1(cp::Vect value);
	cp::Vect getAnchr2(void);
	void setAnchr2(cp::Vect value);
	cpFloat getMin(void);
	void setMin(cpFloat value);
	cpFloat getMax(void);
	void setMax(cpFloat value);

};
};//namespace cp
