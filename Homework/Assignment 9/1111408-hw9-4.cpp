#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace::std;

 // reads in a C++ program from a cpp file, and put it to the vector program
void load( vector< string > &program );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( string &sourceLine );

// deletes all string constants from sourceLine ""
void delStrConsts( string &sourceLine );

// deletes all character constants from sourceLine ''
void delCharConsts( string &sourceLine );

// extracts all identifiers from sourceLine, and put them into the vector identifiers
void extractIdentifiers( string &sourceLine, vector< string > &identifiers );

// stores all non-keyword strings in the vector identifiers into a text file
void store( vector< string > &identifiers );

// return true if and only if "str" is a C++ keyword
bool keyword( string str );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( vector< string > &identifiers, int pos );

const string keywords[] = { "auto", "break", "case", "char", "const",
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
   vector< string > program;
   // reads in a C++ program from a cpp file, and put it to the vector program
   load( program );

   vector< string > identifiers;
   string null;

   for( size_t i = 0; i < program.size(); i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      if( program[ i ] != null )
         extractIdentifiers( program[ i ], identifiers );
         // extracts all identifiers from program[ i ], and put them into the vector identifiers
   }

   // stores all non-keyword strings in the vector identifiers into a text file
   store( identifiers );

	system( "pause" );
}

void load( vector< string > &program )
{
    ifstream inFile("test2.cpp", ios::in);

    if (!inFile)
        cout << "open file error";

    string line;

    while (getline(inFile, line))
    {
        program.push_back(line);       
    }

    inFile.close();
}

void delComment( string &sourceLine )
{
   size_t length = sourceLine.size();
   if( length > 1 )
      for( size_t i = 0; i < length - 1; i++ )
         if( sourceLine[ i ] == '/' && sourceLine[ i + 1 ] == '/' )
         {
            sourceLine.erase( i, length );
            break;
         }
}

void delStrConsts( string &sourceLine )
{
    size_t length = sourceLine.size();
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

void delCharConsts( string &sourceLine )
{
    size_t length = sourceLine.size();
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

void extractIdentifiers( string &sourceLine, vector< string > &identifiers )
{
    size_t length = sourceLine.size();
       
    //delete operator and only math
    for (int i = 0; i < length; i++) { //delete operator
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

    // delete keywords
    string  words;
    int keywordsSize = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < length; i++) {
        if (sourceLine[i] != ' ') {           
            words.push_back(sourceLine[i]);  
        }
        else {
            if (words[0] != NULL) {
                for (int j = 0; j < keywordsSize; j++) { //compare keywords
                    if (words == keywords[j]) { //delete it  
                        size_t found = sourceLine.find(keywords[j]);
                        for (int k = 0; k < words.size(); k++)
                            sourceLine[found + k] = ' ';
                    }
                }
                words.clear();
            }           
        }
    }
    
    //store identifiers
    string tmp;
    bool IDin = true;
    for (int i = 0; i < length; i++) 
    {       
        if (sourceLine[i] != ' ') {
            tmp.push_back(sourceLine[i]);
        }
        else { //sourceLine[i] == ' '
            if (tmp[0] != NULL) { //if tmp store things

                if (identifiers.size() == 0) { //first tmp
                    identifiers.push_back(tmp);
                }
                int IDsize = identifiers.size();
                for (int j = 0; j < IDsize; j++) { //check double
                    if (identifiers[j] == tmp) {
                        IDin = false;
                        break;
                    }
                    IDin = true;
                }
                if (IDin) {
                    identifiers.push_back(tmp);
                }
                tmp.clear();
            }            
        }             
    }
}

void store( vector< string > &identifiers )
{
    ofstream outFile("identifiers.txt.", ios::out);
    int IDsize = identifiers.size();
    for (int i = 0; i < IDsize; i++) {
        outFile << identifiers[i] << endl;
    }
}

bool keyword( string str )
{
   size_t numKeywords = sizeof( keywords ) / 20;
   for( size_t i = 0; i < numKeywords; i++ )
      if( keywords[ i ] == str )
         return true;

   return false;
}

bool duplicate( vector< string > &identifiers, int pos )
{
   for( int i = 0; i < pos; i++ )
      if( identifiers[ i ] == identifiers[ pos ] )
         return true;

   return false;
}