#include <iostream>
#include <algorithm>
using namespace std;

int recMaxSpeed( int numRemaining );

int main()
{
	int T; //幾筆測資
	cin >> T;
	for( int i = 1; i <= T; i++ )
	{
		int N; //學生數
		cin >> N;
		cout << "Case " << i << ": " << recMaxSpeed( N ) << endl;
	}

	system( "pause" );
}

int recMaxSpeed( int numRemaining )
{
	int speed;
	cin >> speed;
	if (numRemaining == 1) { //遞迴最底層上來
		return speed;
	}
	else{  
		int last = recMaxSpeed(numRemaining - 1); 
		if (speed > last) {
			return speed;
		}
		else {
			return last;
		}
	}
}