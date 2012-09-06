#pragma once

#include "chipmunk.h"
#include "Vect.hpp"
#include "Constraint.hpp"

namespace cp {


class GrooveJoint : public Constraint{
protected:
	cpGrooveJoint*groovejoint;
public:

	cpGrooveJoint* get() const
	{
		return groovejoint;
	}

	operator cpGrooveJoint*() const
	{
		return groovejoint;
	}

	inline const cpConstraintClass *getClass()
	{
		return cpGrooveJointGetClass();
	}

	inline void setGrooveA(cpVect value)
	{
		cpGrooveJointSetGrooveA(constraint,value);
	}

	inline void setGrooveB(cpVect value)
	{
		cpGrooveJointSetGrooveB(constraint,value);
	}

	inline cp::Vect getGrooveA(void)
	{
		return cpGrooveJointGetGrooveA(constraint);
	}

	inline cp::Vect getGrooveB(void)
	{
		return cpGrooveJointGetGrooveB(constraint);
	}

	inline cp::Vect getAnchr2(void)
	{
		return cpGrooveJointGetAnchr2(constraint);
	}

	inline void setAnchr2(cp::Vect& value)
	{
		cpGrooveJointSetAnchr2(constraint,value);
	}

	GrooveJoint(cpBody *a,cpBody *b,cpVect groove_a,cpVect groove_b,cpVect anchr2)
	 : Constraint(cpGrooveJointNew(a,b,groove_a,groove_b,anchr2))
	{
		constraint->data = this;
	}

};
}//namespace cp
