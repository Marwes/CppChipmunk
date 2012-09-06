#pragma once

#include "chipmunk.h"
#include "Vect.hpp"
#include "Constraint.hpp"

namespace cp {


class SlideJoint : public Constraint{
protected:
	cpSlideJoint*slidejoint;
public:

	cpSlideJoint* get() const
	{
		return slidejoint;
	}

	operator cpSlideJoint*() const
	{
		return slidejoint;
	}

	inline const cpConstraintClass *getClass()
	{
		return cpSlideJointGetClass();
	}

	inline cp::Vect getAnchr1(void)
	{
		return cpSlideJointGetAnchr1(constraint);
	}

	inline void setAnchr1(cp::Vect& value)
	{
		cpSlideJointSetAnchr1(constraint,value);
	}

	inline cp::Vect getAnchr2(void)
	{
		return cpSlideJointGetAnchr2(constraint);
	}

	inline void setAnchr2(cp::Vect& value)
	{
		cpSlideJointSetAnchr2(constraint,value);
	}

	inline cpFloat getMin(void)
	{
		return cpSlideJointGetMin(constraint);
	}

	inline void setMin(cpFloat value)
	{
		cpSlideJointSetMin(constraint,value);
	}

	inline cpFloat getMax(void)
	{
		return cpSlideJointGetMax(constraint);
	}

	inline void setMax(cpFloat value)
	{
		cpSlideJointSetMax(constraint,value);
	}

	SlideJoint(cpBody *a,cpBody *b,cpVect anchr1,cpVect anchr2,cpFloat min,cpFloat max)
	 : Constraint(cpSlideJointNew(a,b,anchr1,anchr2,min,max))
	{
		constraint->data = this;
	}

};
}//namespace cp
