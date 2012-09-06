#pragma once

#include "chipmunk.h"
#include "Constraint.hpp"

namespace cp {


class DampedRotarySpring : public Constraint{
protected:
	cpDampedRotarySpring*dampedrotaryspring;
public:

	cpDampedRotarySpring* get() const
	{
		return dampedrotaryspring;
	}

	operator cpDampedRotarySpring*() const
	{
		return dampedrotaryspring;
	}

	inline const cpConstraintClass *getClass()
	{
		return cpDampedRotarySpringGetClass();
	}

	inline cpFloat getRestAngle(void)
	{
		return cpDampedRotarySpringGetRestAngle(constraint);
	}

	inline void setRestAngle(cpFloat value)
	{
		cpDampedRotarySpringSetRestAngle(constraint,value);
	}

	inline cpFloat getStiffness(void)
	{
		return cpDampedRotarySpringGetStiffness(constraint);
	}

	inline void setStiffness(cpFloat value)
	{
		cpDampedRotarySpringSetStiffness(constraint,value);
	}

	inline cpFloat getDamping(void)
	{
		return cpDampedRotarySpringGetDamping(constraint);
	}

	inline void setDamping(cpFloat value)
	{
		cpDampedRotarySpringSetDamping(constraint,value);
	}

	inline cpDampedRotarySpringTorqueFunc getSpringTorqueFunc(void)
	{
		return cpDampedRotarySpringGetSpringTorqueFunc(constraint);
	}

	inline void setSpringTorqueFunc(cpDampedRotarySpringTorqueFunc value)
	{
		cpDampedRotarySpringSetSpringTorqueFunc(constraint,value);
	}

	DampedRotarySpring(cpBody *a,cpBody *b,cpFloat restAngle,cpFloat stiffness,cpFloat damping)
	 : Constraint(cpDampedRotarySpringNew(a,b,restAngle,stiffness,damping))
	{
		constraint->data = this;
	}

};
}//namespace cp
