/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/15/12 09:00:46.
 */
#include "PivotJoint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

cpPivotJoint* PivotJoint::get()
{
		return pivotjoint;
}
const cpConstraintClass *PivotJoint::getClass()
{
		return cpPivotJointGetClass();
}
PivotJoint::PivotJoint(cp::Body *a,cp::Body *b,cp::Vect pivot)
	: Constraint(cpPivotJointNew(a ? a->get() : 0,b ? b->get() : 0,pivot))
{
		constraint->data = this;
}
PivotJoint::PivotJoint(cp::Body *a,cp::Body *b,cp::Vect anchr1,cp::Vect anchr2)
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
