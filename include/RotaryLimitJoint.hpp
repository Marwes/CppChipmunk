/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/19/12 14:10:01.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"

namespace cp {

class RotaryLimitJoint : public Constraint {
protected:
	cpRotaryLimitJoint* rotarylimitjoint;
public:
	cpRotaryLimitJoint* get();
	const cpConstraintClass *getClass();
/// Allocate and initialize a damped rotary limit joint.
	RotaryLimitJoint(cp::Body *a,cp::Body *b,cpFloat min,cpFloat max);
	cpFloat getMin(void);
	void setMin(cpFloat value);
	cpFloat getMax(void);
	void setMax(cpFloat value);

};
};//namespace cp
