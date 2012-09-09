/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
 */
#include "RatchetJoint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

namespace cp {

cpRatchetJoint* RatchetJoint::get()
{
		return ratchetjoint;
}
const cpConstraintClass *RatchetJoint::getClass()
{
		return cpRatchetJointGetClass();
}
RatchetJoint::RatchetJoint(cp::Body *a,cp::Body *b,cpFloat phase,cpFloat ratchet)
	: Constraint(cpRatchetJointNew(a ? a->get() : 0,b ? b->get() : 0,phase,ratchet))
{
		constraint->data = this;
}
cpFloat RatchetJoint::getAngle(void)
{
		return cpRatchetJointGetAngle(constraint);
}
void RatchetJoint::setAngle(cpFloat value)
{
		cpRatchetJointSetAngle(constraint,value);
}
cpFloat RatchetJoint::getPhase(void)
{
		return cpRatchetJointGetPhase(constraint);
}
void RatchetJoint::setPhase(cpFloat value)
{
		cpRatchetJointSetPhase(constraint,value);
}
cpFloat RatchetJoint::getRatchet(void)
{
		return cpRatchetJointGetRatchet(constraint);
}
void RatchetJoint::setRatchet(cpFloat value)
{
		cpRatchetJointSetRatchet(constraint,value);
}
};//namespace cp
