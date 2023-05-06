#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>
using std::log10;

// HugeInt class definition
class HugeInt
{
public:
   // returns true if and only if the specified huge integer is zero
   bool isZero();

   // return true if and only if hugeInt1 == hugeInt2
   bool equal( const HugeInt &hugeInt2 );

   // returns true if and only if hugeInt1 < hugeInt2
   bool less( const HugeInt &hugeInt2 );

   // --hugeInt
   void decrement();

   // minuend -= subtrahend provided that minuend > subtrahend
   void subtraAssign( const HugeInt &subtrahend );

   // multiplicand *= multiplier
   void multiAssign( const HugeInt &multiplier );

   // quotient = dividend / divisor; remainder = dividend % divisor
   void division( const HugeInt &divisor, HugeInt &quotient, HugeInt &remainder );

   // hugeInt /= 10, or equivalently, shifts right by one position
   void divideBy10();

   // hugeInt1 = hugeInt2
   void assign( const HugeInt &hugeInt2 );

   void reset();
   
   void output();

   int size = 1;       // the number of digits of the integer; it can never be zero
   int *ptr = new int[ 1 ](); // used to store a nonnegative integer, one digit per element
};

const int maxSize = 200;

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
         HugeInt dividend;
         HugeInt divisor;
         HugeInt quotient;
         HugeInt remainder;

         // put all digits of t into base
         HugeInt base;
         delete[] base.ptr;
         base.ptr = new int[ 10 ]();
         base.size = 0;
         for( int i = t; i > 0; i /= 10 )
            base.ptr[ base.size++ ] = i % 10;

         // dividend = pow( t, a )
         dividend.ptr[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            dividend.multiAssign( base );
            if( dividend.size > maxSize - base.size )
               break;
         }

         if( dividend.size > maxSize - base.size )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            // divisor = pow( t, b )
            divisor.ptr[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
            {
               divisor.multiAssign( base );
               if( divisor.size > maxSize - base.size )
                  break;
            }

            if( divisor.size > maxSize - base.size )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               dividend.decrement(); // --dividend
               divisor.decrement();   // --divisor

               dividend.division( divisor, quotient, remainder );

               if( quotient.size > 1 && quotient.ptr[ quotient.size - 1 ] == 0 )
                  cout << "quotient has a leading zero!\n";

               if( remainder.size > 1 && remainder.ptr[ remainder.size - 1 ] == 0 )
                  cout << "remainder has a leading zero!\n";

               // quotient is an integer with less than 100 digits
               if( quotient.size < 100 && remainder.isZero() )
                  for( int i = quotient.size - 1; i >= 0; i-- )
                     cout << quotient.ptr[ i ];
               else
                  cout << "is not an integer with less than 100 digits.";
               cout << endl;
            }
         }

         delete[] dividend.ptr;
         delete[] divisor.ptr;
         delete[] quotient.ptr;
         delete[] remainder.ptr;
      }
   }

   system( "pause" );
}

// returns true if and only if the specified huge integer is zero
bool HugeInt::isZero()
{
   return ( size == 1 && ptr[ 0 ] == 0 );
}

// return true if and only if hugeInt1 == hugeInt2
bool HugeInt::equal( const HugeInt &hugeInt2 )
{
   if( size != hugeInt2.size )
      return false;

   for( int i = size - 1; i >= 0; i-- )
      if( ptr[ i ] != hugeInt2.ptr[ i ] )
         return false;

   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool HugeInt::less( const HugeInt &hugeInt2 )
{
    if (size < hugeInt2.size) 
        return true;
    else if (size > hugeInt2.size)
        return false;
    else {
        for (int i = size - 1; i >= 0; i--) {
            if (ptr[i] < hugeInt2.ptr[i])
                return true;
            else if (ptr[i] > hugeInt2.ptr[i])
                return false;
        }
        return false;
    }
}

void HugeInt::output() {
    for (int i = size - 1; i >= 0; i--)
        cout << ptr[i];
    cout << endl;
}

// --hugeInt
void HugeInt::decrement()
{
   HugeInt one;
   one.ptr[ 0 ] = 1;
   subtraAssign( one );
   delete[] one.ptr;
}

// minuend -= subtrahend provided that minuend > subtrahend
void HugeInt::subtraAssign( const HugeInt &subtrahend )
{
   if( equal( subtrahend ) )
   {
      reset();
      return;
   }
   HugeInt difference;
   difference.assign(*this); //difference = minued

   for (int i = subtrahend.size - 1; i >= 0; i--) //difference -= subtrahend
       difference.ptr[i] -= subtrahend.ptr[i];
   
   for (int i = 0; i < difference.size - 1; i++) { //check °h¦ì
       if (difference.ptr[i] < 0) {
           difference.ptr[i] += 10;
           difference.ptr[i + 1] -= 1;
       }
   }

   while(difference.size > 1 && difference.ptr[difference.size - 1] == 0) //check 0
       difference.size--;

   if( difference.size > 1 && difference.ptr[ difference.size - 1 ] == 0 )
      cout << "difference has a leading zero!\n";

   assign( difference ); // minuend = difference

   delete[] difference.ptr;
}

// multiplicand *= multiplier
void HugeInt::multiAssign( const HugeInt &multiplier )
{
   HugeInt product;
   product.size = size + multiplier.size; //preset maxsize
   delete[] product.ptr;
   product.ptr = new int[product.size]();
   for (int i = 0; i < size; i++) {
       for (int j = 0; j < multiplier.size; j++)
           product.ptr[i + j] += ptr[i] * multiplier.ptr[j];
   }

   for (int i = 0; i < product.size - 1; i++) { //check over10
       if (product.ptr[i] > 9) {
           product.ptr[i + 1] += product.ptr[i] / 10;
           product.ptr[i] %= 10;          
       }
   }

   if (product.size > 1 && product.ptr[product.size - 1] == 0)
       product.size--;

   if( product.size > 1 && product.ptr[ product.size - 1 ] == 0 )
      cout << "product has a leading zero!\n";

   assign( product ); // *this = product

   delete[] product.ptr;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void HugeInt::division( const HugeInt &divisor, HugeInt &quotient, HugeInt &remainder )
{
   remainder.assign( *this ); // remainder = dividend

   if( less( divisor ) )
      quotient.reset();
   else
   {
      HugeInt buffer;
      buffer.size = size;
      delete[] buffer.ptr;
      buffer.ptr = new int[ buffer.size ]();
      int n = size - divisor.size;
      for (int i = buffer.size - 1; i >= n; i--)
          buffer.ptr[i] = divisor.ptr[i - n];
      
      quotient.size = size - divisor.size;
      if (less(buffer)) //dividend < buffer
           buffer.divideBy10();
      else
          quotient.size++;
      delete[] quotient.ptr;
      quotient.ptr = new int [quotient.size]();
      
      for (int k = quotient.size - 1; k >= 0; k--) {
          while (!remainder.less(buffer)) { //remainder >= buffer
              remainder.subtraAssign(buffer);
              quotient.ptr[k]++;
              if (remainder.isZero()) //over
                  break;
          }
          buffer.divideBy10();
      }

      delete[] buffer.ptr;
   }
}

// hugeInt /= 10, or equivalently, shifts right by one position
void HugeInt::divideBy10()
{
   if( size == 1 )
      ptr[ 0 ] = 0;
   else
   {
      HugeInt buffer;
      buffer.assign( *this ); // buffer = *this

      size--;
      delete[] ptr;
      ptr = new int[ size ]();

      for( int i = 1; i <= size; i++ )
         ptr[ i - 1 ] = buffer.ptr[ i ];
   }
}

// hugeInt1 = hugeInt2; assignment
void HugeInt::assign( const HugeInt &hugeInt2 )
{
   size = hugeInt2.size;
   delete[] ptr;
   ptr = new int[ size ];
   for( int i = 0; i < size; i++ )
      ptr[ i ] = hugeInt2.ptr[ i ];
}

void HugeInt::reset()
{
   size = 1;
   delete[] ptr;
   ptr = new int[ 1 ]();
}