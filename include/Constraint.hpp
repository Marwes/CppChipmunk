/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 20:29:34.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"

namespace cp {

class Constraint {
protected:
	cpConstraint* constraint;
	cpDataPointer data;
public:
	inline cpConstraint* get(){
		return constraint;
}
/// Destroy and free a constraint.
	~Constraint();
/// @private
	void activateBodies();
// Get the last impulse applied by this constraint.
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
