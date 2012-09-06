#pragma once

#include "chipmunk.h"

namespace cp {


class Vect : public cpVect{
public:

	inline cp::Vect slerp(Vect& v2,const cpFloat t)
	{
		return cpvslerp(*this,v2,t);
	}

	inline cp::Vect slerpconst(Vect& v2,const cpFloat a)
	{
		return cpvslerpconst(*this,v2,a);
	}

	inline char* str()
	{
		return cpvstr(*this);
	}

	inline cpBool operator==(Vect& v2)
	{
		return cpveql(*this,v2);
	}

	inline cp::Vect operator+(Vect& v2)
	{
		return cpvadd(*this,v2);
	}

	inline cp::Vect operator-(Vect& v2)
	{
		return cpvsub(*this,v2);
	}

	inline cp::Vect operator-()
	{
		return cpvneg(*this);
	}

	inline cp::Vect operator*(const cpFloat s)
	{
		return cpvmult(*this,s);
	}

	inline cpFloat dot(Vect& v2)
	{
		return cpvdot(*this,v2);
	}

	inline cpFloat cross(Vect& v2)
	{
		return cpvcross(*this,v2);
	}

	inline cp::Vect perp()
	{
		return cpvperp(*this);
	}

	inline cp::Vect rperp()
	{
		return cpvrperp(*this);
	}

	inline cp::Vect project(Vect& v2)
	{
		return cpvproject(*this,v2);
	}

	inline cp::Vect forangle(const cpFloat a)
	{
		return cpvforangle(a);
	}

	inline cpFloat toangle()
	{
		return cpvtoangle(*this);
	}

	inline cp::Vect rotate(Vect& v2)
	{
		return cpvrotate(*this,v2);
	}

	inline cp::Vect unrotate(Vect& v2)
	{
		return cpvunrotate(*this,v2);
	}

	inline cpFloat lengthsq()
	{
		return cpvlengthsq(*this);
	}

	inline cpFloat length()
	{
		return cpvlength(*this);
	}

	inline cp::Vect lerp(Vect& v2,const cpFloat t)
	{
		return cpvlerp(*this,v2,t);
	}

	inline cp::Vect normalize()
	{
		return cpvnormalize(*this);
	}

	inline cp::Vect normalize_safe()
	{
		return cpvnormalize_safe(*this);
	}

	inline cp::Vect clamp(const cpFloat len)
	{
		return cpvclamp(*this,len);
	}

	inline cp::Vect lerpconst(Vect& v2,cpFloat d)
	{
		return cpvlerpconst(*this,v2,d);
	}

	inline cpFloat dist(Vect& v2)
	{
		return cpvdist(*this,v2);
	}

	inline cpFloat distsq(Vect& v2)
	{
		return cpvdistsq(*this,v2);
	}

	inline cpBool near(Vect& v2,const cpFloat dist)
	{
		return cpvnear(*this,v2,dist);
	}

	Vect(cpFloat x=0, cpFloat y=0)
	{ this->x = x; this->y = y; }

	Vect(cpVect cv)
	{ this->x = cv.x; this->y = cv.y; }

};
}//namespace cp
