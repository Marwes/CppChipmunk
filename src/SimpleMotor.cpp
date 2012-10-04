/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:56:58.
 */
#include "SimpleMotor.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"

namespace cp {

const cpConstraintClass *SimpleMotor::getClass()
{
		return cpSimpleMotorGetClass();
}
SimpleMotor::SimpleMotor(cpBody *a,cpBody *b,cpFloat rate)
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
