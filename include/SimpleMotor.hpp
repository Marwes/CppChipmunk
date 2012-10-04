/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 20:29:34.
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
	inline cpSimpleMotor* get(){
		return simplemotor;
}
	const cpConstraintClass *getClass();
/// Allocate and initialize a simple motor.
	SimpleMotor(cp::Body *a,cp::Body *b,cpFloat rate);
	cpFloat getRate(void);
	void setRate(cpFloat value);

};
};//namespace cp
