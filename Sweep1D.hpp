#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"
#include "SpatialIndex.hpp"

namespace cp {

class Sweep1D : public SpatialIndex {
protected:
	cpSweep1D* sweep1d;
public:
	cpSweep1D* get();
	Sweep1D(cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex);

};
};//namespace cp
