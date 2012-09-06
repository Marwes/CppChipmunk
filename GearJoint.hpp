#pragma once

#include "chipmunk.h"
#include "Constraint.hpp"

namespace cp {


class GearJoint : public Constraint{
protected:
	cpGearJoint*gearjoint;
public:

	cpGearJoint* get() const
	{
		return gearjoint;
	}

	operator cpGearJoint*() const
	{
		return gearjoint;
	}

	inline const cpConstraintClass *getClass()
	{
		return cpGearJointGetClass();
	}

	inline void setRatio(cpFloat value)
	{
		cpGearJointSetRatio(constraint,value);
	}

	inline cpFloat getPhase(void)
	{
		return cpGearJointGetPhase(constraint);
	}

	inline void setPhase(cpFloat value)
	{
		cpGearJointSetPhase(constraint,value);
	}

	inline cpFloat getRatio(void)
	{
		return cpGearJointGetRatio(constraint);
	}

	GearJoint(cpBody *a,cpBody *b,cpFloat phase,cpFloat ratio)
	 : Constraint(cpGearJointNew(a,b,phase,ratio))
	{
		constraint->data = this;
	}

};
}//namespace cp
