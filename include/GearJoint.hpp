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

class GearJoint : public Constraint {
protected:
	cpGearJoint* gearjoint;
public:
	cpGearJoint* get();
	const cpConstraintClass *getClass();
/// Allocate and initialize a gear joint.
	GearJoint(cp::Body *a,cp::Body *b,cpFloat phase,cpFloat ratio);
/// Set the ratio of a gear joint.
	void setRatio(cpFloat value);
	cpFloat getPhase(void);
	void setPhase(cpFloat value);
	cpFloat getRatio(void);

};
};//namespace cp
