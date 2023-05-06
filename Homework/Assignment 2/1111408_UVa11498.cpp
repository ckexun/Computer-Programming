#include <iostream>
using namespace std;
int main()
{
	int k;
	while(cin >> k)
	{
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < k; ++i)
		{
			int x, y;
			cin >> x >> y;
			if (x == n || y == m)
			{
				cout << "divisa" << endl;//xy軸
			}
			else if (x > n)
			{
				if (y > m)
				{
					cout << "NE" << endl;//東北
				}
				else
				{
					cout << "SE" << endl;//東南
				}
			}
			else if (x < n)
			{
				if (y > m)
				{
					cout << "NO" << endl;//西北
				}
				else
				{
					cout << "SO" << endl;//西南
				}
			}
		}
	}
	return 0;
}