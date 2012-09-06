#pragma once

#include "chipmunk.h"
#include "Vect.hpp"

namespace cp {


class Arbiter{
protected:
	cpArbiter*arb;
public:

	cpArbiter* get() const
	{
		return arb;
	}

	operator cpArbiter*() const
	{
		return arb;
	}

	inline cpVect totalImpulse()
	{
		return cpArbiterTotalImpulse(arb);
	}

	inline cpVect totalImpulseWithFriction()
	{
		return cpArbiterTotalImpulseWithFriction(arb);
	}

	inline cpFloat totalKE()
	{
		return cpArbiterTotalKE(arb);
	}

	inline void ignore()
	{
		cpArbiterIgnore(arb);
	}

	inline void getShapes(cpShape **a,cpShape **b)
	{
		cpArbiterGetShapes(arb,a,b);
	}

	inline void getBodies(cpBody **a,cpBody **b)
	{
		cpArbiterGetBodies(arb,a,b);
	}

	inline cpContactPointSet getContactPointSet()
	{
		return cpArbiterGetContactPointSet(arb);
	}

	inline cpBool isFirstContact()
	{
		return cpArbiterIsFirstContact(arb);
	}

	inline int getCount()
	{
		return cpArbiterGetCount(arb);
	}

	inline cpVect getNormal(int i)
	{
		return cpArbiterGetNormal(arb,i);
	}

	inline cpVect getPoint(int i)
	{
		return cpArbiterGetPoint(arb,i);
	}

	inline cpFloat getDepth(int i)
	{
		return cpArbiterGetDepth(arb,i);
	}

	inline cpFloat getElasticity(void)
	{
		return cpArbiterGetElasticity(arb);
	}

	inline void setElasticity(cpFloat value)
	{
		cpArbiterSetElasticity(arb,value);
	}

	inline cpFloat getFriction(void)
	{
		return cpArbiterGetFriction(arb);
	}

	inline void setFriction(cpFloat value)
	{
		cpArbiterSetFriction(arb,value);
	}

	inline cp::Vect getSurfaceVelocity(void)
	{
		return cpArbiterGetSurfaceVelocity(arb);
	}

	inline void setSurfaceVelocity(cp::Vect& value)
	{
		cpArbiterSetSurfaceVelocity(arb,value);
	}

	Arbiter(cpArbiter* v)
	{
		arb = v;
	}

};
}//namespace cp
