/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:52:11.
 */
#include "SimpleMotor.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

namespace cp {

cpSimpleMotor* SimpleMotor::get()
{
		return simplemotor;
}
const cpConstraintClass *SimpleMotor::getClass()
{
		return cpSimpleMotorGetClass();
}
SimpleMotor::SimpleMotor(cp::Body *a,cp::Body *b,cpFloat rate)
	: Constraint(cpSimpleMotorNew(a ? a->get() : 0,b ? b->get() : 0,rate))
{
		constraint->data = this;
}
cpFloat SimpleMotor::getRate(void)
{
		return cpSimpleMotorGetRate(constraint);
}
void SimpleMotor::setRate(cpFloat value)
{
		cpSimpleMotorSetRate(constraint,value);
}
};//namespace cp