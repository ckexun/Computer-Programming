#include <iostream>
using namespace std;

int main()
{
   system( "mode con:cols=60 lines=16" );
   system( "color F0" );

   char s1[ 20 ];
   char s2[] = "string literal";

   cout << "Enter the string \"eat here\": ";
   cin >> s1; // reads "eat"

   cout << "s1 is: " << s1 << "\nstring2 is: " << s2;

   cout << "\nstring1 with spaces between characters is:\n";
   for ( int i = 0; s1[ i ] != '\0'; i++ )
      cout << s1[ i ] << ' ';
   cout << '\n';

   cout << '\n' << s1[ 0 ] << ' ' << s1[ 1 ] << ' ' << s1[ 2 ] << '\n';
   cout << '\n' << s1[ 0 ] << '\'' << s1[ 1 ] << '\'' << s1[ 2 ] << '\n';
   cout << '\n' << s1[ 0 ] << ' ' << s1[ 1 ] << '\'' << s1[ 2 ] << '\n';
   cout << '\n' << s1[ 0 ] << '\'' << s1[ 1 ] << ' ' << s1[ 2 ] << '\n';

   cin >> s1; // reads "here"
   cout << "\nstring1 is: " << s1 << '\n';

   system( "pause" );
}