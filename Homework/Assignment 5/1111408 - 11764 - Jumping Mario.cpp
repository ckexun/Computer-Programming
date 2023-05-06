#include <iostream>
using namespace std;

void recCompNumJumps( int &highJumps, int &lowJumps, int preHeight, int numWallsRemaining );

int main()
{
   int T; //´X²Õ´ú¸ê
   cin >> T;
   for( int i = 1; i <= T; i++ )
   {
      int highJumps = 0;
      int lowJumps = 0;
      int preHeight;
      int numWalls;
      cin >> numWalls;
      cin >> preHeight;
      
      recCompNumJumps( highJumps, lowJumps, preHeight, numWalls - 1 );

      cout << "Case " << i << ": " << highJumps << ' ' << lowJumps << endl;
   }

   system( "pause" );
}

void recCompNumJumps( int &highJumps, int &lowJumps, int preHeight, int numWallsRemaining )
{
   if (numWallsRemaining == 0)
       return;

   int height;
   cin >> height;
   if (preHeight - height < 0) {
       highJumps += 1;
       preHeight = height;
   }
   else if (preHeight - height > 0) {
       lowJumps += 1;
       preHeight = height;
   }
   recCompNumJumps(highJumps, lowJumps, preHeight, numWallsRemaining - 1);

}