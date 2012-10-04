/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:40:05.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"

namespace cp {

class Arbiter {
protected:
	cpArbiter* arb;
public:
	cpArbiter* get(){
		return arb;
}
/// Calculate the total impulse that was applied by this arbiter.
/// This function should only be called from a post-solve, post-step or cpBodyEachArbiter callback.
	cpVect totalImpulse();
/// Calculate the total impulse including the friction that was applied by this arbiter.
/// This function should only be called from a post-solve, post-step or cpBodyEachArbiter callback.
	cpVect totalImpulseWithFriction();
/// Calculate the amount of energy lost in a collision including static, but not dynamic friction.
/// This function should only be called from a post-solve, post-step or cpBodyEachArbiter callback.
	cpFloat totalKE();
/// Causes a collision pair to be ignored as if you returned false from a begin callback.
/// If called from a pre-step callback, you will still need to return false
/// if you want it to be ignored in the current step.
	void ignore();
/// Return the colliding shapes involved for this arbiter.
/// The order of their cpSpace.collision_type values will match
/// the order set when the collision handler was registered.
	void getShapes(cpShape *&a,cpShape *&b);
/// A macro shortcut for defining and retrieving the shapes from an arbiter.
/// Return the colliding bodies involved for this arbiter.
/// The order of the cpSpace.collision_type the bodies are associated with values will match
/// the order set when the collision handler was registered.
	void getBodies(cpBody *&a,cpBody *&b);
/// Return a contact set from an arbiter.
	cpContactPointSet getContactPointSet();
/// Returns true if this is the first step a pair of objects started colliding.
	cpBool isFirstContact();
/// Get the number of contact points for this arbiter.
	int getCount();
/// Get the normal of the @c ith contact point.
	cpVect getNormal(int i);
/// Get the position of the @c ith contact point.
	cpVect getPoint(int i);
/// Get the depth of the @c ith contact point.
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
