/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 18:39:31.
 */
#include "Sweep1D.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"
#include "SpatialIndex.hpp"

namespace cp {

cpSweep1D* Sweep1D::get()
{
		return sweep1d;
}
Sweep1D::Sweep1D(cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex)
	: SpatialIndex(cpSweep1DNew(bbfunc,staticIndex ? staticIndex->get() : 0))
{
		}
};//namespace cp
