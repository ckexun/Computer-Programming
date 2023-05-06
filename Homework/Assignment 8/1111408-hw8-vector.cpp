#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>
using std::log10;

#include <vector>
using std::vector;

// returns true if and only if the specified huge integer is zero
bool isZero( const vector< int > &hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( const vector< int > &hugeInt1, const vector< int > &hugeInt2 );

// returns true if and only if hugeInt1 < hugeInt2
bool less( const vector< int > &hugeInt1, const vector< int > &hugeInt2 );

// --hugeInt
void decrement( vector< int > &hugeInt );

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( vector< int > &minuend, const vector< int > &subtrahend );

// multiplicand *= multiplier
void multiplication( vector< int > &multiplicand, const vector< int > &multiplier );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( const vector< int > &dividend, const vector< int > &divisor,
               vector< int > &quotient, vector< int > &remainder );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( vector< int > &hugeInt );

const int arraySize = 200;

int main()
{
   int t, a, b;
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         vector< int > dividend( 1 );
         vector< int > divisor( 1 );
         vector< int > quotient( 1 );
         vector< int > remainder( 1 );

         // put all digits of t into base
         vector< int > base;
         for( int i = t; i > 0; i /= 10 )
            base.push_back( i % 10 );

         // dividend = pow( t, a )
         dividend[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiplication( dividend, base );
            if( dividend.size() > arraySize - base.size() )
               break;
         }

         if( dividend.size() > arraySize - base.size() )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            // divisor = pow( t, b )
            divisor[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
            {
               multiplication( divisor, base );
               if( divisor.size() > arraySize - base.size() )
                  break;
            }

            if( divisor.size() > arraySize - base.size() )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               decrement( dividend ); // --dividend           
               decrement( divisor );   // --divisor

               division( dividend, divisor, quotient, remainder );

               // quotient is an integer with less than 100 digits
               if( quotient.size() < 100 && isZero( remainder ) )
                  for( int i = quotient.size() - 1; i >= 0; i-- )
                     cout << quotient[ i ];
               else
                  cout << "is not an integer with less than 100 digits.";
               cout << endl;
            }
         }
      }
   }
}

// returns true if and only if the specified huge integer is zero
bool isZero( const vector< int > &hugeInt )
{
   return ( hugeInt.size() == 1 && hugeInt[ 0 ] == 0 );
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( const vector< int > &hugeInt1, const vector< int > &hugeInt2 )
{
   if( hugeInt1.size() != hugeInt2.size() )
      return false;

   for( int i = hugeInt1.size() - 1; i >= 0; i-- )
      if( hugeInt1[ i ] != hugeInt2[ i ] )
         return false;

   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( const vector< int > &hugeInt1, const vector< int > &hugeInt2 )
{
    if (hugeInt1.size() > hugeInt2.size())
        return false;
    else if (hugeInt1.size() < hugeInt2.size())
        return true;
    else{
        for (int i = hugeInt1.size() - 1; i >= 0; i--) {
            if (hugeInt1[i] > hugeInt2[i])
                return false;
            else if (hugeInt1[i] < hugeInt2[i])
                return true;
        }
        return false;
    }
}

// --hugeInt
void decrement( vector< int > &hugeInt )
{
   vector< int > one( 1 );
   one[ 0 ] = 1;
   subtraAssign( hugeInt, one );
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( vector< int > &minuend, const vector< int > &subtrahend )
{
   if( equal( minuend, subtrahend ) )
   {
      minuend.resize( 1 );
      minuend[ 0 ] = 0;
      return;
   }

   for (int i = subtrahend.size() - 1; i >= 0; i--)
       minuend[i] -= subtrahend[i];
   for (int i = 0; i < minuend.size() - 1; i++) {
       if (minuend[i] < 0) {
           minuend[i] += 10;
           minuend[i + 1] -= 1;
       }
   }

   int minuendSize = minuend.size();
   while (minuendSize > 1 && minuend[minuendSize - 1] == 0)
       minuendSize--;

   minuend.resize( minuendSize );
}

// multiplicand *= multiplier
void multiplication( vector< int > &multiplicand, const vector< int > &multiplier )
{
   int multiplicandSize = multiplicand.size();
   int multiplierSize = multiplier.size();
   vector< int > product( multiplicandSize + multiplierSize ); //set maxSize
   for (int i = 0; i < multiplicand.size(); i++) {
       for (int j = 0; j < multiplier.size(); j++) 
           product[i + j] += multiplicand[i] * multiplier[j];      
   }

   for (int i = 0; i < product.size() - 1; i++) {
       if (product[i] > 9) {
           product[i + 1] += product[i] / 10;
           product[i] %= 10;
       }
   }
   int productSize = product.size();

   if( product[ productSize - 1 ] == 0 )
      product.pop_back();

   multiplicand = product;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( const vector< int > &dividend, const vector< int > &divisor,
               vector< int > &quotient, vector< int > &remainder )
{
   remainder = dividend;

   if( less( dividend, divisor ) )
      quotient.resize( 1 );
   else
   {
      int dividendSize = dividend.size();
      int divisorSize = divisor.size();
      int quotientSize = dividendSize - divisorSize;
      vector< int > buffer( dividendSize );
      int n = dividendSize - divisorSize;

      for (int i = buffer.size() - 1; i >= n; i--)
          buffer[i] = divisor[i - n];
      if (less(dividend, buffer))
          divideBy10(buffer);
      else
          quotientSize++;
      quotient.resize(quotientSize);

      for (int k = quotientSize - 1; k >= 0; k--) {
          while (!less(remainder, buffer)) {
              subtraAssign(remainder, buffer);
              quotient[k]++;
              if (isZero(remainder))
                  break;
          }         
          divideBy10(buffer);
      }
   }
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( vector< int > &hugeInt )
{
   if( hugeInt.size() == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      int size = hugeInt.size();
      for( int i = 1; i < size; i++ )
         hugeInt[ i - 1 ] = hugeInt[ i ];

      hugeInt.pop_back();
   }
}