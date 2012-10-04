/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 20:19:55.
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
BB::BB(const cp::Vect p,const cpFloat r)
	: cpBB(cpBBNewForCircle(p,r))
{
		}
cpBool BB::intersects(const cp::BB b)
{
		return cpBBIntersects(*this,b);
}
cpBool BB::containsBB(const cp::BB other)
{
		return cpBBContainsBB(*this,other);
}
cpBool BB::containsVect(const cp::Vect v)
{
		return cpBBContainsVect(*this,v);
}
cp::BB BB::merge(const cp::BB b)
{
		return cpBBMerge(*this,b);
}
cp::BB BB::expand(const cp::Vect v)
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
cp::Vect BB::wrapVect(const cp::Vect v)
{
		return cpBBWrapVect(*this,v);
}
};//namespace cp
