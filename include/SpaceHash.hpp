/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/15/12 09:55:02.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"

namespace cp {

class SpaceHash : public SpatialIndex {
protected:
	cpSpaceHash* hash;
public:
	cpSpaceHash* get();
/// Allocate and initialize a spatial hash.
	SpaceHash(cpFloat celldim,int cells,cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex);
/// Change the cell dimensions and table size of the spatial hash to tune it.
/// The cell dimensions should roughly match the average size of your objects
/// and the table size should be ~10 larger than the number of objects inserted.
/// Some trial and error is required to find the optimum numbers for efficiency.
	void resize(cpFloat celldim,int numcells);

};
};//namespace cp
