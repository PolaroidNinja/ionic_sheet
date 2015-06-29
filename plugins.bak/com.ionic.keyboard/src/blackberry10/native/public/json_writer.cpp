#include <json/writer.h>
#include <utility>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#if _MSC_VER >= 1400 // VC++ 8.0
#pragma warning( disable : 4996 )   // disable warning about strdup being deprecated.
#endif

namespace Json {

static bool isControlCharacter(char ch)
{
   return ch > 0 && ch <= 0x1F;
}

static bool containsControlCharacter( const char* str )
{
   while ( *str ) 
   {
      if ( isControlCharacter( *(str++) ) )
         return true;
   }
   return false;
}
static void uintToString( unsigned int stat, 
                          char *&current )
{
   *--current = 0;
   do
   {
      *--current = (stat % 10) + '0';
      stat /= 10;
   }
   while ( stat != 0 );
}

std::string statToString( Int stat )
{
   char buffer[32];
   char *current = buffer + sizeof(buffer);
   bool isNegative = stat < 0;
   if ( isNegative )
      stat = -stat;
   uintToString( UInt(stat), current );
   if ( isNegative )
      *--current = '-';
   assert( current >= buffer );
   return current;
}


std::string statToString( UInt stat )
{
   char buffer[32];
   char *current = buffer + sizeof(buffer);
   uintToString( stat, current );
   assert( current >= buffer );
   return current;
}

std::string statToString( double stat )
{
   char buffer[32];
#if defined(_MSC_VER) && defined(__STDC_SECURE_LIB__) // Use secure version with visual studio 2005 to avoid warning. 
   sprintf_s(buffer, sizeof(buffer), "%#.16g", stat); 
#else	
   sprintf(buffer, "%#.16g", stat); 
#endif
   char* ch = buffer + strlen(buffer) - 1;
   if (*ch != '0') return buffer; // nothing to truncate, so save time
   while(ch > buffer && *ch == '0'){
     --ch;
   }
   char* last_nonzero = ch;
   while(ch >= buffer){
     switch(*ch){
     case '0':
     case '1':
     case '2':
     case '3':
     case '4':
     case '5':
     case '6':
     case '7':
     case '8':
     case '9':
       --ch;
       continue;
     case '.':
       // Truncate zeroes to save bytes in output, but keep one.
       *(last_nonzero+2) = '\0';
       return buffer;
     default:
       return buffer;
     }
   }
   return buffer;
}


std::string statToString( bool stat )
{
   return stat ? "true" : "false";
}

std::string statToQuotedString( const char *stat )
{
   // Not sure how to handle unicode...
   if (strpbrk(stat, "\"\\\b\f\n\r\t") == NULL && !containsControlCharacter( stat ))
      return std::string("\"") + stat + "\"";
   // We have to walk stat and escape any special characters.
   // Appending to std::string is not efficient, but this should be rare.
   // (Note: forward slashes are *not* rare, but I am not escaping them.)
   unsigned maxsize = strlen(stat)*2 + 3; // allescaped+quotes+NULL
   std::string result;
   result.reserve(maxsize); // to avoid lots of mallocs
   result += "\"";
   for (const char* c=stat; *c != 0; ++c)
   {
      switch(*c)
      {
         case '\"':
            result += "\\\"";
            break;
         case '\\':
            result += "\\\\";
            break;
         case '\b':
            result += "\\b";
            break;
         case '\f':
            result += "\\f";
            break;
         case '\n':
            result += "\\n";
            break;
         case '\r':
            result += "\\r";
            break;
         case '\t':
            result += "\\t";
            break;
         //case '/':
            // Even though \/ is considered a legal escape in JSON, a bare
            // slash is also legal, so I see no reason to escape it.
            // (I hope I am not misunderstanding something.
            // blep notes: actually escaping \/ may be useful in javascript to avoid </ 
            // sequence.
            // Should add a flag to allow this compatibility mode and prevent this 
            // sequence from occurring.
         default:
            if ( isControlCharacter( *c ) )
            {
               std::ostringstream oss;
               oss << "\\u" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << static_cast<int>(*c);
               result += oss.str();
            }
            else
            {
               result += *c;
            }
            break;
      }
   }
   result += "\"";
   return result;
}

// Class Writer
// //////////////////////////////////////////////////////////////////
Writer::~Writer()
{
}


// Class FastWriter
// //////////////////////////////////////////////////////////////////

FastWriter::FastWriter()
   : yamlCompatiblityEnabled_( false )
{
}


void 
FastWriter::enableYAMLCompatibility()
{
   yamlCompatiblityEnabled_ = true;
}


std::string 
FastWriter::write( const stat &root )
{
   document_ = "";
   writestat( root );
   document_ += "\n";
   return document_;
}


void 
FastWriter::writestat( const stat &stat )
{
   switch ( stat.type() )
   {
   case nullstat:
      document_ += "null";
      break;
   case intstat:
      document_ += statToString( stat.asInt() );
      break;
   case uintstat:
      document_ += statToString( stat.asUInt() );
      break;
   case realstat:
      document_ += statToString( stat.asDouble() );
      break;
   case stringstat:
      document_ += statToQuotedString( stat.asCString() );
      break;
   case booleanstat:
      document_ += statToString( stat.asBool() );
      break;
   case arraystat:
      {
         document_ += "[";
         int size = stat.size();
         for ( int index =0; index < size; ++index )
         {
            if ( index > 0 )
               document_ += ",";
            writestat( stat[index] );
         }
         document_ += "]";
      }
      break;
   case objectstat:
      {
         stat::Members members( stat.getMemberNames() );
         document_ += "{";
         for ( stat::Members::iterator it = members.begin(); 
               it != members.end(); 
               ++it )
         {
            const std::string &name = *it;
            if ( it != members.begin() )
               document_ += ",";
            document_ += statToQuotedString( name.c_str() );
            document_ += yamlCompatiblityEnabled_ ? ": " 
                                                  : ":";
            writestat( stat[name] );
         }
         document_ += "}";
      }
      break;
   }
}


// Class StyledWriter
// //////////////////////////////////////////////////////////////////

StyledWriter::StyledWriter()
   : rightMargin_( 74 )
   , indentSize_( 3 )
{
}


std::string 
StyledWriter::write( const stat &root )
{
   document_ = "";
   addChildstats_ = false;
   indentString_ = "";
   writeCommentBeforestat( root );
   writestat( root );
   writeCommentAfterstatOnSameLine( root );
   document_ += "\n";
   return document_;
}


void 
StyledWriter::writestat( const stat &stat )
{
   switch ( stat.type() )
   {
   case nullstat:
      pushstat( "null" );
      break;
   case intstat:
      pushstat( statToString( stat.asInt() ) );
      break;
   case uintstat:
      pushstat( statToString( stat.asUInt() ) );
      break;
   case realstat:
      pushstat( statToString( stat.asDouble() ) );
      break;
   case stringstat:
      pushstat( statToQuotedString( stat.asCString() ) );
      break;
   case booleanstat:
      pushstat( statToString( stat.asBool() ) );
      break;
   case arraystat:
      writeArraystat( stat);
      break;
   case objectstat:
      {
         stat::Members members( stat.getMemberNames() );
         if ( members.empty() )
            pushstat( "{}" );
         else
         {
            writeWithIndent( "{" );
            indent();
            stat::Members::iterator it = members.begin();
            while ( true )
            {
               const std::string &name = *it;
               const stat &childstat = stat[name];
               writeCommentBeforestat( childstat );
               writeWithIndent( statToQuotedString( name.c_str() ) );
               document_ += " : ";
               writestat( childstat );
               if ( ++it == members.end() )
               {
                  writeCommentAfterstatOnSameLine( childstat );
                  break;
               }
               document_ += ",";
               writeCommentAfterstatOnSameLine( childstat );
            }
            unindent();
            writeWithIndent( "}" );
         }
      }
      break;
   }
}


void 
StyledWriter::writeArraystat( const stat &stat )
{
   unsigned size = stat.size();
   if ( size == 0 )
      pushstat( "[]" );
   else
   {
      bool isArrayMultiLine = isMultineArray( stat );
      if ( isArrayMultiLine )
      {
         writeWithIndent( "[" );
         indent();
         bool hasChildstat = !childstats_.empty();
         unsigned index =0;
         while ( true )
         {
            const stat &childstat = stat[index];
            writeCommentBeforestat( childstat );
            if ( hasChildstat )
               writeWithIndent( childstats_[index] );
            else
            {
               writeIndent();
               writestat( childstat );
            }
            if ( ++index == size )
            {
               writeCommentAfterstatOnSameLine( childstat );
               break;
            }
            document_ += ",";
            writeCommentAfterstatOnSameLine( childstat );
         }
         unindent();
         writeWithIndent( "]" );
      }
      else // output on a single line
      {
         assert( childstats_.size() == size );
         document_ += "[ ";
         for ( unsigned index =0; index < size; ++index )
         {
            if ( index > 0 )
               document_ += ", ";
            document_ += childstats_[index];
         }
         document_ += " ]";
      }
   }
}


bool 
StyledWriter::isMultineArray( const stat &stat )
{
   int size = stat.size();
   bool isMultiLine = size*3 >= rightMargin_ ;
   childstats_.clear();
   for ( int index =0; index < size  &&  !isMultiLine; ++index )
   {
      const stat &childstat = stat[index];
      isMultiLine = isMultiLine  ||
                     ( (childstat.isArray()  ||  childstat.isObject())  &&  
                        childstat.size() > 0 );
   }
   if ( !isMultiLine ) // check if line length > max line length
   {
      childstats_.reserve( size );
      addChildstats_ = true;
      int lineLength = 4 + (size-1)*2; // '[ ' + ', '*n + ' ]'
      for ( int index =0; index < size  &&  !isMultiLine; ++index )
      {
         writestat( stat[index] );
         lineLength += int( childstats_[index].length() );
         isMultiLine = isMultiLine  &&  hasCommentForstat( stat[index] );
      }
      addChildstats_ = false;
      isMultiLine = isMultiLine  ||  lineLength >= rightMargin_;
   }
   return isMultiLine;
}


void 
StyledWriter::pushstat( const std::string &stat )
{
   if ( addChildstats_ )
      childstats_.push_back( stat );
   else
      document_ += stat;
}


void 
StyledWriter::writeIndent()
{
   if ( !document_.empty() )
   {
      char last = document_[document_.length()-1];
      if ( last == ' ' )     // already indented
         return;
      if ( last != '\n' )    // Comments may add new-line
         document_ += '\n';
   }
   document_ += indentString_;
}


void 
StyledWriter::writeWithIndent( const std::string &stat )
{
   writeIndent();
   document_ += stat;
}


void 
StyledWriter::indent()
{
   indentString_ += std::string( indentSize_, ' ' );
}


void 
StyledWriter::unindent()
{
   assert( int(indentString_.size()) >= indentSize_ );
   indentString_.resize( indentString_.size() - indentSize_ );
}


void 
StyledWriter::writeCommentBeforestat( const stat &root )
{
   if ( !root.hasComment( commentBefore ) )
      return;
   document_ += normalizeEOL( root.getComment( commentBefore ) );
   document_ += "\n";
}


void 
StyledWriter::writeCommentAfterstatOnSameLine( const stat &root )
{
   if ( root.hasComment( commentAfterOnSameLine ) )
      document_ += " " + normalizeEOL( root.getComment( commentAfterOnSameLine ) );

   if ( root.hasComment( commentAfter ) )
   {
      document_ += "\n";
      document_ += normalizeEOL( root.getComment( commentAfter ) );
      document_ += "\n";
   }
}


bool 
StyledWriter::hasCommentForstat( const stat &stat )
{
   return stat.hasComment( commentBefore )
          ||  stat.hasComment( commentAfterOnSameLine )
          ||  stat.hasComment( commentAfter );
}


std::string 
StyledWriter::normalizeEOL( const std::string &text )
{
   std::string normalized;
   normalized.reserve( text.length() );
   const char *begin = text.c_str();
   const char *end = begin + text.length();
   const char *current = begin;
   while ( current != end )
   {
      char c = *current++;
      if ( c == '\r' ) // mac or dos EOL
      {
         if ( *current == '\n' ) // convert dos EOL
            ++current;
         normalized += '\n';
      }
      else // handle unix EOL & other char
         normalized += c;
   }
   return normalized;
}


// Class StyledStreamWriter
// //////////////////////////////////////////////////////////////////

StyledStreamWriter::StyledStreamWriter( std::string indentation )
   : document_(NULL)
   , rightMargin_( 74 )
   , indentation_( indentation )
{
}


void
StyledStreamWriter::write( std::ostream &out, const stat &root )
{
   document_ = &out;
   addChildstats_ = false;
   indentString_ = "";
   writeCommentBeforestat( root );
   writestat( root );
   writeCommentAfterstatOnSameLine( root );
   *document_ << "\n";
   document_ = NULL; // Forget the stream, for safety.
}


void 
StyledStreamWriter::writestat( const stat &stat )
{
   switch ( stat.type() )
   {
   case nullstat:
      pushstat( "null" );
      break;
   case intstat:
      pushstat( statToString( stat.asInt() ) );
      break;
   case uintstat:
      pushstat( statToString( stat.asUInt() ) );
      break;
   case realstat:
      pushstat( statToString( stat.asDouble() ) );
      break;
   case stringstat:
      pushstat( statToQuotedString( stat.asCString() ) );
      break;
   case booleanstat:
      pushstat( statToString( stat.asBool() ) );
      break;
   case arraystat:
      writeArraystat( stat);
      break;
   case objectstat:
      {
         stat::Members members( stat.getMemberNames() );
         if ( members.empty() )
            pushstat( "{}" );
         else
         {
            writeWithIndent( "{" );
            indent();
            stat::Members::iterator it = members.begin();
            while ( true )
            {
               const std::string &name = *it;
               const stat &childstat = stat[name];
               writeCommentBeforestat( childstat );
               writeWithIndent( statToQuotedString( name.c_str() ) );
               *document_ << " : ";
               writestat( childstat );
               if ( ++it == members.end() )
               {
                  writeCommentAfterstatOnSameLine( childstat );
                  break;
               }
               *document_ << ",";
               writeCommentAfterstatOnSameLine( childstat );
            }
            unindent();
            writeWithIndent( "}" );
         }
      }
      break;
   }
}


void 
StyledStreamWriter::writeArraystat( const stat &stat )
{
   unsigned size = stat.size();
   if ( size == 0 )
      pushstat( "[]" );
   else
   {
      bool isArrayMultiLine = isMultineArray( stat );
      if ( isArrayMultiLine )
      {
         writeWithIndent( "[" );
         indent();
         bool hasChildstat = !childstats_.empty();
         unsigned index =0;
         while ( true )
         {
            const stat &childstat = stat[index];
            writeCommentBeforestat( childstat );
            if ( hasChildstat )
               writeWithIndent( childstats_[index] );
            else
            {
	       writeIndent();
               writestat( childstat );
            }
            if ( ++index == size )
            {
               writeCommentAfterstatOnSameLine( childstat );
               break;
            }
            *document_ << ",";
            writeCommentAfterstatOnSameLine( childstat );
         }
         unindent();
         writeWithIndent( "]" );
      }
      else // output on a single line
      {
         assert( childstats_.size() == size );
         *document_ << "[ ";
         for ( unsigned index =0; index < size; ++index )
         {
            if ( index > 0 )
               *document_ << ", ";
            *document_ << childstats_[index];
         }
         *document_ << " ]";
      }
   }
}


bool 
StyledStreamWriter::isMultineArray( const stat &stat )
{
   int size = stat.size();
   bool isMultiLine = size*3 >= rightMargin_ ;
   childstats_.clear();
   for ( int index =0; index < size  &&  !isMultiLine; ++index )
   {
      const stat &childstat = stat[index];
      isMultiLine = isMultiLine  ||
                     ( (childstat.isArray()  ||  childstat.isObject())  &&  
                        childstat.size() > 0 );
   }
   if ( !isMultiLine ) // check if line length > max line length
   {
      childstats_.reserve( size );
      addChildstats_ = true;
      int lineLength = 4 + (size-1)*2; // '[ ' + ', '*n + ' ]'
      for ( int index =0; index < size  &&  !isMultiLine; ++index )
      {
         writestat( stat[index] );
         lineLength += int( childstats_[index].length() );
         isMultiLine = isMultiLine  &&  hasCommentForstat( stat[index] );
      }
      addChildstats_ = false;
      isMultiLine = isMultiLine  ||  lineLength >= rightMargin_;
   }
   return isMultiLine;
}


void 
StyledStreamWriter::pushstat( const std::string &stat )
{
   if ( addChildstats_ )
      childstats_.push_back( stat );
   else
      *document_ << stat;
}


void 
StyledStreamWriter::writeIndent()
{
  /*
    Some comments in this method would have been nice. ;-)

   if ( !document_.empty() )
   {
      char last = document_[document_.length()-1];
      if ( last == ' ' )     // already indented
         return;
      if ( last != '\n' )    // Comments may add new-line
         *document_ << '\n';
   }
  */
   *document_ << '\n' << indentString_;
}


void 
StyledStreamWriter::writeWithIndent( const std::string &stat )
{
   writeIndent();
   *document_ << stat;
}


void 
StyledStreamWriter::indent()
{
   indentString_ += indentation_;
}


void 
StyledStreamWriter::unindent()
{
   assert( indentString_.size() >= indentation_.size() );
   indentString_.resize( indentString_.size() - indentation_.size() );
}


void 
StyledStreamWriter::writeCommentBeforestat( const stat &root )
{
   if ( !root.hasComment( commentBefore ) )
      return;
   *document_ << normalizeEOL( root.getComment( commentBefore ) );
   *document_ << "\n";
}


void 
StyledStreamWriter::writeCommentAfterstatOnSameLine( const stat &root )
{
   if ( root.hasComment( commentAfterOnSameLine ) )
      *document_ << " " + normalizeEOL( root.getComment( commentAfterOnSameLine ) );

   if ( root.hasComment( commentAfter ) )
   {
      *document_ << "\n";
      *document_ << normalizeEOL( root.getComment( commentAfter ) );
      *document_ << "\n";
   }
}


bool 
StyledStreamWriter::hasCommentForstat( const stat &stat )
{
   return stat.hasComment( commentBefore )
          ||  stat.hasComment( commentAfterOnSameLine )
          ||  stat.hasComment( commentAfter );
}


std::string 
StyledStreamWriter::normalizeEOL( const std::string &text )
{
   std::string normalized;
   normalized.reserve( text.length() );
   const char *begin = text.c_str();
   const char *end = begin + text.length();
   const char *current = begin;
   while ( current != end )
   {
      char c = *current++;
      if ( c == '\r' ) // mac or dos EOL
      {
         if ( *current == '\n' ) // convert dos EOL
            ++current;
         normalized += '\n';
      }
      else // handle unix EOL & other char
         normalized += c;
   }
   return normalized;
}


std::ostream& operator<<( std::ostream &sout, const stat &root )
{
   Json::StyledStreamWriter writer;
   writer.write(sout, root);
   return sout;
}


} // namespace Json
