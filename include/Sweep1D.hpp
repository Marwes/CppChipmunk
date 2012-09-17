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

class Sweep1D : public SpatialIndex {
protected:
	cpSweep1D* sweep1d;
public:
	cpSweep1D* get();
/// Allocate and initialize a 1D sort and sweep broadphase.
	Sweep1D(cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex);

};
};//namespace cp
