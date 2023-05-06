// Exercise 4.18 Solution: ex04_18.cpp
// Display decimal, binary, octal and hexadecimal numbers.
#include <iostream>
using namespace std; 

int main()
{
   int number; // a positive integer less than 32
   int bit1=0;   // the rightmost bit of number
   int bit2=0;
   int bit3=0;
   int bit4=0;
   int bit5=0;   // the leftmost bit of number
   std::cout << "Enter a positive integer less than 32:";
   std::cin >> number;
   while (number > 0)
   {
       bit1 = bit1 + 1;
       if (bit1 == 2)
       {
        bit2 = bit2 + 1;
        bit1 = 0;
       }
       if (bit2 == 2)
       {
        bit3 = bit3 + 1;
        bit2 = 0;
       }   
       if (bit3 == 2)
       {
        bit4 = bit4 + 1;
        bit3 = 0;
       }
       if (bit4 == 2)
       {
        bit5 = bit5 + 1;
        bit4 = 0;
       }
       number = number - 1;
   }
   std::cout << "The binary equivalent of 10 is "<<bit5<<bit4<<bit3<<bit2<<bit1;
}