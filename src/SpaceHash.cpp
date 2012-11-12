/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 11/12/12 01:17:41.
 */
#include "SpaceHash.hpp"
#include <utility>
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"
#include "SpatialIndex.hpp"

namespace cp {

SpaceHash::SpaceHash(cpFloat celldim,int cells,cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex)
	: SpatialIndex(cpSpaceHashNew(celldim,cells,bbfunc,staticIndex ? staticIndex->get() : 0))
{
		}
void SpaceHash::resize(cpFloat celldim,int numcells)
{
		cpSpaceHashResize(hash,celldim,numcells);
}
SpaceHash::SpaceHash(SpaceHash&&o)
	: hash(o.hash),
	  SpatialIndex(std::move(o))
{
				o.hash = 0;
}
};//namespace cp
