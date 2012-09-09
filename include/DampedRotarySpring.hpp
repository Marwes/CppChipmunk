/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:52:11.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

namespace cp {

class DampedRotarySpring : public Constraint {
protected:
	cpDampedRotarySpring* dampedrotaryspring;
public:
	cpDampedRotarySpring* get();
	const cpConstraintClass *getClass();
	DampedRotarySpring(cp::Body *a,cp::Body *b,cpFloat restAngle,cpFloat stiffness,cpFloat damping);
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
