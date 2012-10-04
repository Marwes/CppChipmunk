/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:40:05.
 */
#include "Vect.hpp"
#include "chipmunk.h"

namespace cp {

Vect::Vect(cpVect cv)
{
		this->x = cv.x; this->y = cv.y;
}
Vect::Vect(const cpFloat x,const cpFloat y)
{
		this->x = x; this->y = y;
}
cpVect Vect::slerp(Vect& v2,const cpFloat t)
{
		return cpvslerp(*this,v2,t);
}
cpVect Vect::slerpconst(Vect& v2,const cpFloat a)
{
		return cpvslerpconst(*this,v2,a);
}
char* Vect::str()
{
		return cpvstr(*this);
}
cpBool Vect::eql(Vect& v2)
{
		return cpveql(*this,v2);
}
cpVect Vect::add(Vect& v2)
{
		return cpvadd(*this,v2);
}
cpVect Vect::sub(Vect& v2)
{
		return cpvsub(*this,v2);
}
cpVect Vect::neg()
{
		return cpvneg(*this);
}
cpVect Vect::mult(const cpFloat s)
{
		return cpvmult(*this,s);
}
cpFloat Vect::dot(Vect& v2)
{
		return cpvdot(*this,v2);
}
cpFloat Vect::cross(Vect& v2)
{
		return cpvcross(*this,v2);
}
cpVect Vect::perp()
{
		return cpvperp(*this);
}
cpVect Vect::rperp()
{
		return cpvrperp(*this);
}
cpVect Vect::project(Vect& v2)
{
		return cpvproject(*this,v2);
}
cpVect Vect::forangle(const cpFloat a)
{
		return cpvforangle(a);
}
cpFloat Vect::toangle()
{
		return cpvtoangle(*this);
}
cpVect Vect::rotate(Vect& v2)
{
		return cpvrotate(*this,v2);
}
cpVect Vect::unrotate(Vect& v2)
{
		return cpvunrotate(*this,v2);
}
cpFloat Vect::lengthsq()
{
		return cpvlengthsq(*this);
}
cpFloat Vect::length()
{
		return cpvlength(*this);
}
cpVect Vect::lerp(Vect& v2,const cpFloat t)
{
		return cpvlerp(*this,v2,t);
}
cpVect Vect::normalize()
{
		return cpvnormalize(*this);
}
cpVect Vect::normalize_safe()
{
		return cpvnormalize_safe(*this);
}
cpVect Vect::clamp(const cpFloat len)
{
		return cpvclamp(*this,len);
}
cpVect Vect::lerpconst(Vect& v2,cpFloat d)
{
		return cpvlerpconst(*this,v2,d);
}
cpFloat Vect::dist(Vect& v2)
{
		return cpvdist(*this,v2);
}
cpFloat Vect::distsq(Vect& v2)
{
		return cpvdistsq(*this,v2);
}
cpBool Vect::near(Vect& v2,const cpFloat dist)
{
		return cpvnear(*this,v2,dist);
}
};//namespace cp
