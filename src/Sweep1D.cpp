/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on Mon Nov 12 17:53:27 2012.
 */
#include "Sweep1D.hpp"
#include <utility>
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"
#include "SpatialIndex.hpp"

namespace cp {

Sweep1D::Sweep1D(cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex)
	: SpatialIndex(cpSweep1DNew(bbfunc,staticIndex ? staticIndex->get() : 0))
{
		}
Sweep1D::Sweep1D(Sweep1D&&o)
	: sweep1d(o.sweep1d),
	  SpatialIndex(std::move(o))
{
				o.sweep1d = 0;
}
};//namespace cp
