#pragma once

#include "chipmunk.h"
#include "SpatialIndex.hpp"

namespace cp {


class BBTree : public SpatialIndex{
protected:
	cpBBTree*bbtree;
public:

	cpBBTree* get() const
	{
		return bbtree;
	}

	operator cpBBTree*() const
	{
		return bbtree;
	}

	inline void optimize()
	{
		cpBBTreeOptimize(index);
	}

	inline void setVelocityFunc(cpBBTreeVelocityFunc func)
	{
		cpBBTreeSetVelocityFunc(index,func);
	}

	BBTree(cpSpatialIndexBBFunc bbfunc,cpSpatialIndex *staticIndex)
	 : SpatialIndex(cpBBTreeNew(bbfunc,staticIndex))
	{
			}

};
}//namespace cp
