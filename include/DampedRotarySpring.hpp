/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:56:58.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"

namespace cp {

class DampedRotarySpring : public Constraint {
protected:
	cpDampedRotarySpring* dampedrotaryspring;
public:
	cpDampedRotarySpring* get(){
		return dampedrotaryspring;
}
	const cpConstraintClass *getClass();
/// Allocate and initialize a damped rotary spring.
	DampedRotarySpring(cpBody *a,cpBody *b,cpFloat restAngle,cpFloat stiffness,cpFloat damping);
	cpFloat getRestAngle(void);
	void setRestAngle(cpFloat value);
	cpFloat getStiffness(void);
	void setStiffness(cpFloat value);
	cpFloat getDamping(void);
	void setDamping(cpFloat value);
	cpDampedRotarySpringTorqueFunc getSpringTorqueFunc(void);
	void setSpringTorqueFunc(cpDampedRotarySpringTorqueFunc value);

};
};//namespace cp
