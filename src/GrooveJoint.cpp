/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:56:58.
 */
#include "GrooveJoint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Vect.hpp"

namespace cp {

const cpConstraintClass *GrooveJoint::getClass()
{
		return cpGrooveJointGetClass();
}
GrooveJoint::GrooveJoint(cpBody *a,cpBody *b,cpVect groove_a,cpVect groove_b,cpVect anchr2)
	: Constraint(cpGrooveJointNew(a ? a->get() : 0,b ? b->get() : 0,groove_a,groove_b,anchr2))
{
		constraint->data = this;
}
void GrooveJoint::setGrooveA(cpVect value)
{
		cpGrooveJointSetGrooveA(Constraint::get(),value);
}
void GrooveJoint::setGrooveB(cpVect value)
{
		cpGrooveJointSetGrooveB(Constraint::get(),value);
}
cp::Vect GrooveJoint::getGrooveA(void)
{
		return cpGrooveJointGetGrooveA(constraint);
}
cp::Vect GrooveJoint::getGrooveB(void)
{
		return cpGrooveJointGetGrooveB(constraint);
}
cp::Vect GrooveJoint::getAnchr2(void)
{
		return cpGrooveJointGetAnchr2(constraint);
}
void GrooveJoint::setAnchr2(cp::Vect value)
{
		cpGrooveJointSetAnchr2(constraint,value);
}
};//namespace cp
