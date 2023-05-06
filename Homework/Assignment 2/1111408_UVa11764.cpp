#include <iostream>
using namespace std;
int main()
{
	int t;
	cin >> t;
	for (int i = 1; i <=t; ++i)//t筆測資
	{
		int n;//牆壁數
		int high{ 0 }, low{ 0 };//結果初始值
		int stand, jump;//牆壁站與跳
		cin >> n;
		cin >> stand;
		while (n > 1)
		{
			cin >> jump;
			if (jump > stand)
			{
				high += 1;
			}
			else if (jump < stand)
			{
				low += 1;
			}
			stand = jump;
			n -= 1;
		}
		cout << "Case " << i<<": "<<high<<" " << low << endl;
	}
}