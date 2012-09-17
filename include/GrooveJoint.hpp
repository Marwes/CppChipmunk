/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/15/12 09:55:02.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"

namespace cp {

class GrooveJoint : public Constraint {
protected:
	cpGrooveJoint* groovejoint;
public:
	cpGrooveJoint* get();
	const cpConstraintClass *getClass();
/// Allocate and initialize a groove joint.
	GrooveJoint(cp::Body *a,cp::Body *b,cp::Vect groove_a,cp::Vect groove_b,cp::Vect anchr2);
/// Set endpoint a of a groove joint's groove
	void setGrooveA(cp::Vect value);
/// Set endpoint b of a groove joint's groove
	void setGrooveB(cp::Vect value);
	cp::Vect getGrooveA(void);
	cp::Vect getGrooveB(void);
	cp::Vect getAnchr2(void);
	void setAnchr2(cp::Vect value);

};
};//namespace cp
