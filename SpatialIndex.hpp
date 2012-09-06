#pragma once

#include "chipmunk.h"
#include <functional>

class SpatialIndex;
namespace {
	void SpatialIndexCollideStatic(void *obj1,void *obj2,void *data);
	void SpatialIndexEach(void *obj,void *data);
	void SpatialIndexQuery(void *obj1,void *obj2,void *data);
	cpFloat SpatialIndexSegmentQuery(void *obj1,void *obj2,void *data);
	void SpatialIndexReindexQuery(void *obj1,void *obj2,void *data);
}

namespace cp {

typedef std::function<void (void *,void *)> SpatialIndexQueryFunc ;
typedef std::function<void (void *)> SpatialIndexIteratorFunc ;
typedef std::function<void (void *,void *)> SpatialIndexQueryFunc ;
typedef std::function<cpFloat (void *,void *)> SpatialIndexSegmentQueryFunc ;
typedef std::function<void (void *,void *)> SpatialIndexQueryFunc ;

class SpatialIndex{
protected:
	cpSpatialIndex*index;
public:

	cpSpatialIndex* get() const
	{
		return index;
	}

	operator cpSpatialIndex*() const
	{
		return index;
	}

	~SpatialIndex()
	{
		cpSpatialIndexFree(index);
	}

	inline void collideStatic(cpSpatialIndex *staticIndex,SpatialIndexQueryFunc func)
	{
		cpSpatialIndexCollideStatic(index->dynamicIndex,staticIndex,*SpatialIndexCollideStatic,&func);
	};

	inline void collideStatic(cpSpatialIndex *staticIndex,cpSpatialIndexQueryFunc func,void *data)
	{
		cpSpatialIndexCollideStatic(index,staticIndex,func,data);
	}

	inline int count()
	{
		return cpSpatialIndexCount(index);
	}

	inline void each(SpatialIndexIteratorFunc func)
	{
		cpSpatialIndexEach(index,*SpatialIndexEach,&func);
	};

	inline void each(cpSpatialIndexIteratorFunc func,void *data)
	{
		cpSpatialIndexEach(index,func,data);
	}

	inline cpBool contains(void *obj,cpHashValue hashid)
	{
		return cpSpatialIndexContains(index,obj,hashid);
	}

	inline void insert(void *obj,cpHashValue hashid)
	{
		cpSpatialIndexInsert(index,obj,hashid);
	}

	inline void remove(void *obj,cpHashValue hashid)
	{
		cpSpatialIndexRemove(index,obj,hashid);
	}

	inline void reindex()
	{
		cpSpatialIndexReindex(index);
	}

	inline void reindexObject(void *obj,cpHashValue hashid)
	{
		cpSpatialIndexReindexObject(index,obj,hashid);
	}

	inline void query(void *obj,cpBB bb,SpatialIndexQueryFunc func)
	{
		cpSpatialIndexQuery(index,obj,bb,*SpatialIndexQuery,&func);
	};

	inline void query(void *obj,cpBB bb,cpSpatialIndexQueryFunc func,void *data)
	{
		cpSpatialIndexQuery(index,obj,bb,func,data);
	}

	inline void segmentQuery(void *obj,cpVect a,cpVect b,cpFloat t_exit,SpatialIndexSegmentQueryFunc func)
	{
		cpSpatialIndexSegmentQuery(index,obj,a,b,t_exit,*SpatialIndexSegmentQuery,&func);
	};

	inline void segmentQuery(void *obj,cpVect a,cpVect b,cpFloat t_exit,cpSpatialIndexSegmentQueryFunc func,void *data)
	{
		cpSpatialIndexSegmentQuery(index,obj,a,b,t_exit,func,data);
	}

	inline void reindexQuery(SpatialIndexQueryFunc func)
	{
		cpSpatialIndexReindexQuery(index,*SpatialIndexReindexQuery,&func);
	};

	inline void reindexQuery(cpSpatialIndexQueryFunc func,void *data)
	{
		cpSpatialIndexReindexQuery(index,func,data);
	}

	SpatialIndex(cpSpatialIndex* v)
	{
		index = v;
	}

};
}//namespace cp

namespace {
	void SpatialIndexCollideStatic(void *obj1,void *obj2,void *data)
	{
		(*reinterpret_cast<std::function<void (void *,void *)> *>(data))(obj1,obj2);
	}

	void SpatialIndexEach(void *obj,void *data)
	{
		(*reinterpret_cast<std::function<void (void *)> *>(data))(obj);
	}

	void SpatialIndexQuery(void *obj1,void *obj2,void *data)
	{
		(*reinterpret_cast<std::function<void (void *,void *)> *>(data))(obj1,obj2);
	}

	cpFloat SpatialIndexSegmentQuery(void *obj1,void *obj2,void *data)
	{
		return (*reinterpret_cast<std::function<cpFloat (void *,void *)> *>(data))(obj1,obj2);
	}

	void SpatialIndexReindexQuery(void *obj1,void *obj2,void *data)
	{
		(*reinterpret_cast<std::function<void (void *,void *)> *>(data))(obj1,obj2);
	}

}