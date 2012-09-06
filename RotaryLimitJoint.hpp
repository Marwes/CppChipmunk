#pragma once

#include "chipmunk.h"
#include "Constraint.hpp"

namespace cp {


class RotaryLimitJoint : public Constraint{
protected:
	cpRotaryLimitJoint*rotarylimitjoint;
public:

	cpRotaryLimitJoint* get() const
	{
		return rotarylimitjoint;
	}

	operator cpRotaryLimitJoint*() const
	{
		return rotarylimitjoint;
	}

	inline const cpConstraintClass *getClass()
	{
		return cpRotaryLimitJointGetClass();
	}

	inline cpFloat getMin(void)
	{
		return cpRotaryLimitJointGetMin(constraint);
	}

	inline void setMin(cpFloat value)
	{
		cpRotaryLimitJointSetMin(constraint,value);
	}

	inline cpFloat getMax(void)
	{
		return cpRotaryLimitJointGetMax(constraint);
	}

	inline void setMax(cpFloat value)
	{
		cpRotaryLimitJointSetMax(constraint,value);
	}

	RotaryLimitJoint(cpBody *a,cpBody *b,cpFloat min,cpFloat max)
	 : Constraint(cpRotaryLimitJointNew(a,b,min,max))
	{
		constraint->data = this;
	}

};
}//namespace cp
