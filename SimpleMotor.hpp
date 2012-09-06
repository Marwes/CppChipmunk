#pragma once

#include "chipmunk.h"
#include "Constraint.hpp"

namespace cp {


class SimpleMotor : public Constraint{
protected:
	cpSimpleMotor*simplemotor;
public:

	cpSimpleMotor* get() const
	{
		return simplemotor;
	}

	operator cpSimpleMotor*() const
	{
		return simplemotor;
	}

	inline const cpConstraintClass *getClass()
	{
		return cpSimpleMotorGetClass();
	}

	inline cpFloat getRate(void)
	{
		return cpSimpleMotorGetRate(constraint);
	}

	inline void setRate(cpFloat value)
	{
		cpSimpleMotorSetRate(constraint,value);
	}

	SimpleMotor(cpBody *a,cpBody *b,cpFloat rate)
	 : Constraint(cpSimpleMotorNew(a,b,rate))
	{
		constraint->data = this;
	}

};
}//namespace cp
