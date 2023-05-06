#include <iostream>
#include <fstream>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( char( *program )[ 100 ], int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( char sourceLine[] );

// deletes all string constants from sourceLine
void delStrConsts( char sourceLine[] );

// deletes all character constants from sourceLine
void delCharConsts( char sourceLine[] );

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers );

// stores all non-keyword strings in the array identifiers into a text file
void store( char ( *identifiers )[ 32 ], int numIdentifiers );

// returns true if and only if str is a C++ keyword
bool keyword( char str[] );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( char ( *identifiers )[ 32 ], int pos );

const char keywords[][ 20 ] = { "auto", "break", "case", "char", "const",
                                "continue", "default", "define","do", "double",
                                "else", "enum", "extern", "float", "for",
                                "goto", "if", "int", "long", "register",
                                "return", "short", "signed", "sizeof",
                                "static", "struct", "switch", "typedef",
                                "union", "unsigned", "void", "volatile",
                                "while", "bool", "catch", "class",
                                "const_cast", "delete", "dynamic_cast",
                                "explicit", "false", "friend", "inline",
                                "mutable", "namespace", "new", "operator",
                                "private", "protected", "public",
                                "reinterpret_cast", "static_cast", "template",
                                "this", "throw", "true", "try", "typeid",
                                "typename", "using", "virtual", "include" };

int main()
{
   char ( *program )[ 100 ] = new char[ 500 ][ 100 ];
   int numLines = 0;

   // reads in a C++ program from a cpp file, and put it to the array program
   load( program, numLines );

   char ( *identifiers )[ 32 ] = new char[ 500 ][ 32 ];
   int numIdentifiers = 0;

   for( int i = 0; i < numLines; i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      if( strcmp( program[ i ], "" ) != 0 )
         extractIdentifiers( program[ i ], identifiers, numIdentifiers );
         // extracts all identifiers from program[ i ], and put them into the array identifiers
   }

   // stores all non-keyword strings in the array identifiers into a text file
   store( identifiers, numIdentifiers );

	system( "pause" );
}

void load( char( *program )[ 100 ], int &numLines )
{
    ifstream infile("test2.cpp", ios::in);

    while (infile.getline(program[numLines],100)) {
        numLines++;
    }
    infile.close();
}

void delComment( char sourceLine[] )
{
   size_t length = strlen( sourceLine );
   if( length > 1 )
      for( size_t i = 0; i < length - 1; i++ )
         if( sourceLine[ i ] == '/' && sourceLine[ i + 1 ] == '/' )
         {
            sourceLine[ i ] = '\0';
            return;
         }
}

void delStrConsts( char sourceLine[] )
{
    size_t length = strlen(sourceLine);
    bool replace = false;
    if (length > 1) {
        for (int i = 0; i < length; i++) {
            if (sourceLine[i] == '\\' && sourceLine[i + 1] == '\"') {
                sourceLine[i] = ' ';
                replace = !replace;
            }
            if (sourceLine[i] == '\"') {
                sourceLine[i] = ' ';
                replace = !replace;
            }
            if (replace)
                sourceLine[i] = ' ';
        }
    }
}

void delCharConsts( char sourceLine[] )
{
    size_t length = strlen(sourceLine);
    bool replace = false;
    if (length > 1) {
        for (int i = 0; i < length; i++) {
            if (sourceLine[i] == '\\' && sourceLine[i + 1] == '\'') {
                sourceLine[i] = ' ';
                replace = !replace;
            }
            if (sourceLine[i] == '\'') {
                sourceLine[i] = ' ';
                replace = !replace;
            }
            if (replace)
                sourceLine[i] = ' ';
        }
    }
}

void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers )
{
    //delete operetor & math
    size_t length = strlen(sourceLine);

    for (int i = 0; i < length; i++) {
        //delete operator
        if (sourceLine[i] >= (char)33 && sourceLine[i] <= char(47) ||
            sourceLine[i] >= (char)58 && sourceLine[i] <= (char)64 ||
            sourceLine[i] >= (char)91 && sourceLine[i] <= (char)94 ||
            sourceLine[i] >= (char)123 && sourceLine[i] <= (char)126)
        {
            sourceLine[i] = ' ';
        }
        // delete math
        else if (sourceLine[i] >= (char)48 && sourceLine[i] <= (char)57 && sourceLine[i - 1] == ' ')
        {
            sourceLine[i] = ' ';
        }
    }

    //put in identifiers
    char words[100]{};
    int n = 0;
    int keywordsSize = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < length; i++) {
        if (sourceLine[i] != ' ') {
            words[n] = sourceLine[i];
            n++;
        }
        else {
            if(n > 0){
                if (!keyword(words)) {
                    strcpy_s(identifiers[numIdentifiers], words);                   
                    if (duplicate(identifiers, numIdentifiers)) {
                        strcpy_s(identifiers[numIdentifiers],"\0");
                        numIdentifiers--;
                    }
                    numIdentifiers++;
                }
                for (int j = strlen(words) - 1; j >= 0; j--) {
                    words[j] = '\0';
                }
                n = 0;
            }
        }
    }
}

void store( char ( *identifiers )[ 32 ], int numIdentifiers )
{
    ofstream outfile("identifers.txt", ios::out);
    for (int i = 0; i < numIdentifiers; i++) {
        outfile << identifiers[i] << endl;
    }
}

bool keyword( char str[] )
{
   size_t numKeywords = sizeof( keywords ) / 20;
   for( size_t i = 0; i < numKeywords; i++ )
      if( strcmp( keywords[ i ], str ) == 0 )
         return true;

   return false;
}

bool duplicate( char ( *identifiers )[ 32 ], int pos )
{
   for( int i = 0; i < pos; i++ )
      if( strcmp( identifiers[ i ], identifiers[ pos ] ) == 0 )
         return true;

   return false;
}