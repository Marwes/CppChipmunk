#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

class PinJoint : public Constraint {
protected:
	cpPinJoint* pinjoint;
public:
	cpPinJoint* get();
	const cpConstraintClass *getClass();
	PinJoint(cp::Body *a,cp::Body *b,cp::Vect anchr1,cp::Vect anchr2);
	cp::Vect getAnchr1(void);
	void setAnchr1(cp::Vect value);
	cp::Vect getAnchr2(void);
	void setAnchr2(cp::Vect value);
	cpFloat getDist(void);
	void setDist(cpFloat value);

};
};//namespace cp
