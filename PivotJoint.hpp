#pragma once

#include "chipmunk.h"
#include "Vect.hpp"
#include "Constraint.hpp"

namespace cp {


class PivotJoint : public Constraint{
protected:
	cpPivotJoint*pivotjoint;
public:

	cpPivotJoint* get() const
	{
		return pivotjoint;
	}

	operator cpPivotJoint*() const
	{
		return pivotjoint;
	}

	inline const cpConstraintClass *getClass()
	{
		return cpPivotJointGetClass();
	}

	inline cp::Vect getAnchr1(void)
	{
		return cpPivotJointGetAnchr1(constraint);
	}

	inline void setAnchr1(cp::Vect& value)
	{
		cpPivotJointSetAnchr1(constraint,value);
	}

	inline cp::Vect getAnchr2(void)
	{
		return cpPivotJointGetAnchr2(constraint);
	}

	inline void setAnchr2(cp::Vect& value)
	{
		cpPivotJointSetAnchr2(constraint,value);
	}

	PivotJoint(cpBody *a,cpBody *b,cpVect pivot)
	 : Constraint(cpPivotJointNew(a,b,pivot))
	{
		constraint->data = this;
	}

	PivotJoint(cpBody *a,cpBody *b,cpVect anchr1,cpVect anchr2)
	 : Constraint(cpPivotJointNew2(a,b,anchr1,anchr2))
	{
		constraint->data = this;
	}

};
}//namespace cp
