/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

namespace cp {

class RotaryLimitJoint : public Constraint {
protected:
	cpRotaryLimitJoint* rotarylimitjoint;
public:
	cpRotaryLimitJoint* get();
	const cpConstraintClass *getClass();
	RotaryLimitJoint(cp::Body *a,cp::Body *b,cpFloat min,cpFloat max);
	cpFloat getMin(void);
	void setMin(cpFloat value);
	cpFloat getMax(void);
	void setMax(cpFloat value);

};
};//namespace cp
