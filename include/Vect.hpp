/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
 */
#pragma once

#include "chipmunk.h"
#include "Vect.hpp"

namespace cp {

class Vect : public cpVect {
protected:
public:
	Vect(cpVect cv);
	Vect(const cpFloat x,const cpFloat y);
	cp::Vect slerp(Vect& v2,const cpFloat t);
	cp::Vect slerpconst(Vect& v2,const cpFloat a);
	char* str();
	cpBool eql(Vect& v2);
	cp::Vect add(Vect& v2);
	cp::Vect sub(Vect& v2);
	cp::Vect neg();
	cp::Vect mult(const cpFloat s);
	cpFloat dot(Vect& v2);
	cpFloat cross(Vect& v2);
	cp::Vect perp();
	cp::Vect rperp();
	cp::Vect project(Vect& v2);
	cp::Vect forangle(const cpFloat a);
	cpFloat toangle();
	cp::Vect rotate(Vect& v2);
	cp::Vect unrotate(Vect& v2);
	cpFloat lengthsq();
	cpFloat length();
	cp::Vect lerp(Vect& v2,const cpFloat t);
	cp::Vect normalize();
	cp::Vect normalize_safe();
	cp::Vect clamp(const cpFloat len);
	cp::Vect lerpconst(Vect& v2,cpFloat d);
	cpFloat dist(Vect& v2);
	cpFloat distsq(Vect& v2);
	cpBool near(Vect& v2,const cpFloat dist);

};
};//namespace cp
