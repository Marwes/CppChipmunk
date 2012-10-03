/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 22:41:26.
 */
#include "Sweep1D.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"

namespace cp {

Sweep1D::Sweep1D(cpSpatialIndexBBFunc bbfunc,cpSpatialIndex *staticIndex)
	: SpatialIndex(cpSweep1DNew(bbfunc,SpatialIndex::get()))
{
		}
};//namespace cp
