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

class GrooveJoint : public Constraint {
protected:
	cpGrooveJoint* groovejoint;
public:
	cpGrooveJoint* get(){
		return groovejoint;
}
	const cpConstraintClass *getClass();
/// Allocate and initialize a groove joint.
	GrooveJoint(cp::Body *a,cp::Body *b,cpVect groove_a,cpVect groove_b,cpVect anchr2);
/// Set endpoint a of a groove joint's groove
	void setGrooveA(cpVect value);
/// Set endpoint b of a groove joint's groove
	void setGrooveB(cpVect value);
	cp::Vect getGrooveA(void);
	cp::Vect getGrooveB(void);
	cp::Vect getAnchr2(void);
	void setAnchr2(cp::Vect value);

};
};//namespace cp
