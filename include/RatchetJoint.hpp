/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

namespace cp {

class RatchetJoint : public Constraint {
protected:
	cpRatchetJoint* ratchetjoint;
public:
	cpRatchetJoint* get();
	const cpConstraintClass *getClass();
	RatchetJoint(cp::Body *a,cp::Body *b,cpFloat phase,cpFloat ratchet);
	cpFloat getAngle(void);
	void setAngle(cpFloat value);
	cpFloat getPhase(void);
	void setPhase(cpFloat value);
	cpFloat getRatchet(void);
	void setRatchet(cpFloat value);

};
};//namespace cp
