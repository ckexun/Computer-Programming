#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
    char* words;
    char* tmp = NULL;
    char* part = NULL;
    
    words = strtok_s(sourceLine, " ",&tmp); //take first words from sourceLine
    part = words;
    strncat_s(part,strlen(part), " ", 1);
    if (keyword(words)) {
        for (int i = 0; i < strlen(words); i++) {
            words[i] = ' ';
        } 
    }       

    words = strtok_s(NULL, " ", &tmp); //take other words in sourceLine
//    strcat(part,(const char*)words);
//    strncat_s(part,strlen(part), " ", 1);
    while (words != NULL) {
        if (keyword(words)) {
            for (int i = 0; i < strlen(words); i++) {
                words[i] = ' ';
            }
        }
        words = strtok_s(NULL, " ", &tmp);
//        strcat(part, (const char*)words);
//        strncat_s(part,strlen(part), " ", 1);
    }
//    cout << sourceLine;
}