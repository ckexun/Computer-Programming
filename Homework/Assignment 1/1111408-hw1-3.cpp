#include <iostream>
using namespace std;

int main()
{
   int number;
   int a, b, c, d, e;
   std::cout << "Enter a 5-digit positive integer:";
   std::cin >> number;
   a = number % 10;
   b = (number - a) % 100;
   b = b / 10;
   c = (number - 10*b-a) % 1000;
   c = c / 100;
   d = (number - 100*c- 10 * b - a) % 10000;
   d = d / 1000;
   e = (number - 1000*d - 100 * c - 10 * b - a) % 100000;
   e = e / 10000;
   std::cout << "The digits in the reverse order :"<<a<<b<<c<<d<<e;
}