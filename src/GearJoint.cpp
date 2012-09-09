/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
 */
#include "GearJoint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

namespace cp {

cpGearJoint* GearJoint::get()
{
		return gearjoint;
}
const cpConstraintClass *GearJoint::getClass()
{
		return cpGearJointGetClass();
}
GearJoint::GearJoint(cp::Body *a,cp::Body *b,cpFloat phase,cpFloat ratio)
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
