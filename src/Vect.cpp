/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/15/12 09:55:02.
 */
#include "Vect.hpp"
#include "chipmunk.h"
#include "Vect.hpp"

namespace cp {

Vect::Vect(cpVect cv)
{
		this->x = cv.x; this->y = cv.y;
}
Vect::Vect(const cpFloat x,const cpFloat y)
{
		this->x = x; this->y = y;
}
cp::Vect Vect::slerp(Vect& v2,const cpFloat t)
{
		return cpvslerp(*this,v2,t);
}
cp::Vect Vect::slerpconst(Vect& v2,const cpFloat a)
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
cp::Vect Vect::add(Vect& v2)
{
		return cpvadd(*this,v2);
}
cp::Vect Vect::sub(Vect& v2)
{
		return cpvsub(*this,v2);
}
cp::Vect Vect::neg()
{
		return cpvneg(*this);
}
cp::Vect Vect::mult(const cpFloat s)
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
cp::Vect Vect::perp()
{
		return cpvperp(*this);
}
cp::Vect Vect::rperp()
{
		return cpvrperp(*this);
}
cp::Vect Vect::project(Vect& v2)
{
		return cpvproject(*this,v2);
}
cp::Vect Vect::forangle(const cpFloat a)
{
		return cpvforangle(a);
}
cpFloat Vect::toangle()
{
		return cpvtoangle(*this);
}
cp::Vect Vect::rotate(Vect& v2)
{
		return cpvrotate(*this,v2);
}
cp::Vect Vect::unrotate(Vect& v2)
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
cp::Vect Vect::lerp(Vect& v2,const cpFloat t)
{
		return cpvlerp(*this,v2,t);
}
cp::Vect Vect::normalize()
{
		return cpvnormalize(*this);
}
cp::Vect Vect::normalize_safe()
{
		return cpvnormalize_safe(*this);
}
cp::Vect Vect::clamp(const cpFloat len)
{
		return cpvclamp(*this,len);
}
cp::Vect Vect::lerpconst(Vect& v2,cpFloat d)
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
