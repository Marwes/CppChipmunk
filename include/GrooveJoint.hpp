/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:52:11.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Vect.hpp"
#include "Body.hpp"

namespace cp {

class GrooveJoint : public Constraint {
protected:
	cpGrooveJoint* groovejoint;
public:
	cpGrooveJoint* get();
	const cpConstraintClass *getClass();
	GrooveJoint(cp::Body *a,cp::Body *b,cp::Vect groove_a,cp::Vect groove_b,cp::Vect anchr2);
	void setGrooveA(cp::Vect value);
	void setGrooveB(cp::Vect value);
	cp::Vect getGrooveA(void);
	cp::Vect getGrooveB(void);
	cp::Vect getAnchr2(void);
	void setAnchr2(cp::Vect value);

};
};//namespace cp
