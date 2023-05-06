#include <iostream>
using namespace std;

long long int recFinalPremium( int numFarmersRemaining );

int main()
{
   int n;
   cin >> n;
   for( int i = 0; i < n; i++ )//幾組測資
   {
      int f; //農夫個數
      cin >> f;
      cout << recFinalPremium( f ) << endl;
   }

   system( "pause" );
}

long long int recFinalPremium( int numFarmersRemaining )
{
   if (numFarmersRemaining == 0)
       return 0;

   long long int size;
   int numAnimals;
   long long int friendliness;
   cin >> size >> numAnimals >> friendliness;
   return size * friendliness + recFinalPremium(numFarmersRemaining - 1);

}