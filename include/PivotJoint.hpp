/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 20:29:34.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"

namespace cp {

class PivotJoint : public Constraint {
protected:
	cpPivotJoint* pivotjoint;
public:
	inline cpPivotJoint* get(){
		return pivotjoint;
}
	const cpConstraintClass *getClass();
/// Allocate and initialize a pivot joint.
	PivotJoint(cp::Body *a,cp::Body *b,cp::Vect pivot);
/// Allocate and initialize a pivot joint with specific anchors.
	PivotJoint(cp::Body *a,cp::Body *b,cp::Vect anchr1,cp::Vect anchr2);
	cp::Vect getAnchr1(void);
	void setAnchr1(cp::Vect value);
	cp::Vect getAnchr2(void);
	void setAnchr2(cp::Vect value);

};
};//namespace cp
