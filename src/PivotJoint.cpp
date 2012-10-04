/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:56:58.
 */
#include "PivotJoint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Vect.hpp"

namespace cp {

const cpConstraintClass *PivotJoint::getClass()
{
		return cpPivotJointGetClass();
}
PivotJoint::PivotJoint(cpBody *a,cpBody *b,cpVect pivot)
	: Constraint(cpPivotJointNew(a ? a->get() : 0,b ? b->get() : 0,pivot))
{
		constraint->data = this;
}
PivotJoint::PivotJoint(cpBody *a,cpBody *b,cpVect anchr1,cpVect anchr2)
	: Constraint(cpPivotJointNew2(a ? a->get() : 0,b ? b->get() : 0,anchr1,anchr2))
{
		constraint->data = this;
}
cp::Vect PivotJoint::getAnchr1(void)
{
		return cpPivotJointGetAnchr1(constraint);
}
void PivotJoint::setAnchr1(cp::Vect value)
{
		cpPivotJointSetAnchr1(constraint,value);
}
cp::Vect PivotJoint::getAnchr2(void)
{
		return cpPivotJointGetAnchr2(constraint);
}
void PivotJoint::setAnchr2(cp::Vect value)
{
		cpPivotJointSetAnchr2(constraint,value);
}
};//namespace cp
