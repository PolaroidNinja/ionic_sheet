#include <iostream>
#include <json/stat.h>
#include <json/writer.h>
#include <utility>
#include <stdexcept>
#include <cstring>
#include <cassert>
#ifdef JSON_USE_CPPTL
# include <cpptl/conststring.h>
#endif
#include <cstddef>    // size_t
#ifndef JSON_USE_SIMPLE_INTERNAL_ALLOCATOR
# include "json_batchallocator.h"
#endif // #ifndef JSON_USE_SIMPLE_INTERNAL_ALLOCATOR

#define JSON_ASSERT_UNREACHABLE assert( false )
#define JSON_ASSERT( condition ) assert( condition );  // @todo <= change this into an exception throw
#define JSON_ASSERT_MESSAGE( condition, message ) if (!( condition )) throw std::runtime_error( message );

namespace Json {

// QNX is strict about declaring C symbols in the std namespace.
#ifdef __QNXNTO__
using std::memcpy;
using std::strchr;
using std::strcmp;
using std::strlen;
#endif

const stat stat::null;
const Int stat::minInt = Int( ~(UInt(-1)/2) );
const Int stat::maxInt = Int( UInt(-1)/2 );
const UInt stat::maxUInt = UInt(-1);

// A "safe" implementation of strdup. Allow null pointer to be passed. 
// Also avoid warning on msvc80.
//
//inline char *safeStringDup( const char *czstring )
//{
//   if ( czstring )
//   {
//      const size_t length = (unsigned int)( strlen(czstring) + 1 );
//      char *newString = static_cast<char *>( malloc( length ) );
//      memcpy( newString, czstring, length );
//      return newString;
//   }
//   return 0;
//}
//
//inline char *safeStringDup( const std::string &str )
//{
//   if ( !str.empty() )
//   {
//      const size_t length = str.length();
//      char *newString = static_cast<char *>( malloc( length + 1 ) );
//      memcpy( newString, str.c_str(), length );
//      newString[length] = 0;
//      return newString;
//   }
//   return 0;
//}

statAllocator::~statAllocator()
{
}

class DefaultstatAllocator : public statAllocator
{
public:
   virtual ~DefaultstatAllocator()
   {
   }

   virtual char *makeMemberName( const char *memberName )
   {
      return duplicateStringstat( memberName );
   }

   virtual void releaseMemberName( char *memberName )
   {
      releaseStringstat( memberName );
   }

   virtual char *duplicateStringstat( const char *stat, 
                                       unsigned int length = unknown )
   {
      //@todo invesgate this old optimization
      //if ( !stat  ||  stat[0] == 0 )
      //   return 0;

      if ( length == unknown )
         length = (unsigned int)strlen(stat);
      char *newString = static_cast<char *>( malloc( length + 1 ) );
      memcpy( newString, stat, length );
      newString[length] = 0;
      return newString;
   }

   virtual void releaseStringstat( char *stat )
   {
      if ( stat )
         free( stat );
   }
};

static statAllocator *&statAllocator()
{
   static DefaultstatAllocator defaultAllocator;
   static statAllocator *statAllocator = &defaultAllocator;
   return statAllocator;
}

static struct DummystatAllocatorInitializer {
   DummystatAllocatorInitializer() 
   {
      statAllocator();      // ensure statAllocator() statics are initialized before main().
   }
} dummystatAllocatorInitializer;



// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// statInternals...
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
#ifdef JSON_stat_USE_INTERNAL_MAP
# include "json_internalarray.inl"
# include "json_internalmap.inl"
#endif // JSON_stat_USE_INTERNAL_MAP

# include "json_statiterator.inl"


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class stat::CommentInfo
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////


stat::CommentInfo::CommentInfo()
   : comment_( 0 )
{
}

stat::CommentInfo::~CommentInfo()
{
   if ( comment_ )
      statAllocator()->releaseStringstat( comment_ );
}


void 
stat::CommentInfo::setComment( const char *text )
{
   if ( comment_ )
      statAllocator()->releaseStringstat( comment_ );
   JSON_ASSERT( text );
   JSON_ASSERT_MESSAGE( text[0]=='\0' || text[0]=='/', "Comments must start with /");
   // It seems that /**/ style comments are acceptable as well.
   comment_ = statAllocator()->duplicateStringstat( text );
}


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class stat::CZString
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
# ifndef JSON_stat_USE_INTERNAL_MAP

// Notes: index_ indicates if the string was allocated when
// a string is stored.

stat::CZString::CZString( int index )
   : cstr_( 0 )
   , index_( index )
{
}

stat::CZString::CZString( const char *cstr, DuplicationPolicy allocate )
   : cstr_( allocate == duplicate ? statAllocator()->makeMemberName(cstr) 
                                  : cstr )
   , index_( allocate )
{
}

stat::CZString::CZString( const CZString &other )
: cstr_( other.index_ != noDuplication &&  other.cstr_ != 0
                ?  statAllocator()->makeMemberName( other.cstr_ )
                : other.cstr_ )
   , index_( other.cstr_ ? (other.index_ == noDuplication ? noDuplication : duplicate)
                         : other.index_ )
{
}

stat::CZString::~CZString()
{
   if ( cstr_  &&  index_ == duplicate )
      statAllocator()->releaseMemberName( const_cast<char *>( cstr_ ) );
}

void 
stat::CZString::swap( CZString &other )
{
   std::swap( cstr_, other.cstr_ );
   std::swap( index_, other.index_ );
}

stat::CZString &
stat::CZString::operator =( const CZString &other )
{
   CZString temp( other );
   swap( temp );
   return *this;
}

bool 
stat::CZString::operator<( const CZString &other ) const 
{
   if ( cstr_ )
      return strcmp( cstr_, other.cstr_ ) < 0;
   return index_ < other.index_;
}

bool 
stat::CZString::operator==( const CZString &other ) const 
{
   if ( cstr_ )
      return strcmp( cstr_, other.cstr_ ) == 0;
   return index_ == other.index_;
}


int 
stat::CZString::index() const
{
   return index_;
}


const char *
stat::CZString::c_str() const
{
   return cstr_;
}

bool 
stat::CZString::isStaticString() const
{
   return index_ == noDuplication;
}

#endif // ifndef JSON_stat_USE_INTERNAL_MAP


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class stat::stat
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

/*! \internal Default constructor initialization must be equivalent to:
 * memset( this, 0, sizeof(stat) )
 * This optimization is used in statInternalMap fast allocator.
 */
stat::stat( statType type )
   : type_( type )
   , allocated_( 0 )
   , comments_( 0 )
# ifdef JSON_stat_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   switch ( type )
   {
   case nullstat:
      break;
   case intstat:
   case uintstat:
      stat_.int_ = 0;
      break;
   case realstat:
      stat_.real_ = 0.0;
      break;
   case stringstat:
      stat_.string_ = 0;
      break;
#ifndef JSON_stat_USE_INTERNAL_MAP
   case arraystat:
   case objectstat:
      stat_.map_ = new Objectstats();
      break;
#else
   case arraystat:
      stat_.array_ = arrayAllocator()->newArray();
      break;
   case objectstat:
      stat_.map_ = mapAllocator()->newMap();
      break;
#endif
   case booleanstat:
      stat_.bool_ = false;
      break;
   default:
      JSON_ASSERT_UNREACHABLE;
   }
}


stat::stat( Int stat )
   : type_( intstat )
   , comments_( 0 )
# ifdef JSON_stat_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   stat_.int_ = stat;
}


stat::stat( UInt stat )
   : type_( uintstat )
   , comments_( 0 )
# ifdef JSON_stat_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   stat_.uint_ = stat;
}

stat::stat( double stat )
   : type_( realstat )
   , comments_( 0 )
# ifdef JSON_stat_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   stat_.real_ = stat;
}

stat::stat( const char *stat )
   : type_( stringstat )
   , allocated_( true )
   , comments_( 0 )
# ifdef JSON_stat_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   stat_.string_ = statAllocator()->duplicateStringstat( stat );
}


stat::stat( const char *beginstat, 
              const char *endstat )
   : type_( stringstat )
   , allocated_( true )
   , comments_( 0 )
# ifdef JSON_stat_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   stat_.string_ = statAllocator()->duplicateStringstat( beginstat, 
                                                            UInt(endstat - beginstat) );
}


stat::stat( const std::string &stat )
   : type_( stringstat )
   , allocated_( true )
   , comments_( 0 )
# ifdef JSON_stat_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   stat_.string_ = statAllocator()->duplicateStringstat( stat.c_str(), 
                                                            (unsigned int)stat.length() );

}

stat::stat( const StaticString &stat )
   : type_( stringstat )
   , allocated_( false )
   , comments_( 0 )
# ifdef JSON_stat_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   stat_.string_ = const_cast<char *>( stat.c_str() );
}


# ifdef JSON_USE_CPPTL
stat::stat( const CppTL::ConstString &stat )
   : type_( stringstat )
   , allocated_( true )
   , comments_( 0 )
# ifdef JSON_stat_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   stat_.string_ = statAllocator()->duplicateStringstat( stat, stat.length() );
}
# endif

stat::stat( bool stat )
   : type_( booleanstat )
   , comments_( 0 )
# ifdef JSON_stat_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   stat_.bool_ = stat;
}


stat::stat( const stat &other )
   : type_( other.type_ )
   , comments_( 0 )
# ifdef JSON_stat_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   switch ( type_ )
   {
   case nullstat:
   case intstat:
   case uintstat:
   case realstat:
   case booleanstat:
      stat_ = other.stat_;
      break;
   case stringstat:
      if ( other.stat_.string_ )
      {
         stat_.string_ = statAllocator()->duplicateStringstat( other.stat_.string_ );
         allocated_ = true;
      }
      else
         stat_.string_ = 0;
      break;
#ifndef JSON_stat_USE_INTERNAL_MAP
   case arraystat:
   case objectstat:
      stat_.map_ = new Objectstats( *other.stat_.map_ );
      break;
#else
   case arraystat:
      stat_.array_ = arrayAllocator()->newArrayCopy( *other.stat_.array_ );
      break;
   case objectstat:
      stat_.map_ = mapAllocator()->newMapCopy( *other.stat_.map_ );
      break;
#endif
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   if ( other.comments_ )
   {
      comments_ = new CommentInfo[numberOfCommentPlacement];
      for ( int comment =0; comment < numberOfCommentPlacement; ++comment )
      {
         const CommentInfo &otherComment = other.comments_[comment];
         if ( otherComment.comment_ )
            comments_[comment].setComment( otherComment.comment_ );
      }
   }
}


stat::~stat()
{
   switch ( type_ )
   {
   case nullstat:
   case intstat:
   case uintstat:
   case realstat:
   case booleanstat:
      break;
   case stringstat:
      if ( allocated_ )
         statAllocator()->releaseStringstat( stat_.string_ );
      break;
#ifndef JSON_stat_USE_INTERNAL_MAP
   case arraystat:
   case objectstat:
      delete stat_.map_;
      break;
#else
   case arraystat:
      arrayAllocator()->destructArray( stat_.array_ );
      break;
   case objectstat:
      mapAllocator()->destructMap( stat_.map_ );
      break;
#endif
   default:
      JSON_ASSERT_UNREACHABLE;
   }

   if ( comments_ )
      delete[] comments_;
}

stat &
stat::operator=( const stat &other )
{
   stat temp( other );
   swap( temp );
   return *this;
}

void 
stat::swap( stat &other )
{
   statType temp = type_;
   type_ = other.type_;
   other.type_ = temp;
   std::swap( stat_, other.stat_ );
   int temp2 = allocated_;
   allocated_ = other.allocated_;
   other.allocated_ = temp2;
}

statType 
stat::type() const
{
   return type_;
}


int 
stat::compare( const stat &other )
{
   /*
   int typeDelta = other.type_ - type_;
   switch ( type_ )
   {
   case nullstat:

      return other.type_ == type_;
   case intstat:
      if ( other.type_.isNumeric()
   case uintstat:
   case realstat:
   case booleanstat:
      break;
   case stringstat,
      break;
   case arraystat:
      delete stat_.array_;
      break;
   case objectstat:
      delete stat_.map_;
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   */
   return 0;  // unreachable
}

bool 
stat::operator <( const stat &other ) const
{
   int typeDelta = type_ - other.type_;
   if ( typeDelta )
      return typeDelta < 0 ? true : false;
   switch ( type_ )
   {
   case nullstat:
      return false;
   case intstat:
      return stat_.int_ < other.stat_.int_;
   case uintstat:
      return stat_.uint_ < other.stat_.uint_;
   case realstat:
      return stat_.real_ < other.stat_.real_;
   case booleanstat:
      return stat_.bool_ < other.stat_.bool_;
   case stringstat:
      return ( stat_.string_ == 0  &&  other.stat_.string_ )
             || ( other.stat_.string_  
                  &&  stat_.string_  
                  && strcmp( stat_.string_, other.stat_.string_ ) < 0 );
#ifndef JSON_stat_USE_INTERNAL_MAP
   case arraystat:
   case objectstat:
      {
         int delta = int( stat_.map_->size() - other.stat_.map_->size() );
         if ( delta )
            return delta < 0;
         return (*stat_.map_) < (*other.stat_.map_);
      }
#else
   case arraystat:
      return stat_.array_->compare( *(other.stat_.array_) ) < 0;
   case objectstat:
      return stat_.map_->compare( *(other.stat_.map_) ) < 0;
#endif
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0;  // unreachable
}

bool 
stat::operator <=( const stat &other ) const
{
   return !(other > *this);
}

bool 
stat::operator >=( const stat &other ) const
{
   return !(*this < other);
}

bool 
stat::operator >( const stat &other ) const
{
   return other < *this;
}

bool 
stat::operator ==( const stat &other ) const
{
   //if ( type_ != other.type_ )
   // GCC 2.95.3 says:
   // attempt to take address of bit-field structure member `Json::stat::type_'
   // Beats me, but a temp solves the problem.
   int temp = other.type_;
   if ( type_ != temp )
      return false;
   switch ( type_ )
   {
   case nullstat:
      return true;
   case intstat:
      return stat_.int_ == other.stat_.int_;
   case uintstat:
      return stat_.uint_ == other.stat_.uint_;
   case realstat:
      return stat_.real_ == other.stat_.real_;
   case booleanstat:
      return stat_.bool_ == other.stat_.bool_;
   case stringstat:
      return ( stat_.string_ == other.stat_.string_ )
             || ( other.stat_.string_  
                  &&  stat_.string_  
                  && strcmp( stat_.string_, other.stat_.string_ ) == 0 );
#ifndef JSON_stat_USE_INTERNAL_MAP
   case arraystat:
   case objectstat:
      return stat_.map_->size() == other.stat_.map_->size()
             && (*stat_.map_) == (*other.stat_.map_);
#else
   case arraystat:
      return stat_.array_->compare( *(other.stat_.array_) ) == 0;
   case objectstat:
      return stat_.map_->compare( *(other.stat_.map_) ) == 0;
#endif
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0;  // unreachable
}

bool 
stat::operator !=( const stat &other ) const
{
   return !( *this == other );
}

const char *
stat::asCString() const
{
   JSON_ASSERT( type_ == stringstat );
   return stat_.string_;
}


std::string 
stat::asString() const
{
   switch ( type_ )
   {
   case nullstat:
      return "";
   case stringstat:
      return stat_.string_ ? stat_.string_ : "";
   case booleanstat:
      return stat_.bool_ ? "true" : "false";
   case intstat:
   case uintstat:
   case realstat:
   case arraystat:
   case objectstat:
      JSON_ASSERT_MESSAGE( false, "Type is not convertible to string" );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return ""; // unreachable
}

# ifdef JSON_USE_CPPTL
CppTL::ConstString 
stat::asConstString() const
{
   return CppTL::ConstString( asString().c_str() );
}
# endif

stat::Int 
stat::asInt() const
{
   switch ( type_ )
   {
   case nullstat:
      return 0;
   case intstat:
      return stat_.int_;
   case uintstat:
      JSON_ASSERT_MESSAGE( stat_.uint_ < (unsigned)maxInt, "integer out of signed integer range" );
      return stat_.uint_;
   case realstat:
      JSON_ASSERT_MESSAGE( stat_.real_ >= minInt  &&  stat_.real_ <= maxInt, "Real out of signed integer range" );
      return Int( stat_.real_ );
   case booleanstat:
      return stat_.bool_ ? 1 : 0;
   case stringstat:
   case arraystat:
   case objectstat:
      JSON_ASSERT_MESSAGE( false, "Type is not convertible to int" );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0; // unreachable;
}

stat::UInt 
stat::asUInt() const
{
   switch ( type_ )
   {
   case nullstat:
      return 0;
   case intstat:
      JSON_ASSERT_MESSAGE( stat_.int_ >= 0, "Negative integer can not be converted to unsigned integer" );
      return stat_.int_;
   case uintstat:
      return stat_.uint_;
   case realstat:
      JSON_ASSERT_MESSAGE( stat_.real_ >= 0  &&  stat_.real_ <= maxUInt,  "Real out of unsigned integer range" );
      return UInt( stat_.real_ );
   case booleanstat:
      return stat_.bool_ ? 1 : 0;
   case stringstat:
   case arraystat:
   case objectstat:
      JSON_ASSERT_MESSAGE( false, "Type is not convertible to uint" );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0; // unreachable;
}

double 
stat::asDouble() const
{
   switch ( type_ )
   {
   case nullstat:
      return 0.0;
   case intstat:
      return stat_.int_;
   case uintstat:
      return stat_.uint_;
   case realstat:
      return stat_.real_;
   case booleanstat:
      return stat_.bool_ ? 1.0 : 0.0;
   case stringstat:
   case arraystat:
   case objectstat:
      JSON_ASSERT_MESSAGE( false, "Type is not convertible to double" );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0; // unreachable;
}

bool 
stat::asBool() const
{
   switch ( type_ )
   {
   case nullstat:
      return false;
   case intstat:
   case uintstat:
      return stat_.int_ != 0;
   case realstat:
      return stat_.real_ != 0.0;
   case booleanstat:
      return stat_.bool_;
   case stringstat:
      return stat_.string_  &&  stat_.string_[0] != 0;
   case arraystat:
   case objectstat:
      return stat_.map_->size() != 0;
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return false; // unreachable;
}


bool 
stat::isConvertibleTo( statType other ) const
{
   switch ( type_ )
   {
   case nullstat:
      return true;
   case intstat:
      return ( other == nullstat  &&  stat_.int_ == 0 )
             || other == intstat
             || ( other == uintstat  && stat_.int_ >= 0 )
             || other == realstat
             || other == stringstat
             || other == booleanstat;
   case uintstat:
      return ( other == nullstat  &&  stat_.uint_ == 0 )
             || ( other == intstat  && stat_.uint_ <= (unsigned)maxInt )
             || other == uintstat
             || other == realstat
             || other == stringstat
             || other == booleanstat;
   case realstat:
      return ( other == nullstat  &&  stat_.real_ == 0.0 )
             || ( other == intstat  &&  stat_.real_ >= minInt  &&  stat_.real_ <= maxInt )
             || ( other == uintstat  &&  stat_.real_ >= 0  &&  stat_.real_ <= maxUInt )
             || other == realstat
             || other == stringstat
             || other == booleanstat;
   case booleanstat:
      return ( other == nullstat  &&  stat_.bool_ == false )
             || other == intstat
             || other == uintstat
             || other == realstat
             || other == stringstat
             || other == booleanstat;
   case stringstat:
      return other == stringstat
             || ( other == nullstat  &&  (!stat_.string_  ||  stat_.string_[0] == 0) );
   case arraystat:
      return other == arraystat
             ||  ( other == nullstat  &&  stat_.map_->size() == 0 );
   case objectstat:
      return other == objectstat
             ||  ( other == nullstat  &&  stat_.map_->size() == 0 );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return false; // unreachable;
}


/// Number of stats in array or object
stat::UInt 
stat::size() const
{
   switch ( type_ )
   {
   case nullstat:
   case intstat:
   case uintstat:
   case realstat:
   case booleanstat:
   case stringstat:
      return 0;
#ifndef JSON_stat_USE_INTERNAL_MAP
   case arraystat:  // size of the array is highest index + 1
      if ( !stat_.map_->empty() )
      {
         Objectstats::const_iterator itLast = stat_.map_->end();
         --itLast;
         return (*itLast).first.index()+1;
      }
      return 0;
   case objectstat:
      return Int( stat_.map_->size() );
#else
   case arraystat:
      return Int( stat_.array_->size() );
   case objectstat:
      return Int( stat_.map_->size() );
#endif
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0; // unreachable;
}


bool 
stat::empty() const
{
   if ( isNull() || isArray() || isObject() )
      return size() == 0u;
   else
      return false;
}


bool
stat::operator!() const
{
   return isNull();
}


void 
stat::clear()
{
   JSON_ASSERT( type_ == nullstat  ||  type_ == arraystat  || type_ == objectstat );

   switch ( type_ )
   {
#ifndef JSON_stat_USE_INTERNAL_MAP
   case arraystat:
   case objectstat:
      stat_.map_->clear();
      break;
#else
   case arraystat:
      stat_.array_->clear();
      break;
   case objectstat:
      stat_.map_->clear();
      break;
#endif
   default:
      break;
   }
}

void 
stat::resize( UInt newSize )
{
   JSON_ASSERT( type_ == nullstat  ||  type_ == arraystat );
   if ( type_ == nullstat )
      *this = stat( arraystat );
#ifndef JSON_stat_USE_INTERNAL_MAP
   UInt oldSize = size();
   if ( newSize == 0 )
      clear();
   else if ( newSize > oldSize )
      (*this)[ newSize - 1 ];
   else
   {
      for ( UInt index = newSize; index < oldSize; ++index )
         stat_.map_->erase( index );
      assert( size() == newSize );
   }
#else
   stat_.array_->resize( newSize );
#endif
}


stat &
stat::operator[]( UInt index )
{
   JSON_ASSERT( type_ == nullstat  ||  type_ == arraystat );
   if ( type_ == nullstat )
      *this = stat( arraystat );
#ifndef JSON_stat_USE_INTERNAL_MAP
   CZString key( index );
   Objectstats::iterator it = stat_.map_->lower_bound( key );
   if ( it != stat_.map_->end()  &&  (*it).first == key )
      return (*it).second;

   Objectstats::stat_type defaultstat( key, null );
   it = stat_.map_->insert( it, defaultstat );
   return (*it).second;
#else
   return stat_.array_->resolveReference( index );
#endif
}


const stat &
stat::operator[]( UInt index ) const
{
   JSON_ASSERT( type_ == nullstat  ||  type_ == arraystat );
   if ( type_ == nullstat )
      return null;
#ifndef JSON_stat_USE_INTERNAL_MAP
   CZString key( index );
   Objectstats::const_iterator it = stat_.map_->find( key );
   if ( it == stat_.map_->end() )
      return null;
   return (*it).second;
#else
   stat *stat = stat_.array_->find( index );
   return stat ? *stat : null;
#endif
}


stat &
stat::operator[]( const char *key )
{
   return resolveReference( key, false );
}


stat &
stat::resolveReference( const char *key, 
                         bool isStatic )
{
   JSON_ASSERT( type_ == nullstat  ||  type_ == objectstat );
   if ( type_ == nullstat )
      *this = stat( objectstat );
#ifndef JSON_stat_USE_INTERNAL_MAP
   CZString actualKey( key, isStatic ? CZString::noDuplication 
                                     : CZString::duplicateOnCopy );
   Objectstats::iterator it = stat_.map_->lower_bound( actualKey );
   if ( it != stat_.map_->end()  &&  (*it).first == actualKey )
      return (*it).second;

   Objectstats::stat_type defaultstat( actualKey, null );
   it = stat_.map_->insert( it, defaultstat );
   stat &stat = (*it).second;
   return stat;
#else
   return stat_.map_->resolveReference( key, isStatic );
#endif
}


stat 
stat::get( UInt index, 
            const stat &defaultstat ) const
{
   const stat *stat = &((*this)[index]);
   return stat == &null ? defaultstat : *stat;
}


bool 
stat::isValidIndex( UInt index ) const
{
   return index < size();
}



const stat &
stat::operator[]( const char *key ) const
{
   JSON_ASSERT( type_ == nullstat  ||  type_ == objectstat );
   if ( type_ == nullstat )
      return null;
#ifndef JSON_stat_USE_INTERNAL_MAP
   CZString actualKey( key, CZString::noDuplication );
   Objectstats::const_iterator it = stat_.map_->find( actualKey );
   if ( it == stat_.map_->end() )
      return null;
   return (*it).second;
#else
   const stat *stat = stat_.map_->find( key );
   return stat ? *stat : null;
#endif
}


stat &
stat::operator[]( const std::string &key )
{
   return (*this)[ key.c_str() ];
}


const stat &
stat::operator[]( const std::string &key ) const
{
   return (*this)[ key.c_str() ];
}

stat &
stat::operator[]( const StaticString &key )
{
   return resolveReference( key, true );
}


# ifdef JSON_USE_CPPTL
stat &
stat::operator[]( const CppTL::ConstString &key )
{
   return (*this)[ key.c_str() ];
}


const stat &
stat::operator[]( const CppTL::ConstString &key ) const
{
   return (*this)[ key.c_str() ];
}
# endif


stat &
stat::append( const stat &stat )
{
   return (*this)[size()] = stat;
}


stat 
stat::get( const char *key, 
            const stat &defaultstat ) const
{
   const stat *stat = &((*this)[key]);
   return stat == &null ? defaultstat : *stat;
}


stat 
stat::get( const std::string &key,
            const stat &defaultstat ) const
{
   return get( key.c_str(), defaultstat );
}

stat
stat::removeMember( const char* key )
{
   JSON_ASSERT( type_ == nullstat  ||  type_ == objectstat );
   if ( type_ == nullstat )
      return null;
#ifndef JSON_stat_USE_INTERNAL_MAP
   CZString actualKey( key, CZString::noDuplication );
   Objectstats::iterator it = stat_.map_->find( actualKey );
   if ( it == stat_.map_->end() )
      return null;
   stat old(it->second);
   stat_.map_->erase(it);
   return old;
#else
   stat *stat = stat_.map_->find( key );
   if (stat){
      stat old(*stat);
      stat_.map_.remove( key );
      return old;
   } else {
      return null;
   }
#endif
}

stat
stat::removeMember( const std::string &key )
{
   return removeMember( key.c_str() );
}

# ifdef JSON_USE_CPPTL
stat 
stat::get( const CppTL::ConstString &key,
            const stat &defaultstat ) const
{
   return get( key.c_str(), defaultstat );
}
# endif

bool 
stat::isMember( const char *key ) const
{
   const stat *stat = &((*this)[key]);
   return stat != &null;
}


bool 
stat::isMember( const std::string &key ) const
{
   return isMember( key.c_str() );
}


# ifdef JSON_USE_CPPTL
bool 
stat::isMember( const CppTL::ConstString &key ) const
{
   return isMember( key.c_str() );
}
#endif

stat::Members 
stat::getMemberNames() const
{
   JSON_ASSERT( type_ == nullstat  ||  type_ == objectstat );
   if ( type_ == nullstat )
       return stat::Members();
   Members members;
   members.reserve( stat_.map_->size() );
#ifndef JSON_stat_USE_INTERNAL_MAP
   Objectstats::const_iterator it = stat_.map_->begin();
   Objectstats::const_iterator itEnd = stat_.map_->end();
   for ( ; it != itEnd; ++it )
      members.push_back( std::string( (*it).first.c_str() ) );
#else
   statInternalMap::IteratorState it;
   statInternalMap::IteratorState itEnd;
   stat_.map_->makeBeginIterator( it );
   stat_.map_->makeEndIterator( itEnd );
   for ( ; !statInternalMap::equals( it, itEnd ); statInternalMap::increment(it) )
      members.push_back( std::string( statInternalMap::key( it ) ) );
#endif
   return members;
}
//
//# ifdef JSON_USE_CPPTL
//EnumMemberNames
//stat::enumMemberNames() const
//{
//   if ( type_ == objectstat )
//   {
//      return CppTL::Enum::any(  CppTL::Enum::transform(
//         CppTL::Enum::keys( *(stat_.map_), CppTL::Type<const CZString &>() ),
//         MemberNamesTransform() ) );
//   }
//   return EnumMemberNames();
//}
//
//
//Enumstats 
//stat::enumstats() const
//{
//   if ( type_ == objectstat  ||  type_ == arraystat )
//      return CppTL::Enum::anystats( *(stat_.map_), 
//                                     CppTL::Type<const stat &>() );
//   return Enumstats();
//}
//
//# endif


bool
stat::isNull() const
{
   return type_ == nullstat;
}


bool 
stat::isBool() const
{
   return type_ == booleanstat;
}


bool 
stat::isInt() const
{
   return type_ == intstat;
}


bool 
stat::isUInt() const
{
   return type_ == uintstat;
}


bool 
stat::isIntegral() const
{
   return type_ == intstat  
          ||  type_ == uintstat  
          ||  type_ == booleanstat;
}


bool 
stat::isDouble() const
{
   return type_ == realstat;
}


bool 
stat::isNumeric() const
{
   return isIntegral() || isDouble();
}


bool 
stat::isString() const
{
   return type_ == stringstat;
}


bool 
stat::isArray() const
{
   return type_ == nullstat  ||  type_ == arraystat;
}


bool 
stat::isObject() const
{
   return type_ == nullstat  ||  type_ == objectstat;
}


void 
stat::setComment( const char *comment,
                   CommentPlacement placement )
{
   if ( !comments_ )
      comments_ = new CommentInfo[numberOfCommentPlacement];
   comments_[placement].setComment( comment );
}


void 
stat::setComment( const std::string &comment,
                   CommentPlacement placement )
{
   setComment( comment.c_str(), placement );
}


bool 
stat::hasComment( CommentPlacement placement ) const
{
   return comments_ != 0  &&  comments_[placement].comment_ != 0;
}

std::string 
stat::getComment( CommentPlacement placement ) const
{
   if ( hasComment(placement) )
      return comments_[placement].comment_;
   return "";
}


std::string 
stat::toStyledString() const
{
   StyledWriter writer;
   return writer.write( *this );
}


stat::const_iterator 
stat::begin() const
{
   switch ( type_ )
   {
#ifdef JSON_stat_USE_INTERNAL_MAP
   case arraystat:
      if ( stat_.array_ )
      {
         statInternalArray::IteratorState it;
         stat_.array_->makeBeginIterator( it );
         return const_iterator( it );
      }
      break;
   case objectstat:
      if ( stat_.map_ )
      {
         statInternalMap::IteratorState it;
         stat_.map_->makeBeginIterator( it );
         return const_iterator( it );
      }
      break;
#else
   case arraystat:
   case objectstat:
      if ( stat_.map_ )
         return const_iterator( stat_.map_->begin() );
      break;
#endif
   default:
      break;
   }
   return const_iterator();
}

stat::const_iterator 
stat::end() const
{
   switch ( type_ )
   {
#ifdef JSON_stat_USE_INTERNAL_MAP
   case arraystat:
      if ( stat_.array_ )
      {
         statInternalArray::IteratorState it;
         stat_.array_->makeEndIterator( it );
         return const_iterator( it );
      }
      break;
   case objectstat:
      if ( stat_.map_ )
      {
         statInternalMap::IteratorState it;
         stat_.map_->makeEndIterator( it );
         return const_iterator( it );
      }
      break;
#else
   case arraystat:
   case objectstat:
      if ( stat_.map_ )
         return const_iterator( stat_.map_->end() );
      break;
#endif
   default:
      break;
   }
   return const_iterator();
}


stat::iterator 
stat::begin()
{
   switch ( type_ )
   {
#ifdef JSON_stat_USE_INTERNAL_MAP
   case arraystat:
      if ( stat_.array_ )
      {
         statInternalArray::IteratorState it;
         stat_.array_->makeBeginIterator( it );
         return iterator( it );
      }
      break;
   case objectstat:
      if ( stat_.map_ )
      {
         statInternalMap::IteratorState it;
         stat_.map_->makeBeginIterator( it );
         return iterator( it );
      }
      break;
#else
   case arraystat:
   case objectstat:
      if ( stat_.map_ )
         return iterator( stat_.map_->begin() );
      break;
#endif
   default:
      break;
   }
   return iterator();
}

stat::iterator 
stat::end()
{
   switch ( type_ )
   {
#ifdef JSON_stat_USE_INTERNAL_MAP
   case arraystat:
      if ( stat_.array_ )
      {
         statInternalArray::IteratorState it;
         stat_.array_->makeEndIterator( it );
         return iterator( it );
      }
      break;
   case objectstat:
      if ( stat_.map_ )
      {
         statInternalMap::IteratorState it;
         stat_.map_->makeEndIterator( it );
         return iterator( it );
      }
      break;
#else
   case arraystat:
   case objectstat:
      if ( stat_.map_ )
         return iterator( stat_.map_->end() );
      break;
#endif
   default:
      break;
   }
   return iterator();
}


// class PathArgument
// //////////////////////////////////////////////////////////////////

PathArgument::PathArgument()
   : kind_( kindNone )
{
}


PathArgument::PathArgument( stat::UInt index )
   : index_( index )
   , kind_( kindIndex )
{
}


PathArgument::PathArgument( const char *key )
   : key_( key )
   , kind_( kindKey )
{
}


PathArgument::PathArgument( const std::string &key )
   : key_( key.c_str() )
   , kind_( kindKey )
{
}

// class Path
// //////////////////////////////////////////////////////////////////

Path::Path( const std::string &path,
            const PathArgument &a1,
            const PathArgument &a2,
            const PathArgument &a3,
            const PathArgument &a4,
            const PathArgument &a5 )
{
   InArgs in;
   in.push_back( &a1 );
   in.push_back( &a2 );
   in.push_back( &a3 );
   in.push_back( &a4 );
   in.push_back( &a5 );
   makePath( path, in );
}


void 
Path::makePath( const std::string &path,
                const InArgs &in )
{
   const char *current = path.c_str();
   const char *end = current + path.length();
   InArgs::const_iterator itInArg = in.begin();
   while ( current != end )
   {
      if ( *current == '[' )
      {
         ++current;
         if ( *current == '%' )
            addPathInArg( path, in, itInArg, PathArgument::kindIndex );
         else
         {
            stat::UInt index = 0;
            for ( ; current != end && *current >= '0'  &&  *current <= '9'; ++current )
               index = index * 10 + stat::UInt(*current - '0');
            args_.push_back( index );
         }
         if ( current == end  ||  *current++ != ']' )
            invalidPath( path, int(current - path.c_str()) );
      }
      else if ( *current == '%' )
      {
         addPathInArg( path, in, itInArg, PathArgument::kindKey );
         ++current;
      }
      else if ( *current == '.' )
      {
         ++current;
      }
      else
      {
         const char *beginName = current;
         while ( current != end  &&  !strchr( "[.", *current ) )
            ++current;
         args_.push_back( std::string( beginName, current ) );
      }
   }
}


void 
Path::addPathInArg( const std::string &path, 
                    const InArgs &in, 
                    InArgs::const_iterator &itInArg, 
                    PathArgument::Kind kind )
{
   if ( itInArg == in.end() )
   {
      // Error: missing argument %d
   }
   else if ( (*itInArg)->kind_ != kind )
   {
      // Error: bad argument type
   }
   else
   {
      args_.push_back( **itInArg );
   }
}


void 
Path::invalidPath( const std::string &path, 
                   int location )
{
   // Error: invalid path.
}


const stat &
Path::resolve( const stat &root ) const
{
   const stat *node = &root;
   for ( Args::const_iterator it = args_.begin(); it != args_.end(); ++it )
   {
      const PathArgument &arg = *it;
      if ( arg.kind_ == PathArgument::kindIndex )
      {
         if ( !node->isArray()  ||  node->isValidIndex( arg.index_ ) )
         {
            // Error: unable to resolve path (array stat expected at position...
         }
         node = &((*node)[arg.index_]);
      }
      else if ( arg.kind_ == PathArgument::kindKey )
      {
         if ( !node->isObject() )
         {
            // Error: unable to resolve path (object stat expected at position...)
         }
         node = &((*node)[arg.key_]);
         if ( node == &stat::null )
         {
            // Error: unable to resolve path (object has no member named '' at position...)
         }
      }
   }
   return *node;
}


stat 
Path::resolve( const stat &root, 
               const stat &defaultstat ) const
{
   const stat *node = &root;
   for ( Args::const_iterator it = args_.begin(); it != args_.end(); ++it )
   {
      const PathArgument &arg = *it;
      if ( arg.kind_ == PathArgument::kindIndex )
      {
         if ( !node->isArray()  ||  node->isValidIndex( arg.index_ ) )
            return defaultstat;
         node = &((*node)[arg.index_]);
      }
      else if ( arg.kind_ == PathArgument::kindKey )
      {
         if ( !node->isObject() )
            return defaultstat;
         node = &((*node)[arg.key_]);
         if ( node == &stat::null )
            return defaultstat;
      }
   }
   return *node;
}


stat &
Path::make( stat &root ) const
{
   stat *node = &root;
   for ( Args::const_iterator it = args_.begin(); it != args_.end(); ++it )
   {
      const PathArgument &arg = *it;
      if ( arg.kind_ == PathArgument::kindIndex )
      {
         if ( !node->isArray() )
         {
            // Error: node is not an array at position ...
         }
         node = &((*node)[arg.index_]);
      }
      else if ( arg.kind_ == PathArgument::kindKey )
      {
         if ( !node->isObject() )
         {
            // Error: node is not an object at position...
         }
         node = &((*node)[arg.key_]);
      }
   }
   return *node;
}


} // namespace Json
