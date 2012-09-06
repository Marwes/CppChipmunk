#pragma once

#include "chipmunk.h"
#include "SpatialIndex.hpp"

namespace cp {


class SpaceHash : public SpatialIndex{
protected:
	cpSpaceHash*hash;
public:

	cpSpaceHash* get() const
	{
		return hash;
	}

	operator cpSpaceHash*() const
	{
		return hash;
	}

	inline void resize(cpFloat celldim,int numcells)
	{
		cpSpaceHashResize(hash,celldim,numcells);
	}

	SpaceHash(cpFloat celldim,int cells,cpSpatialIndexBBFunc bbfunc,cpSpatialIndex *staticIndex)
	 : SpatialIndex(cpSpaceHashNew(celldim,cells,bbfunc,staticIndex))
	{
			}

};
}//namespace cp
