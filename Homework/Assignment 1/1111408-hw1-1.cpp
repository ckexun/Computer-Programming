#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
	int number1; // first integer read from user
	int number2; // second integer read from user
	int number3; // third integer read from user
	int answer;
	std::cout << "Enter three distinct integers:";
	std::cin >> number1 >> number2 >> number3;
	if (number1 > number2)
	{
		if (number2 > number3)
			answer = number2;
		else if (number3 > number1)
			answer = number1;
		else
			answer = number3;
	}
	else if (number2 > number1)
	{
		if (number1 > number3)
			answer = number1;
		else if (number3 > number2)
			answer = number2;
		else
			answer = number3;
	}
	std::cout << "Median is" << answer;
}