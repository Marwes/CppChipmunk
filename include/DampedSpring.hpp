/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 19:02:38.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"

namespace cp {

class DampedSpring : public Constraint {
protected:
	cpDampedSpring* dampedspring;
public:
	cpDampedSpring* get(){
		return dampedspring;
}
	const cpConstraintClass *getClass();
/// Allocate and initialize a damped spring.
	DampedSpring(cp::Body *a,cp::Body *b,cpVect anchr1,cpVect anchr2,cpFloat restLength,cpFloat stiffness,cpFloat damping);
	cp::Vect getAnchr1(void);
	void setAnchr1(cp::Vect value);
	cp::Vect getAnchr2(void);
	void setAnchr2(cp::Vect value);
	cpFloat getRestLength(void);
	void setRestLength(cpFloat value);
	cpFloat getStiffness(void);
	void setStiffness(cpFloat value);
	cpFloat getDamping(void);
	void setDamping(cpFloat value);
	cpDampedSpringForceFunc getSpringForceFunc(void);
	void setSpringForceFunc(cpDampedSpringForceFunc value);

};
};//namespace cp
