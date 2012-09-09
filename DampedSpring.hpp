#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

class DampedSpring : public Constraint {
protected:
	cpDampedSpring* dampedspring;
public:
	cpDampedSpring* get();
	const cpConstraintClass *getClass();
	DampedSpring(cp::Body *a,cp::Body *b,cp::Vect anchr1,cp::Vect anchr2,cpFloat restLength,cpFloat stiffness,cpFloat damping);
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