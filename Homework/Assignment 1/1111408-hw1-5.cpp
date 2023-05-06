#include <iostream>
using namespace std;

int main()
{
   int year;
   int ans;
   std::cout << "Enter a year ( 1583-3000 ):";
   std::cin >> year;
   if (year % 100 != 0 && year % 4 == 0 || year % 400 == 0)
	   std::cout << "Year " << year << " is a leap year.";
   else
	   std::cout << "Year " << year << " is a common yaer.";
}