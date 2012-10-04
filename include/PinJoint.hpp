/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:56:58.
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
	cpPinJoint* get(){
		return pinjoint;
}
	const cpConstraintClass *getClass();
/// Allocate and initialize a pin joint.
	PinJoint(cpBody *a,cpBody *b,cpVect anchr1,cpVect anchr2);
	cp::Vect getAnchr1(void);
	void setAnchr1(cp::Vect value);
	cp::Vect getAnchr2(void);
	void setAnchr2(cp::Vect value);
	cpFloat getDist(void);
	void setDist(cpFloat value);

};
};//namespace cp
