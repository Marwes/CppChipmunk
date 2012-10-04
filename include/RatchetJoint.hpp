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

class RatchetJoint : public Constraint {
protected:
	cpRatchetJoint* ratchetjoint;
public:
	cpRatchetJoint* get(){
		return ratchetjoint;
}
	const cpConstraintClass *getClass();
/// Allocate and initialize a ratchet joint.
	RatchetJoint(cpBody *a,cpBody *b,cpFloat phase,cpFloat ratchet);
	cpFloat getAngle(void);
	void setAngle(cpFloat value);
	cpFloat getPhase(void);
	void setPhase(cpFloat value);
	cpFloat getRatchet(void);
	void setRatchet(cpFloat value);

};
};//namespace cp
