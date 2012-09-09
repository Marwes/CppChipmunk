/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:52:11.
 */
#include "RotaryLimitJoint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

namespace cp {

cpRotaryLimitJoint* RotaryLimitJoint::get()
{
		return rotarylimitjoint;
}
const cpConstraintClass *RotaryLimitJoint::getClass()
{
		return cpRotaryLimitJointGetClass();
}
RotaryLimitJoint::RotaryLimitJoint(cp::Body *a,cp::Body *b,cpFloat min,cpFloat max)
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
