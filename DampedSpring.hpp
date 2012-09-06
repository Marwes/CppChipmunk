#pragma once

#include "chipmunk.h"
#include "Vect.hpp"
#include "Constraint.hpp"

namespace cp {


class DampedSpring : public Constraint{
protected:
	cpDampedSpring*dampedspring;
public:

	cpDampedSpring* get() const
	{
		return dampedspring;
	}

	operator cpDampedSpring*() const
	{
		return dampedspring;
	}

	inline const cpConstraintClass *getClass()
	{
		return cpDampedSpringGetClass();
	}

	inline cp::Vect getAnchr1(void)
	{
		return cpDampedSpringGetAnchr1(constraint);
	}

	inline void setAnchr1(cp::Vect& value)
	{
		cpDampedSpringSetAnchr1(constraint,value);
	}

	inline cp::Vect getAnchr2(void)
	{
		return cpDampedSpringGetAnchr2(constraint);
	}

	inline void setAnchr2(cp::Vect& value)
	{
		cpDampedSpringSetAnchr2(constraint,value);
	}

	inline cpFloat getRestLength(void)
	{
		return cpDampedSpringGetRestLength(constraint);
	}

	inline void setRestLength(cpFloat value)
	{
		cpDampedSpringSetRestLength(constraint,value);
	}

	inline cpFloat getStiffness(void)
	{
		return cpDampedSpringGetStiffness(constraint);
	}

	inline void setStiffness(cpFloat value)
	{
		cpDampedSpringSetStiffness(constraint,value);
	}

	inline cpFloat getDamping(void)
	{
		return cpDampedSpringGetDamping(constraint);
	}

	inline void setDamping(cpFloat value)
	{
		cpDampedSpringSetDamping(constraint,value);
	}

	inline cpDampedSpringForceFunc getSpringForceFunc(void)
	{
		return cpDampedSpringGetSpringForceFunc(constraint);
	}

	inline void setSpringForceFunc(cpDampedSpringForceFunc value)
	{
		cpDampedSpringSetSpringForceFunc(constraint,value);
	}

	DampedSpring(cpBody *a,cpBody *b,cpVect anchr1,cpVect anchr2,cpFloat restLength,cpFloat stiffness,cpFloat damping)
	 : Constraint(cpDampedSpringNew(a,b,anchr1,anchr2,restLength,stiffness,damping))
	{
		constraint->data = this;
	}

};
}//namespace cp
