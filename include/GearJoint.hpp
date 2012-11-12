/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 11/12/12 01:02:18.
 */
#pragma once

#include <utility>
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"

namespace cp {

class GearJoint : public Constraint {
protected:
	cpGearJoint* gearjoint;
public:
	inline cpGearJoint* get(){
		return gearjoint;
}
	const cpConstraintClass *getClass();
/// Allocate and initialize a gear joint.
	GearJoint(cp::Body *a,cp::Body *b,cpFloat phase,cpFloat ratio);
/// Set the ratio of a gear joint.
	void setRatio(cpFloat value);
	cpFloat getPhase(void);
	void setPhase(cpFloat value);
	cpFloat getRatio(void);
	GearJoint(GearJoint&&o);
private:
//Hiding copy constructor and assignmentGearJoint(const GearJoint&);
GearJoint& operator=(const GearJoint&);

};
};//namespace cp
