/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Space.hpp"
#include "Body.hpp"

namespace cp {

class Constraint {
protected:
	cpConstraint* constraint;
	cpDataPointer data;
public:
	cpConstraint* get();
	~Constraint();
	void activateBodies();
	cpFloat getImpulse();
	cp::Space* getSpace(void);
	cp::Body* getA(void);
	cp::Body* getB(void);
	cpFloat getMaxForce(void);
	void setMaxForce(cpFloat value);
	cpFloat getErrorBias(void);
	void setErrorBias(cpFloat value);
	cpFloat getMaxBias(void);
	void setMaxBias(cpFloat value);
	cpConstraintPreSolveFunc getPreSolveFunc(void);
	void setPreSolveFunc(cpConstraintPreSolveFunc value);
	cpConstraintPostSolveFunc getPostSolveFunc(void);
	void setPostSolveFunc(cpConstraintPostSolveFunc value);
	cpDataPointer getUserData(void);
	void setUserData(cpDataPointer value);
	Constraint(cpConstraint* v);

};
};//namespace cp
