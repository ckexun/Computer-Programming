// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

// outputs the specified polynomial
void output( int coefficient[], int exponent[], int size );

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms( int coefficient[], int size );

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( int coefficient[], int size );

// returns true if and only if polynomial1 == polynomial2
bool equal( int coefficient1[], int exponent1[], int size1,
            int coefficient2[], int exponent2[], int size2 );

// polynomial1 = -polynomial2
void minus( int coefficient1[], int exponent1[], int &size1,
            int coefficient2[], int exponent2[], int size2 );

// addend += adder
void addition( int addendCoef[], int addendExpon[], int &addendSize,
               int adderCoef[], int adderExpon[], int adderSize );

// minuend -= subtrahend
void subtraction( int minuendCoef[], int minuendExpon[], int &minuendSize,
                  int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize );

// product = multiplicand * multiplier
void multiplication( int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
                     int multiplierCoef[], int multiplierExpon[], int multiplierSize,
                     int productCoef[], int productExpon[], int &productSize );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division( int dividendCoef[], int dividendExpon[], int dividendSize,
               int divisorCoef[], int divisorExpon[], int divisorSize,
               int quotientCoef[], int quotientExpon[], int &quotientSize,
               int remainderCoef[], int remainderExpon[], int &remainderSize );

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;
int main()
{
   ifstream inFile( "Polynomials.dat", ios::in | ios::binary );

   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   int numErrors = numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      int dividendCoef[ arraySize ] = {};
      int dividendExpon[ arraySize ] = {};
      int divisorCoef[ arraySize ] = {};
      int divisorExpon[ arraySize ] = {};

      // input dividend and divisor from the file Polynomials.dat
      inFile.read( reinterpret_cast< char * >( dividendCoef ), 80 );
      inFile.read( reinterpret_cast< char * >( dividendExpon ), 80 );
      inFile.read( reinterpret_cast< char * >( divisorCoef ), 80 );
      inFile.read( reinterpret_cast< char * >( divisorExpon ), 80 );

      int dividendSize = arraySize;
      while( dividendSize > 1 && dividendCoef[ dividendSize - 1 ] == 0 )
         dividendSize--;

      int divisorSize = arraySize;
      while( divisorSize > 1 && divisorCoef[ divisorSize - 1 ] == 0 )
         divisorSize--;

      int quotientCoef[ arraySize ] = {};
      int quotientExpon[ arraySize ] = {};
      int remainderCoef[ arraySize ] = {};
      int remainderExpon[ arraySize ] = {};
      int quotientSize = 1;
      int remainderSize = 1;

      cout << "dividend:  ";
      output( dividendCoef, dividendExpon, dividendSize );

      cout << " divisor:  ";
      output( divisorCoef, divisorExpon, divisorSize );

      // quotient = dividend / divisor; remainder = dividend % divisor
      // thus, dividend == divisor * quotient + remainder
      division( dividendCoef, dividendExpon, dividendSize,
                divisorCoef, divisorExpon, divisorSize,
                quotientCoef, quotientExpon, quotientSize,
                remainderCoef, remainderExpon, remainderSize );

      cout << "quotient:  ";
      output( quotientCoef, quotientExpon, quotientSize );
      cout << endl;

      if( zeroTerms( quotientCoef, quotientSize ) )
         cout << "quotient has at least a zero term!\n";

      if( zeroTerms( remainderCoef, remainderSize ) )
         cout << "remainder has at least a zero term!\n";

      int bufferCoef[ arraySize ] = {};
      int bufferExpon[ arraySize ] = {};
      int bufferSize = 1;

      // buffer = divisor * quotient
      multiplication( divisorCoef, divisorExpon, divisorSize,
                      quotientCoef, quotientExpon, quotientSize,
                      bufferCoef, bufferExpon, bufferSize );

      if( zeroTerms( bufferCoef, bufferSize ) )
         cout << "buffer has at least a zero term!\n";

      // buffer = buffer + remainder = divisor * quotient + remainder
      addition( bufferCoef, bufferExpon, bufferSize,
                remainderCoef, remainderExpon, remainderSize );

      if( zeroTerms( bufferCoef, bufferSize ) )
         cout << "buffer has at least a zero term!\n";

      // if buffer != dividend, an error occurred!
      if( equal( bufferCoef, bufferExpon, bufferSize,
                 dividendCoef, dividendExpon, dividendSize ) )
         numErrors--;
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

// outputs the specified polynomial
void output( int coefficient[], int exponent[], int size )
{
   // the specified polynomial is zero polynomial
   if( isZero( coefficient, size ) )
      cout << 0;
   else
   {
      if( coefficient[ size - 1 ] < 0 )
         cout << "-" << -coefficient[ size - 1 ];
      else if( coefficient[ size - 1 ] > 0 )
         cout << coefficient[ size - 1 ];

      if( exponent[ size - 1 ] > 0 )
      {
         if( exponent[ size - 1 ] == 1 )
            cout << "x";
         else
            cout << "x^" << exponent[ size - 1 ];
      }

      for( int i = size - 2; i >= 0; i-- )
      {
         if( coefficient[ i ] < 0 )
            cout << " - " << -coefficient[ i ];
         else if( coefficient[ i ] > 0 )
            cout << " + " << coefficient[ i ];

         if( exponent[ i ] > 0 )
         {
            if( exponent[ i ] == 1 )
               cout << "x";
            else
               cout << "x^" << exponent[ i ];
         }
      }
   }

   cout << endl;
}

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms( int coefficient[], int size )
{
   if( !isZero( coefficient, size ) )
      for( int i = 0; i < size; i++ )
         if( coefficient[ i ] == 0 )
            return true;

   return false;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( int coefficient[], int size )
{
   if( size == 1 && coefficient[ 0 ] == 0 )
      return true;
   return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal( int coefficient1[], int exponent1[], int size1,
            int coefficient2[], int exponent2[], int size2 )
{
   if( size1 != size2 )
      return false;

   for( int i = 0; i < size1; i++ )
      if( coefficient1[ i ] != coefficient2[ i ] || exponent1[ i ] != exponent2[ i ] )
         return false;

   return true;
}

// polynomial1 = -polynomial2
void minus( int coefficient1[], int exponent1[], int &size1,
            int coefficient2[], int exponent2[], int size2 )
{
   size1 = size2;
   for( int i = 0; i < size1; i++ )
   {
      coefficient1[ i ] = -coefficient2[ i ];
      exponent1[ i ] = exponent2[ i ];
   }
}

// addend += adder
void addition( int addendCoef[], int addendExpon[], int &addendSize,
               int adderCoef[], int adderExpon[], int adderSize )
{
   // if( adder == 0 )
   if( isZero( adderCoef, adderSize ) )
      return;

   // if( addend == 0 )
   if( isZero( addendCoef, addendSize ) )
   {
      // addend = adder
      addendSize = adderSize;
      for( int i = 0; i < addendSize; i++ )
      {
         addendCoef[ i ] = adderCoef[ i ];
         addendExpon[ i ] = adderExpon[ i ];
      }
      return;
   }

   int sumCoef[ arraySize ] = {};
   int sumExpon[ arraySize ] = {};
   int i = 0;
   int j = 0;
   int k = 0;
   while( i < addendSize && j < adderSize )
   {
       if (addendExpon[ i ] == adderExpon[ j ])
       {
           sumExpon[ k ] = addendExpon[ i ] = adderExpon[ j ];
           sumCoef[ k ] = addendCoef[ i ] + adderCoef[ j ];
            i++;
            j++;     
           if (sumCoef[k] == 0)//相加值為0時內容重新輸入
               k--;
       }
       else if (addendExpon[i] < adderExpon[j])
       {
           sumExpon[k] = addendExpon[i];
           sumCoef[k] = addendCoef[i];
           i++;
       }
       else
       {
           sumExpon[k] = adderExpon[j];
           sumCoef[k] = adderCoef[j];
           j++;
       }
       k++;
   }

   while( i < addendSize )
   {
       sumExpon[k] = addendExpon[i];
       sumCoef[k] = addendCoef[i];
       i++;
       k++;
   }

   while( j < adderSize )
   {
       sumExpon[k] = adderExpon[j];
       sumCoef[k] = adderCoef[j];
       j++;
       k++;
   }

   addendSize = k;
   for( int i = 0; i < addendSize; i++ ) // addend = sum
   {
      addendCoef[ i ] = sumCoef[ i ];
      addendExpon[ i ] = sumExpon[ i ];
   }

   if( zeroTerms( addendCoef, addendSize ) )
      cout << "addend has at least a zero term!\n";
}

// minuend -= subtrahend
void subtraction( int minuendCoef[], int minuendExpon[], int &minuendSize,
                  int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize )
{
   // minuend == subtrahend
   if( equal( minuendCoef, minuendExpon, minuendSize, subtrahendCoef, subtrahendExpon, subtrahendSize ) )
   {
    minuendSize = 1;     // minuend = 0;
    minuendCoef[0] = 0;
    minuendExpon[0] = 0;
    return;
   }

   // buffer = 0
   int bufferCoef[arraySize] = {};
   int bufferExpon[arraySize] = {};
   int bufferSize = 1;

   // buffer = -subtrahend
   minus(bufferCoef, bufferExpon, bufferSize, subtrahendCoef, subtrahendExpon, subtrahendSize);

   // minuend = minuend + buffer = minuend - subtrahend
   addition(minuendCoef, minuendExpon, minuendSize, bufferCoef, bufferExpon, bufferSize);

   if (zeroTerms(minuendCoef, minuendSize))
       cout << "minuend has at least a zero term!\n";
}

// product = multiplicand * multiplier
void multiplication(int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
    int multiplierCoef[], int multiplierExpon[], int multiplierSize,
    int productCoef[], int productExpon[], int& productSize)
{
    // product = 0;
    productSize = 1;
    productCoef[0] = 0;
    productExpon[0] = 0;
    int bufferCoef[arraySize] = {};
    int bufferExpon[arraySize] = {};
    int bufferSize = multiplicandSize;
    if (isZero(multiplicandCoef, multiplicandSize) || isZero(multiplierCoef, multiplierSize))//判斷是否為0多項式
        return;
    for (int i = 0; i < multiplierSize; i++)
    {
        for (int j = 0; j < multiplicandSize; j++)
        {
            bufferExpon[j] = multiplierExpon[i] + multiplicandExpon[j];
            bufferCoef[j] = multiplierCoef[i] * multiplicandCoef[j];
        }
        addition(productCoef, productExpon, productSize,
            bufferCoef, bufferExpon, bufferSize);
    }

    if (zeroTerms(productCoef, productSize))
        cout << "product has at least a zero term!\n";
}

/*int main()
{
    int a1Coef[arraySize] = {}, a1Expon[arraySize] = {}, a1Size = 19;

}*/
// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division(int dividendCoef[], int dividendExpon[], int dividendSize,
    int divisorCoef[], int divisorExpon[], int divisorSize,
    int quotientCoef[], int quotientExpon[], int& quotientSize,
    int remainderCoef[], int remainderExpon[], int& remainderSize)
{
    // if( dividend == 0 )
    if (isZero(dividendCoef, dividendSize))
    {
        // quotient = 0
        quotientSize = 1;
        quotientCoef[0] = 0;
        quotientExpon[0] = 0;

        // remainder = 0
        remainderSize = 1;
        remainderCoef[0] = 0;
        remainderExpon[0] = 0;
        return;
    }

    // remainder = dividend
    remainderSize = dividendSize;
    for (int i = 0; i < remainderSize; i++)
    {
        remainderCoef[i] = dividendCoef[i];
        remainderExpon[i] = dividendExpon[i];
    }

    quotientSize = dividendExpon[dividendSize - 1] - divisorExpon[divisorSize - 1] + 1;
    for (int i = quotientSize - 1; i >= 0; i--)
    {
        quotientExpon[i] = remainderExpon[remainderSize - 1] - divisorExpon[divisorSize - 1];//輸入商
        quotientCoef[i] = remainderCoef[remainderSize - 1] / divisorCoef[divisorSize - 1];
        int monomialExpon[arraySize] = {}, monomialCoef[arraySize] = {}, monomialSize = 1;//定義monomial
        //呼叫減法，乘法
        monomialExpon[0] = quotientExpon[i];
        monomialCoef[0] = quotientCoef[i];
        int bufferExpon[20] = {}, bufferCoef[20] = {}, bufferSize;
        //buffer =monomial*divisor
        multiplication(monomialCoef, monomialExpon, monomialSize, divisorCoef, divisorExpon, divisorSize, bufferCoef, bufferExpon, bufferSize);
        //remainder-=buffer
        subtraction(remainderCoef, remainderExpon, remainderSize, bufferCoef, bufferExpon, bufferSize);
        if (remainderExpon[remainderSize - 1] < divisorExpon[divisorSize - 1] || //除式可結束的條件
            remainderExpon[remainderSize - 1] == 0 && remainderCoef[remainderSize - 1] / dividendCoef[divisorSize - 1] == 0)
        {
            quotientSize = quotientSize - i; //算出未執行完次數
            if (i > 0)
                for (int j = 0; j < quotientSize; j++) { //往前填補
                    quotientCoef[j] = quotientCoef[j + i];
                    quotientExpon[j] = quotientExpon[j + i];
                    quotientCoef[j + i] = quotientExpon[j + i] = 0;
                }
            return;

        }
   }
}