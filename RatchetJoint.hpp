#pragma once

#include "chipmunk.h"
#include "Constraint.hpp"

namespace cp {


class RatchetJoint : public Constraint{
protected:
	cpRatchetJoint*ratchetjoint;
public:

	cpRatchetJoint* get() const
	{
		return ratchetjoint;
	}

	operator cpRatchetJoint*() const
	{
		return ratchetjoint;
	}

	inline const cpConstraintClass *getClass()
	{
		return cpRatchetJointGetClass();
	}

	inline cpFloat getAngle(void)
	{
		return cpRatchetJointGetAngle(constraint);
	}

	inline void setAngle(cpFloat value)
	{
		cpRatchetJointSetAngle(constraint,value);
	}

	inline cpFloat getPhase(void)
	{
		return cpRatchetJointGetPhase(constraint);
	}

	inline void setPhase(cpFloat value)
	{
		cpRatchetJointSetPhase(constraint,value);
	}

	inline cpFloat getRatchet(void)
	{
		return cpRatchetJointGetRatchet(constraint);
	}

	inline void setRatchet(cpFloat value)
	{
		cpRatchetJointSetRatchet(constraint,value);
	}

	RatchetJoint(cpBody *a,cpBody *b,cpFloat phase,cpFloat ratchet)
	 : Constraint(cpRatchetJointNew(a,b,phase,ratchet))
	{
		constraint->data = this;
	}

};
}//namespace cp
