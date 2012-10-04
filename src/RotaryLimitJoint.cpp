/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:56:58.
 */
#include "RotaryLimitJoint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"

namespace cp {

const cpConstraintClass *RotaryLimitJoint::getClass()
{
		return cpRotaryLimitJointGetClass();
}
RotaryLimitJoint::RotaryLimitJoint(cpBody *a,cpBody *b,cpFloat min,cpFloat max)
	: Constraint(cpRotaryLimitJointNew(a ? a->get() : 0,b ? b->get() : 0,min,max))
{
		constraint->data = this;
}
cpFloat RotaryLimitJoint::getMin(void)
{
		return cpRotaryLimitJointGetMin(constraint);
}
void RotaryLimitJoint::setMin(cpFloat value)
{
		cpRotaryLimitJointSetMin(constraint,value);
}
cpFloat RotaryLimitJoint::getMax(void)
{
		return cpRotaryLimitJointGetMax(constraint);
}
void RotaryLimitJoint::setMax(cpFloat value)
{
		cpRotaryLimitJointSetMax(constraint,value);
}
};//namespace cp
