#include "PinJoint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

cpPinJoint* PinJoint::get()
{
		return pinjoint;
}
const cpConstraintClass *PinJoint::getClass()
{
		return cpPinJointGetClass();
}
PinJoint::PinJoint(cp::Body *a,cp::Body *b,cp::Vect anchr1,cp::Vect anchr2)
	: Constraint(cpPinJointNew(a ? a->get() : 0,b ? b->get() : 0,anchr1,anchr2))
{
		constraint->data = this;
}
cp::Vect PinJoint::getAnchr1(void)
{
		return cpPinJointGetAnchr1(constraint);
}
void PinJoint::setAnchr1(cp::Vect value)
{
		cpPinJointSetAnchr1(constraint,value);
}
cp::Vect PinJoint::getAnchr2(void)
{
		return cpPinJointGetAnchr2(constraint);
}
void PinJoint::setAnchr2(cp::Vect value)
{
		cpPinJointSetAnchr2(constraint,value);
}
cpFloat PinJoint::getDist(void)
{
		return cpPinJointGetDist(constraint);
}
void PinJoint::setDist(cpFloat value)
{
		cpPinJointSetDist(constraint,value);
}
};//namespace cp
