// This program reads a binary file,
// updates grades previously written to the file,
// adds new grades in the file,
// and deletes data previously stored in the file.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;

struct StudentData
{
   char studentId[ 8 ];
   char lastName[ 12 ];
   char firstName[ 12 ];
   int grade;
};

enum class Choices{ PRINT = 1, UPDATE, NEW, DELETE, END };

// enable user to input menu choice
Choices enterChoice();

// create text file for printing
void createTextFile( fstream &readFromFile );

// update grade in record
void updateRecord( fstream &updateFile );

// add a new grade in record
void newRecord( fstream &insertInFile );

// delete an existing record
void deleteRecord( fstream &deleteFromFile );

// obtain student ID from user
void getID( const char * const prompt, char studentId[] );

int main()
{
   // open file for reading and writing
   fstream inOutGrade( "grades.dat", ios::in | ios::out | ios::binary );

   // exit program if fstream cannot open file
   if( !inOutGrade )
   {
      cerr << "File could not be opened." << endl;
      system( "pause" );
      exit( 1 );
   }

   Choices choice; // store user choice

   // enable user to specify action
   while( ( choice = enterChoice() ) != Choices::END )
   {
      switch( choice )
      {
      case Choices::PRINT:
         createTextFile( inOutGrade ); // create text file from binary file
         break;
      case Choices::UPDATE:
         updateRecord( inOutGrade ); // update grade
         break;
      case Choices::NEW:
         newRecord( inOutGrade ); // add a new grade
         break;
      case Choices::DELETE:
         deleteRecord( inOutGrade ); // delete existing record
         break;
      default:
         cerr << "Incorrect choice" << endl;
         break;
      }

      inOutGrade.clear();
      inOutGrade.seekg(0);
      
      cout << endl;
   }

   inOutGrade.close();

   system( "pause" );
}

// enable user to input menu choice
Choices enterChoice()
{
   // display available options
   cout << "Enter your choice" << endl
      << "1 - store a text file of all students' information" << endl
      << "    called \"grades.txt\" for printing" << endl
      << "2 - update a student's grade" << endl
      << "3 - add a student's grade" << endl
      << "4 - delete a student's information" << endl
      << "5 - end program\n? ";

   int menuChoice;
   cin >> menuChoice;
   return static_cast< Choices >( menuChoice );
}

// create text file for printing
void createTextFile( fstream &readFromFile )
{    
    ofstream outfile("grades.txt", ios::out);
    outfile << setw(13) << left << "ID"
        << setw(12) << "Last Name"
        << setw(13) << "First Name"
        << setw(5) << right << "Grade" << endl;
    
    cout << setw(13) << left << "ID"
        << setw(12) << "Last Name"
        << setw(13) << "First Name"
        << setw(5) << right << "Grade" << endl;

    StudentData student{};
    while (readFromFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData))) {
        if(student.grade != -2){
            outfile << setw(13) << left << student.studentId
                << setw(12) << student.lastName
                << setw(13) << student.firstName
                << setw(5) << right << student.grade << endl;

            cout << setw(13) << left << student.studentId
                << setw(12) << student.lastName
                << setw(13) << student.firstName
                << setw(5) << right << student.grade << endl;
        }
    }
}

// update grade in record
void updateRecord( fstream &updateFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to update", studentId );
   
   StudentData student{};
   int newgrade;

   int inClassId = 10 * (studentId[5] - '0') + (studentId[6] - '0');
   updateFile.seekg((inClassId - 1) * sizeof(StudentData));
   updateFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));

   if (student.grade == -2) {
       cout << endl << "Student ID " << studentId << " is empty." << endl;
   }

   else if (student.grade == -1) {
       cout << endl << "Student ID " << studentId << " has no grade." << endl;
   }

   else {
       cout << endl;
       cout << setw(13) << left << student.studentId
           << setw(12) << student.lastName
           << setw(13) << student.firstName
           << setw(5) << right << student.grade << endl;

       cout << endl << "Enter grade: ";
       cin >> newgrade;
       cout << endl;
       student.grade = newgrade;

       updateFile.seekp((inClassId - 1) * sizeof(StudentData));
       updateFile.write(reinterpret_cast<char*>(&student), sizeof(StudentData));
       cout << setw(13) << left << student.studentId
           << setw(12) << student.lastName
           << setw(13) << student.firstName
           << setw(5) << right << student.grade << endl;
   }
}

// add a new grade in record
void newRecord( fstream &insertInFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to add", studentId );

   StudentData student{};
   int newgrade;

   int inClassId = 10 * (studentId[5] - '0')+ (studentId[6] - '0');
   insertInFile.seekg((inClassId - 1) * sizeof(StudentData));
   insertInFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));
   
   if (student.grade == -2) {
       cout << endl << "Student ID " << studentId << " is empty." << endl;
   }

   else{
       cout << endl << "Enter grade: ";
       cin >> newgrade;
       cout << endl;
       student.grade = newgrade;
   
       insertInFile.seekp((inClassId - 1) * sizeof(StudentData));
       insertInFile.write(reinterpret_cast<char*>(&student), sizeof(StudentData));
       cout << setw(13) << left << student.studentId
            << setw(12) << student.lastName
            << setw(13) << student.firstName
            << setw(5) << right << student.grade << endl;
   }
}

// delete an existing record
void deleteRecord( fstream &deleteFromFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to delete", studentId );

   StudentData student{};

   int inClassId = 10 * (studentId[5] - '0') + (studentId[6] - '0');
   deleteFromFile.seekg((inClassId - 1) * sizeof(StudentData));
   deleteFromFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));

   if (student.grade == -2) {
       cout << endl << "Student ID " << studentId << " is empty." << endl;
   }

   else{
       cout << endl;
       student.grade = -2;

       deleteFromFile.seekp((inClassId - 1) * sizeof(StudentData));
       deleteFromFile.write(reinterpret_cast<char*>(&student), sizeof(StudentData));
       cout <<  "Student ID " << studentId << " deleted." << endl;   
   }
}

// obtain student ID from user
void getID( const char * const prompt, char studentId[] )
{
   do
   {
      cout << prompt << " ( 1111401 - 1111450 ): ";
      cin >> studentId;
   } while( strcmp( studentId, "1111401" ) == -1 || strcmp( studentId, "1111450" ) == 1 );
}