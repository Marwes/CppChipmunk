#pragma once

#include "chipmunk.h"
#include "Vect.hpp"
#include "Constraint.hpp"

namespace cp {


class PinJoint : public Constraint{
protected:
	cpPinJoint*pinjoint;
public:

	cpPinJoint* get() const
	{
		return pinjoint;
	}

	operator cpPinJoint*() const
	{
		return pinjoint;
	}

	inline const cpConstraintClass *getClass()
	{
		return cpPinJointGetClass();
	}

	inline cp::Vect getAnchr1(void)
	{
		return cpPinJointGetAnchr1(constraint);
	}

	inline void setAnchr1(cp::Vect& value)
	{
		cpPinJointSetAnchr1(constraint,value);
	}

	inline cp::Vect getAnchr2(void)
	{
		return cpPinJointGetAnchr2(constraint);
	}

	inline void setAnchr2(cp::Vect& value)
	{
		cpPinJointSetAnchr2(constraint,value);
	}

	inline cpFloat getDist(void)
	{
		return cpPinJointGetDist(constraint);
	}

	inline void setDist(cpFloat value)
	{
		cpPinJointSetDist(constraint,value);
	}

	PinJoint(cpBody *a,cpBody *b,cpVect anchr1,cpVect anchr2)
	 : Constraint(cpPinJointNew(a,b,anchr1,anchr2))
	{
		constraint->data = this;
	}

};
}//namespace cp
