#include <iostream>
using namespace std;
int main()
{
	int	n,f;
	long long int owns = 0;
	double size, number, level, part;
	std::cin >> n;
	for (int i= 0 ; i < n;i++)
	{
		cin >> f;
		while (f > 0)
		{
			cin >> size >> number >> level;
			part= size * level;
			owns = owns + part;
			part = 0;
			f -= 1;
		}
		cout << owns <<endl;
		owns = 0;
	}
}