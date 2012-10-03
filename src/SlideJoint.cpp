/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 19:02:38.
 */
#include "SlideJoint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

const cpConstraintClass *SlideJoint::getClass()
{
		return cpSlideJointGetClass();
}
SlideJoint::SlideJoint(cp::Body *a,cp::Body *b,cpVect anchr1,cpVect anchr2,cpFloat min,cpFloat max)
	: Constraint(cpSlideJointNew(a ? a->get() : 0,b ? b->get() : 0,anchr1,anchr2,min,max))
{
		constraint->data = this;
}
cp::Vect SlideJoint::getAnchr1(void)
{
		return cpSlideJointGetAnchr1(constraint);
}
void SlideJoint::setAnchr1(cp::Vect value)
{
		cpSlideJointSetAnchr1(constraint,value);
}
cp::Vect SlideJoint::getAnchr2(void)
{
		return cpSlideJointGetAnchr2(constraint);
}
void SlideJoint::setAnchr2(cp::Vect value)
{
		cpSlideJointSetAnchr2(constraint,value);
}
cpFloat SlideJoint::getMin(void)
{
		return cpSlideJointGetMin(constraint);
}
void SlideJoint::setMin(cpFloat value)
{
		cpSlideJointSetMin(constraint,value);
}
cpFloat SlideJoint::getMax(void)
{
		return cpSlideJointGetMax(constraint);
}
void SlideJoint::setMax(cpFloat value)
{
		cpSlideJointSetMax(constraint,value);
}
};//namespace cp
