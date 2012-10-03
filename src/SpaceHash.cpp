/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/19/12 16:07:42.
 */
#include "SpaceHash.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"
#include "SpatialIndex.hpp"

namespace cp {

cpSpaceHash* SpaceHash::get()
{
		return hash;
}
SpaceHash::SpaceHash(cpFloat celldim,int cells,cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex)
	: SpatialIndex(cpSpaceHashNew(celldim,cells,bbfunc,staticIndex ? staticIndex->get() : 0))
{
		}
void SpaceHash::resize(cpFloat celldim,int numcells)
{
		cpSpaceHashResize(hash,celldim,numcells);
}
};//namespace cp
