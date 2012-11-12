/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 11/12/12 01:17:41.
 */
#include "PinJoint.hpp"
#include <utility>
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

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
PinJoint::PinJoint(PinJoint&&o)
	: pinjoint(o.pinjoint),
	  Constraint(std::move(o))
{
				o.pinjoint = 0;
}
};//namespace cp
