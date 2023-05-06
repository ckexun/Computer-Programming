#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>
using std::log10;

// HugeInt struct definition
struct HugeInt
{
   int size = 1;       // the number of digits of the integer; it can never be zero
   int *ptr = new int[ 1 ](); // used to store a nonnegative integer, one digit per element
};

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt hugeInt1, HugeInt hugeInt2 );

// returns true if and only if hugeInt1 < hugeInt2
bool less( HugeInt hugeInt1, HugeInt hugeInt2 );

// --hugeInt
void decrement( HugeInt &hugeInt );

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( HugeInt &minuend, HugeInt subtrahend );

// multiplicand *= multiplier
void multiAssign( HugeInt &multiplicand, HugeInt multiplier );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( HugeInt dividend, HugeInt divisor, HugeInt &quotient, HugeInt &remainder );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( HugeInt &hugeInt );

// hugeInt1 = hugeInt2
void assign( HugeInt &hugeInt1, HugeInt hugeInt2 );

void reset( HugeInt &hugeInt );

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
            multiAssign( dividend, base );
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
               multiAssign( divisor, base );
               if( divisor.size > maxSize - base.size )
                  break;
            }

            if( divisor.size > maxSize - base.size )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               decrement( dividend ); // --dividend
               decrement( divisor );   // --divisor

               division( dividend, divisor, quotient, remainder );

               if( quotient.size > 1 && quotient.ptr[ quotient.size - 1 ] == 0 )
                  cout << "quotient has a leading zero!\n";

               if( remainder.size > 1 && remainder.ptr[ remainder.size - 1 ] == 0 )
                  cout << "remainder has a leading zero!\n";

               // quotient is an integer with less than 100 digits
               if( quotient.size < 100 && isZero( remainder ) )
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
bool isZero( HugeInt hugeInt )
{
   return ( hugeInt.size == 1 && hugeInt.ptr[ 0 ] == 0 );
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt hugeInt1, HugeInt hugeInt2 )
{
   if( hugeInt1.size != hugeInt2.size )
      return false;

   for( int i = hugeInt1.size - 1; i >= 0; i-- )
      if( hugeInt1.ptr[ i ] != hugeInt2.ptr[ i ] )
         return false;

   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( HugeInt hugeInt1, HugeInt hugeInt2 )
{
    if (hugeInt1.size > hugeInt2.size)
        return false;
    else if (hugeInt1.size < hugeInt2.size)
        return true;
    else {
        for (int i = hugeInt1.size - 1; i >= 0; i--) {
            if (hugeInt1.ptr[i] > hugeInt2.ptr[i])
                return false;
            else if (hugeInt1.ptr[i] < hugeInt2.ptr[i])
                return true;
        }
        return false;
    }
}

// --hugeInt
void decrement( HugeInt &hugeInt )
{
    hugeInt.ptr[0] -= 1;
    
    for (int i = 0; i < hugeInt.size; i++) {
        if (hugeInt.ptr[i] < 0) {
            hugeInt.ptr[i] += 10;
            hugeInt.ptr[i + 1] -= 1;
        }
    }
    if (hugeInt.size > 0 && hugeInt.ptr[hugeInt.size - 1] == 0)
        hugeInt.size--;
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( HugeInt &minuend, HugeInt subtrahend )
{
   if( equal( minuend, subtrahend ) )
   {
      reset( minuend );
      return;
   }
   
   HugeInt difference;
   assign(difference, minuend);
   for (int i = 0; i < subtrahend.size; i++)
       difference.ptr[i] -= subtrahend.ptr[i];

   for(int i = 0; i < difference.size - 1; i++){
       if (difference.ptr[i] < 0) {
           difference.ptr[i] += 10;
           difference.ptr[i + 1]--;
       }
   }

   while (difference.size > 0 && difference.ptr[difference.size - 1] == 0)
       difference.size--;

   if( difference.size > 1 && difference.ptr[ difference.size - 1 ] == 0 )
      cout << "difference has a leading zero!\n";

   assign( minuend, difference ); // minuend = difference

   delete[] difference.ptr;
}

// multiplicand *= multiplier
void multiAssign( HugeInt &multiplicand, HugeInt multiplier )
{
    HugeInt product;
    product.size = multiplicand.size + multiplier.size;
    delete[] product.ptr;
    product.ptr = new int[product.size]();
    for (int i = 0; i < multiplier.size; i++)
        for (int j = 0; j < multiplicand.size; j++)
            product.ptr[i + j] += multiplier.ptr[i] * multiplicand.ptr[j];
    
    for (int i = 0; i < product.size - 1; i++){
        if (product.ptr[i] > 9) {
            product.ptr[i + 1] += product.ptr[i] / 10;
            product.ptr[i] %= 10;
        }
    }

    while (product.size > 0 && product.ptr[product.size - 1] == 0)
        product.size--;

   if( product.size > 1 && product.ptr[ product.size - 1 ] == 0 )
      cout << "product has a leading zero!\n";

   assign( multiplicand, product ); // multiplicand = product

   delete[] product.ptr;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( HugeInt dividend, HugeInt divisor, HugeInt &quotient, HugeInt &remainder )
{
   assign( remainder, dividend ); // remainder = dividend

   if( less( dividend, divisor ) )
      reset( quotient );
   else
   {
      HugeInt buffer;
      buffer.size = dividend.size;
      delete[] buffer.ptr;
      buffer.ptr = new int[ buffer.size ]();

      assign(remainder, dividend); //remiander = dividend
      quotient.size = dividend.size - divisor.size;

      int n = dividend.size - divisor.size;
      for (int i = buffer.size - 1; i >= n; i--)
          buffer.ptr[i] = divisor.ptr[i - n];     
      if (less(remainder, buffer))
          divideBy10(buffer);
      else
          quotient.size++;
           
      delete[] quotient.ptr;
      quotient.ptr = new int[quotient.size]();      

      for (int k = quotient.size - 1; k >=0 ; k--) {
          while (!less(remainder, buffer)) {
              subtraAssign(remainder, buffer);
              quotient.ptr[k]++;
              if (isZero(remainder))
                  break;                       
          }
          divideBy10(buffer);
      }

      delete[] buffer.ptr;
   }
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( HugeInt &hugeInt )
{
   if( hugeInt.size == 1 )
      hugeInt.ptr[ 0 ] = 0;
   else
   {
      HugeInt buffer;
      assign( buffer, hugeInt ); // buffer = hugeInt

      hugeInt.size--;
      delete[] hugeInt.ptr;
      hugeInt.ptr = new int[ hugeInt.size ]();

      for( int i = 1; i <= hugeInt.size; i++ )
         hugeInt.ptr[ i - 1 ] = buffer.ptr[ i ];
   }
}

// hugeInt1 = hugeInt2; assignment
void assign( HugeInt &hugeInt1, HugeInt hugeInt2 )
{
   hugeInt1.size = hugeInt2.size;
   delete[] hugeInt1.ptr;
   hugeInt1.ptr = new int[ hugeInt1.size ];
   for( int i = 0; i < hugeInt1.size; i++ )
      hugeInt1.ptr[ i ] = hugeInt2.ptr[ i ];
}

void reset( HugeInt &hugeInt )
{
   hugeInt.size = 1;
   delete[] hugeInt.ptr;
   hugeInt.ptr = new int[ 1 ]();
}