#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"
#include "SpatialIndex.hpp"

namespace cp {

class SpaceHash : public SpatialIndex {
protected:
	cpSpaceHash* hash;
public:
	cpSpaceHash* get();
	SpaceHash(cpFloat celldim,int cells,cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex);
	void resize(cpFloat celldim,int numcells);

};
};//namespace cp