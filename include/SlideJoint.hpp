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

class SlideJoint : public Constraint {
protected:
	cpSlideJoint* slidejoint;
public:
	cpSlideJoint* get(){
		return slidejoint;
}
	const cpConstraintClass *getClass();
/// Allocate and initialize a slide joint.
	SlideJoint(cp::Body *a,cp::Body *b,cpVect anchr1,cpVect anchr2,cpFloat min,cpFloat max);
	cp::Vect getAnchr1(void);
	void setAnchr1(cp::Vect value);
	cp::Vect getAnchr2(void);
	void setAnchr2(cp::Vect value);
	cpFloat getMin(void);
	void setMin(cpFloat value);
	cpFloat getMax(void);
	void setMax(cpFloat value);

};
};//namespace cp
