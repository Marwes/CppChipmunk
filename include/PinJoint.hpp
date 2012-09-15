/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/15/12 09:00:46.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"

namespace cp {

class PinJoint : public Constraint {
protected:
	cpPinJoint* pinjoint;
public:
	cpPinJoint* get();
	const cpConstraintClass *getClass();
/// Allocate and initialize a pin joint.
	PinJoint(cp::Body *a,cp::Body *b,cp::Vect anchr1,cp::Vect anchr2);
	cp::Vect getAnchr1(void);
	void setAnchr1(cp::Vect value);
	cp::Vect getAnchr2(void);
	void setAnchr2(cp::Vect value);
	cpFloat getDist(void);
	void setDist(cpFloat value);

};
};//namespace cp
