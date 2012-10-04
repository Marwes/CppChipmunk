/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:56:58.
 */
#include "GearJoint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"

namespace cp {

const cpConstraintClass *GearJoint::getClass()
{
		return cpGearJointGetClass();
}
GearJoint::GearJoint(cpBody *a,cpBody *b,cpFloat phase,cpFloat ratio)
	: Constraint(cpGearJointNew(a ? a->get() : 0,b ? b->get() : 0,phase,ratio))
{
		constraint->data = this;
}
void GearJoint::setRatio(cpFloat value)
{
		cpGearJointSetRatio(Constraint::get(),value);
}
cpFloat GearJoint::getPhase(void)
{
		return cpGearJointGetPhase(constraint);
}
void GearJoint::setPhase(cpFloat value)
{
		cpGearJointSetPhase(constraint,value);
}
cpFloat GearJoint::getRatio(void)
{
		return cpGearJointGetRatio(constraint);
}
};//namespace cp
