#include <iostream>
using namespace std;

void recDivisionNlogonia( int N, int M, int numQueriesRemaining );

int main()
{
	int K, N, M;
	cin >> K; //需判斷點座標數
	while( K > 0 )
	{
		cin >> N >> M; //參考點
		recDivisionNlogonia( N, M, K );
		cin >> K;
	}

	system( "pause" );
}

void recDivisionNlogonia( int N, int M, int numQueriesRemaining )
{
	if (numQueriesRemaining == 0)
		return ;

	int x, y;
	cin >> x >> y;
	if (x - N == 0 || y - M == 0) {
		cout << "divisa" << endl;
	}
	else if (x - N > 0) {
		if (y - M > 0) {
			cout << "NE" << endl;
		}
		else {
			cout << "SE" << endl;
		}
	}
	else {
		if (y - M > 0) {
			cout << "NO" << endl;
		}
		else {
			cout << "SO" << endl;
		}
	}
	recDivisionNlogonia(N, M, numQueriesRemaining - 1);

}