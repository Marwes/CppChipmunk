/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:52:11.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Vect.hpp"
#include "Shape.hpp"
#include "Body.hpp"

namespace cp {

class Arbiter {
protected:
	cpArbiter* arb;
public:
	cpArbiter* get();
	cp::Vect totalImpulse();
	cp::Vect totalImpulseWithFriction();
	cpFloat totalKE();
	void ignore();
	void getShapes(cp::Shape *&a,cp::Shape *&b);
	void getBodies(cp::Body *&a,cp::Body *&b);
	cpContactPointSet getContactPointSet();
	cpBool isFirstContact();
	int getCount();
	cp::Vect getNormal(int i);
	cp::Vect getPoint(int i);
	cpFloat getDepth(int i);
	cpFloat getElasticity(void);
	void setElasticity(cpFloat value);
	cpFloat getFriction(void);
	void setFriction(cpFloat value);
	cp::Vect getSurfaceVelocity(void);
	void setSurfaceVelocity(cp::Vect value);
	Arbiter(cpArbiter* v);

};
};//namespace cp
