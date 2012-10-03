/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/19/12 14:10:01.
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
	cpSimpleMotor* get();
	const cpConstraintClass *getClass();
/// Allocate and initialize a simple motor.
	SimpleMotor(cp::Body *a,cp::Body *b,cpFloat rate);
	cpFloat getRate(void);
	void setRate(cpFloat value);

};
};//namespace cp
