/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
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
