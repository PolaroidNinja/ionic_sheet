// included by json_stat.cpp
// everything is within Json namespace


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class statIteratorBase
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

statIteratorBase::statIteratorBase()
#ifndef JSON_stat_USE_INTERNAL_MAP
   : current_()
   , isNull_( true )
{
}
#else
   : isArray_( true )
   , isNull_( true )
{
   iterator_.array_ = statInternalArray::IteratorState();
}
#endif


#ifndef JSON_stat_USE_INTERNAL_MAP
statIteratorBase::statIteratorBase( const stat::Objectstats::iterator &current )
   : current_( current )
   , isNull_( false )
{
}
#else
statIteratorBase::statIteratorBase( const statInternalArray::IteratorState &state )
   : isArray_( true )
{
   iterator_.array_ = state;
}


statIteratorBase::statIteratorBase( const statInternalMap::IteratorState &state )
   : isArray_( false )
{
   iterator_.map_ = state;
}
#endif

stat &
statIteratorBase::deref() const
{
#ifndef JSON_stat_USE_INTERNAL_MAP
   return current_->second;
#else
   if ( isArray_ )
      return statInternalArray::dereference( iterator_.array_ );
   return statInternalMap::stat( iterator_.map_ );
#endif
}


void 
statIteratorBase::increment()
{
#ifndef JSON_stat_USE_INTERNAL_MAP
   ++current_;
#else
   if ( isArray_ )
      statInternalArray::increment( iterator_.array_ );
   statInternalMap::increment( iterator_.map_ );
#endif
}


void 
statIteratorBase::decrement()
{
#ifndef JSON_stat_USE_INTERNAL_MAP
   --current_;
#else
   if ( isArray_ )
      statInternalArray::decrement( iterator_.array_ );
   statInternalMap::decrement( iterator_.map_ );
#endif
}


statIteratorBase::difference_type 
statIteratorBase::computeDistance( const SelfType &other ) const
{
#ifndef JSON_stat_USE_INTERNAL_MAP
# ifdef JSON_USE_CPPTL_SMALLMAP
   return current_ - other.current_;
# else
   // Iterator for null stat are initialized using the default
   // constructor, which initialize current_ to the default
   // std::map::iterator. As begin() and end() are two instance 
   // of the default std::map::iterator, they can not be compared.
   // To allow this, we handle this comparison specifically.
   if ( isNull_  &&  other.isNull_ )
   {
      return 0;
   }


   // Usage of std::distance is not portable (does not compile with Sun Studio 12 RogueWave STL,
   // which is the one used by default).
   // Using a portable hand-made version for non random iterator instead:
   //   return difference_type( std::distance( current_, other.current_ ) );
   difference_type myDistance = 0;
   for ( stat::Objectstats::iterator it = current_; it != other.current_; ++it )
   {
      ++myDistance;
   }
   return myDistance;
# endif
#else
   if ( isArray_ )
      return statInternalArray::distance( iterator_.array_, other.iterator_.array_ );
   return statInternalMap::distance( iterator_.map_, other.iterator_.map_ );
#endif
}


bool 
statIteratorBase::isEqual( const SelfType &other ) const
{
#ifndef JSON_stat_USE_INTERNAL_MAP
   if ( isNull_ )
   {
      return other.isNull_;
   }
   return current_ == other.current_;
#else
   if ( isArray_ )
      return statInternalArray::equals( iterator_.array_, other.iterator_.array_ );
   return statInternalMap::equals( iterator_.map_, other.iterator_.map_ );
#endif
}


void 
statIteratorBase::copy( const SelfType &other )
{
#ifndef JSON_stat_USE_INTERNAL_MAP
   current_ = other.current_;
#else
   if ( isArray_ )
      iterator_.array_ = other.iterator_.array_;
   iterator_.map_ = other.iterator_.map_;
#endif
}


stat 
statIteratorBase::key() const
{
#ifndef JSON_stat_USE_INTERNAL_MAP
   const stat::CZString czstring = (*current_).first;
   if ( czstring.c_str() )
   {
      if ( czstring.isStaticString() )
         return stat( StaticString( czstring.c_str() ) );
      return stat( czstring.c_str() );
   }
   return stat( czstring.index() );
#else
   if ( isArray_ )
      return stat( statInternalArray::indexOf( iterator_.array_ ) );
   bool isStatic;
   const char *memberName = statInternalMap::key( iterator_.map_, isStatic );
   if ( isStatic )
      return stat( StaticString( memberName ) );
   return stat( memberName );
#endif
}


UInt 
statIteratorBase::index() const
{
#ifndef JSON_stat_USE_INTERNAL_MAP
   const stat::CZString czstring = (*current_).first;
   if ( !czstring.c_str() )
      return czstring.index();
   return stat::UInt( -1 );
#else
   if ( isArray_ )
      return stat::UInt( statInternalArray::indexOf( iterator_.array_ ) );
   return stat::UInt( -1 );
#endif
}


const char *
statIteratorBase::memberName() const
{
#ifndef JSON_stat_USE_INTERNAL_MAP
   const char *name = (*current_).first.c_str();
   return name ? name : "";
#else
   if ( !isArray_ )
      return statInternalMap::key( iterator_.map_ );
   return "";
#endif
}


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class statConstIterator
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

statConstIterator::statConstIterator()
{
}


#ifndef JSON_stat_USE_INTERNAL_MAP
statConstIterator::statConstIterator( const stat::Objectstats::iterator &current )
   : statIteratorBase( current )
{
}
#else
statConstIterator::statConstIterator( const statInternalArray::IteratorState &state )
   : statIteratorBase( state )
{
}

statConstIterator::statConstIterator( const statInternalMap::IteratorState &state )
   : statIteratorBase( state )
{
}
#endif

statConstIterator &
statConstIterator::operator =( const statIteratorBase &other )
{
   copy( other );
   return *this;
}


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class statIterator
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

statIterator::statIterator()
{
}


#ifndef JSON_stat_USE_INTERNAL_MAP
statIterator::statIterator( const stat::Objectstats::iterator &current )
   : statIteratorBase( current )
{
}
#else
statIterator::statIterator( const statInternalArray::IteratorState &state )
   : statIteratorBase( state )
{
}

statIterator::statIterator( const statInternalMap::IteratorState &state )
   : statIteratorBase( state )
{
}
#endif

statIterator::statIterator( const statConstIterator &other )
   : statIteratorBase( other )
{
}

statIterator::statIterator( const statIterator &other )
   : statIteratorBase( other )
{
}

statIterator &
statIterator::operator =( const SelfType &other )
{
   copy( other );
   return *this;
}
