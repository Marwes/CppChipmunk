#pragma once

#include "chipmunk.h"

namespace cp {


class BB{
protected:
	cpBB bb;
public:

	cpBB  get() const
	{
		return bb;
	}

	operator cpBB () const
	{
		return bb;
	}

	inline cpBool intersects(const cpBB b)
	{
		return cpBBIntersects(bb,b);
	}

	inline cpBool containsBB(const cpBB other)
	{
		return cpBBContainsBB(bb,other);
	}

	inline cpBool containsVect(const cpVect v)
	{
		return cpBBContainsVect(bb,v);
	}

	inline cp::BB merge(const cpBB b)
	{
		return cpBBMerge(bb,b);
	}

	inline cp::BB expand(const cpVect v)
	{
		return cpBBExpand(bb,v);
	}

	inline cpFloat area()
	{
		return cpBBArea(bb);
	}

	inline cpFloat mergedArea(cpBB b)
	{
		return cpBBMergedArea(bb,b);
	}

	inline cpFloat segmentQuery(cpVect a,cpVect b)
	{
		return cpBBSegmentQuery(bb,a,b);
	}

	inline cpBool intersectsSegment(cpVect a,cpVect b)
	{
		return cpBBIntersectsSegment(bb,a,b);
	}

	inline cpVect wrapVect(const cpVect v)
	{
		return cpBBWrapVect(bb,v);
	}

	BB(cpBB  v)
	{
		bb = v;
	}

	BB(const cpFloat l,const cpFloat b,const cpFloat r,const cpFloat t)
	 : bb(cpBBNew(l,b,r,t))
	{
			}

	BB(const cpVect p,const cpFloat r)
	 : bb(cpBBNewForCircle(p,r))
	{
			}

};
}//namespace cp
