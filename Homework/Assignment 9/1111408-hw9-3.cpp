#include <iostream>
#include <fstream>
#include <vector>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the vector program
void load( vector< char * > &program );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( char sourceLine[] );

// deletes all string constants from sourceLine
void delStrConsts( char sourceLine[] );

// deletes all character constants from sourceLine
void delCharConsts( char sourceLine[] );

// extracts all identifiers from sourceLine, and put them into the vector identifiers
void extractIdentifiers( char sourceLine[], vector< char * > &identifiers );

// stores all non-keyword strings in the vector identifiers into a text file
void store( vector< char * > &identifiers );

// returns true if and only if str is a C++ keyword
bool keyword( char str[] );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( vector< char * > &identifiers, int pos );

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
   vector< char * > program;

   // reads in a C++ program from a cpp file, and put it to the vector program
   load( program );

   vector< char * > identifiers;
   for( size_t i = 0; i < program.size(); i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      if( strcmp( program[ i ], "" ) != 0 )
         extractIdentifiers( program[ i ], identifiers );
         // extracts all identifiers from program[ i ], and put them into the vector identifiers
   }

   // stores all non-keyword strings in the vector identifiers into a text file
   store( identifiers );

	system( "pause" );
}

void load( vector< char * > &program )
{
    ifstream infile("test2.cpp", ios::in);
    if (!infile) {
        cout << "open file error";
    }
    
    char* line = new char[100]();
    while (infile.getline(line,100)) {
        program.push_back(line);
        line = new char[100]();
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

void extractIdentifiers(char sourceLine[], vector< char* >& identifiers)
{
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

    //delete keywords
    char words[100]{};
    int n = 0;
    int keywordsSize = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < length; i++) {
        if (sourceLine[i] != ' ') {
            words[n] = sourceLine[i];
            n++;
        }
        else {
            if (words[0] != NULL) {
                for (int j = 0; j < keywordsSize; j++) { //compare keywords
                    if (strcmp(keywords[j], words) == 0) { 
                        for (int k = 0; k < strlen(words); k++)
                            sourceLine[(i - 1) - k] = ' '; //delete it
                    }
                }
                for (int p = strlen(words) - 1; p >= 0; p--) {
                    words[p] = NULL;
                }
                n = 0;
            }
        }
    }

    //store identifiers
    int m = 0;    
    char *tmp = new char[100]();     
    for (int i = 0; i < length; i++)
    {        
        if (sourceLine[i] != ' ') {
            tmp[m] = sourceLine[i];
            m++;
        }
        else { //sourceLine[i] == ' '
            if (m > 0) { //if tmp store things
                bool IDin = true;
                int IDsize = identifiers.size();
                for (int j = 0; j < IDsize; j++) { //check double
                    if (strcmp(identifiers[j],tmp) == 0) {
                        IDin = false;
                        break;
                    }
                    IDin = true;
                }
                if (IDin) {
                    identifiers.push_back(tmp);
                }
                tmp = new char[100]();
                m = 0;
            }
        }
    }
}

void store(vector< char* > &identifiers)
{
    ofstream outfile("identifiers.txt", ios::out);
    for (int i = 0; i < identifiers.size(); i++) {
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

bool duplicate( vector< char * > &identifiers, int pos )
{
   for( int i = 0; i < pos; i++ )
      if( strcmp( identifiers[ i ], identifiers[ pos ] ) == 0 )
         return true;

   return false;
}