#pragma once

#include "chipmunk.h"
#include "Space.hpp"
#include "Body.hpp"

namespace cp {


class Constraint{
protected:
	cpConstraint*constraint;
private:
	cpDataPointer data;
public:

	cpConstraint* get() const
	{
		return constraint;
	}

	operator cpConstraint*() const
	{
		return constraint;
	}

	~Constraint()
	{
		cpConstraintFree(constraint);
	}

	inline void activateBodies()
	{
		cpConstraintActivateBodies(constraint);
	}

	inline cpFloat getImpulse()
	{
		return cpConstraintGetImpulse(constraint);
	}

	inline cp::Space* getSpace(void)
	{
		return static_cast<cp::Space*>(cpConstraintGetSpace(constraint) ? cpConstraintGetSpace(constraint)->data : 0);
	}

	inline cp::Body* getA(void)
	{
		return static_cast<cp::Body*>(cpConstraintGetA(constraint) ? cpConstraintGetA(constraint)->data : 0);
	}

	inline cp::Body* getB(void)
	{
		return static_cast<cp::Body*>(cpConstraintGetB(constraint) ? cpConstraintGetB(constraint)->data : 0);
	}

	inline cpFloat getMaxForce(void)
	{
		return cpConstraintGetMaxForce(constraint);
	}

	inline void setMaxForce(cpFloat value)
	{
		cpConstraintSetMaxForce(constraint,value);
	}

	inline cpFloat getErrorBias(void)
	{
		return cpConstraintGetErrorBias(constraint);
	}

	inline void setErrorBias(cpFloat value)
	{
		cpConstraintSetErrorBias(constraint,value);
	}

	inline cpFloat getMaxBias(void)
	{
		return cpConstraintGetMaxBias(constraint);
	}

	inline void setMaxBias(cpFloat value)
	{
		cpConstraintSetMaxBias(constraint,value);
	}

	inline cpConstraintPreSolveFunc getPreSolveFunc(void)
	{
		return cpConstraintGetPreSolveFunc(constraint);
	}

	inline void setPreSolveFunc(cpConstraintPreSolveFunc value)
	{
		cpConstraintSetPreSolveFunc(constraint,value);
	}

	inline cpConstraintPostSolveFunc getPostSolveFunc(void)
	{
		return cpConstraintGetPostSolveFunc(constraint);
	}

	inline void setPostSolveFunc(cpConstraintPostSolveFunc value)
	{
		cpConstraintSetPostSolveFunc(constraint,value);
	}

	inline cpDataPointer getUserData(void)
	{
		return data;
	}

	inline void setUserData(cpDataPointer value)
	{
		data = value;
	}

	Constraint(cpConstraint* v)
	{
		constraint = v;
		data = v->data;
		v->data = this;
	}

};
}//namespace cp
