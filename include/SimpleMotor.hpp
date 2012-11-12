/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 11/12/12 01:02:18.
 */
#pragma once

#include <utility>
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
	SimpleMotor(SimpleMotor&&o);
private:
//Hiding copy constructor and assignmentSimpleMotor(const SimpleMotor&);
SimpleMotor& operator=(const SimpleMotor&);

};
};//namespace cp
