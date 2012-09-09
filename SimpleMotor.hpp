#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

namespace cp {

class SimpleMotor : public Constraint {
protected:
	cpSimpleMotor* simplemotor;
public:
	cpSimpleMotor* get();
	const cpConstraintClass *getClass();
	SimpleMotor(cp::Body *a,cp::Body *b,cpFloat rate);
	cpFloat getRate(void);
	void setRate(cpFloat value);

};
};//namespace cp
