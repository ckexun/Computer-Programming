#include <iostream>
using namespace std;
int main()
{
	int t;//´Xµ§´ú¸ê
	cin >> t;
	for (int i = 1; i <=t; i++)
	{
		int n;//student number
		cin >> n;
		int min=0;//the minimum speed
		while (n > 0)
		{
			int speed;
			cin >> speed;
			if (speed > min)
			{
				min = speed;
			}
			n -= 1;
		}
		cout << "Case " << i << ": " << min<<endl;
	}
}