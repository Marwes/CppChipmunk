/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:56:58.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"

namespace cp {

class SimpleMotor : public Constraint {
protected:
	cpSimpleMotor* simplemotor;
public:
	cpSimpleMotor* get(){
		return simplemotor;
}
	const cpConstraintClass *getClass();
/// Allocate and initialize a simple motor.
	SimpleMotor(cpBody *a,cpBody *b,cpFloat rate);
	cpFloat getRate(void);
	void setRate(cpFloat value);

};
};//namespace cp
