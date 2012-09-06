#pragma once

#include "chipmunk.h"
#include "SpatialIndex.hpp"

namespace cp {


class Sweep1D : public SpatialIndex{
protected:
	cpSweep1D*sweep1d;
public:

	cpSweep1D* get() const
	{
		return sweep1d;
	}

	operator cpSweep1D*() const
	{
		return sweep1d;
	}

	Sweep1D(cpSpatialIndexBBFunc bbfunc,cpSpatialIndex *staticIndex)
	 : SpatialIndex(cpSweep1DNew(bbfunc,staticIndex))
	{
			}

};
}//namespace cp
