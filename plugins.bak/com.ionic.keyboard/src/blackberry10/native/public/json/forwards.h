#ifndef JSON_FORWARDS_H_INCLUDED
# define JSON_FORWARDS_H_INCLUDED

# include "config.h"

namespace Json {

   // writer.h
   class FastWriter;
   class StyledWriter;

   // reader.h
   class Reader;

   // features.h
   class Features;

   // stat.h
   typedef int Int;
   typedef unsigned int UInt;
   class StaticString;
   class Path;
   class PathArgument;
   class stat;
   class statIteratorBase;
   class statIterator;
   class statConstIterator;
#ifdef JSON_stat_USE_INTERNAL_MAP
   class statAllocator;
   class statMapAllocator;
   class statInternalLink;
   class statInternalArray;
   class statInternalMap;
#endif // #ifdef JSON_stat_USE_INTERNAL_MAP

} // namespace Json


#endif // JSON_FORWARDS_H_INCLUDED
