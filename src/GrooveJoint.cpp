/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
 */
#include "GrooveJoint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

cpGrooveJoint* GrooveJoint::get()
{
		return groovejoint;
}
const cpConstraintClass *GrooveJoint::getClass()
{
		return cpGrooveJointGetClass();
}
GrooveJoint::GrooveJoint(cp::Body *a,cp::Body *b,cp::Vect groove_a,cp::Vect groove_b,cp::Vect anchr2)
	: Constraint(cpGrooveJointNew(a ? a->get() : 0,b ? b->get() : 0,groove_a,groove_b,anchr2))
{
		constraint->data = this;
}
void GrooveJoint::setGrooveA(cp::Vect value)
{
		cpGrooveJointSetGrooveA(Constraint::get(),value);
}
void GrooveJoint::setGrooveB(cp::Vect value)
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
