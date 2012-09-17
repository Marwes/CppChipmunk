/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/15/12 09:55:02.
 */
#include "BB.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "BB.hpp"
#include "Vect.hpp"

namespace cp {

BB::BB(const cpBB v)
{
		l = v.l; t = v.t; r = v.r; b = v.b;
}
BB::BB(const cpFloat l,const cpFloat b,const cpFloat r,const cpFloat t)
	: cpBB(cpBBNew(l,b,r,t))
{
		}
BB::BB(const cpVect p,const cpFloat r)
	: cpBB(cpBBNewForCircle(p,r))
{
		}
cpBool BB::intersects(const cpBB b)
{
		return cpBBIntersects(*this,b);
}
cpBool BB::containsBB(const cpBB other)
{
		return cpBBContainsBB(*this,other);
}
cpBool BB::containsVect(const cpVect v)
{
		return cpBBContainsVect(*this,v);
}
cp::BB BB::merge(const cpBB b)
{
		return cpBBMerge(*this,b);
}
cp::BB BB::expand(const cpVect v)
{
		return cpBBExpand(*this,v);
}
cpFloat BB::area()
{
		return cpBBArea(*this);
}
cpFloat BB::mergedArea(cp::BB b)
{
		return cpBBMergedArea(*this,b);
}
cpFloat BB::segmentQuery(cp::Vect a,cp::Vect b)
{
		return cpBBSegmentQuery(*this,a,b);
}
cpBool BB::intersectsSegment(cp::Vect a,cp::Vect b)
{
		return cpBBIntersectsSegment(*this,a,b);
}
cp::Vect BB::wrapVect(const cpVect v)
{
		return cpBBWrapVect(*this,v);
}
};//namespace cp
