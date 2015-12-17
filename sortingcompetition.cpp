/************************
 * Sorting Competition
 * CSE 2341
 * Authors:
 *      Nick Antonelli
 ************************/


#include "sortingcompetition.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "stdlib.h"

using std :: ifstream;
using std :: ofstream;
using std :: cout;
using std :: endl;
using std :: string;

//Constructor
SortingCompetition::SortingCompetition(const string& inputFileName){
    fileName = inputFileName;
    radixHelper = new int*[6];
    for (int i = 0; i < 6; i++){
        radixHelper[i] = new int[11];
        for (int x = 0; x < 11; x++){
            radixHelper[i][x] = 0;
        }
    }
    return;
}

//Sets the private variable fileName equal to the input file name
void SortingCompetition :: setFileName(const string& inputFileName){
    fileName = inputFileName;
    return;
}

//Reads in the data and stores the words as length prefixed C-strings
//Stores the words inside a vector of char* 's
//radixHelper serves as a counter to keep track of how many words of
//various lengths are read from the input file
bool SortingCompetition :: readData(){
    ifstream fin(fileName.c_str());
    if (!fin.is_open()){
        return false;
    }
    char* buff = new char[51];
    while (!fin.eof()){
        fin >> buff;
        int length = strlen(buff);
        char* word = new char[length+3];
        //converts the words into length prefixed C-strings
        if (length < 10){
            word[0] = '0';
            word[1] = (char) '0' + length;
            word[2] = '\0';
            radixHelper[0][length%10]++;
            radixHelper[0][10]++;
        }
        else{
            word[1] = '0' + length % 10;
            word[0] = '0' + length/10;
            word[2] = '\0';
            radixHelper[length/10][length % 10]++;
            radixHelper[length/10][10]++;
        }
        //makes all words lower case. Purely an asthetic thing
        for (int i = 0; i < length; i++){
            buff[i] = tolower(buff[i]);
        }
        strcat(word, buff);
        wordArray.push_back(word);
    }
    delete [] buff;
    fin.close();
    return true;
}

//Copies the words stored in the vector wordArray into a char** sortableArray
bool SortingCompetition :: prepareData(){
    sortableArray = new char*[wordArray.size()];
    sortableSize = wordArray.size();
    for (int i = 0; i < sortableSize; i++){
        sortableArray[i] = wordArray[i];
    }
    return true;
}

//Used to compare the relative value of one char* to another
//It is used by qsort to sort through each of the sets of words
int SortingCompetition :: StringCompare(const void* a, const void* b){
    char const* char_a = *(char const**)a;
    char const* char_b = *(char const**)b;
    return strcmp(char_a, char_b);
}

//Sorts the words by calling radixSort
void SortingCompetition :: sortData(){
    radixSort(sortableArray);
}

//Uses radix sort functionality to sort the words based on length
//Organizes the words into sub arrays containing words of the same length
void SortingCompetition :: radixSort(char**& words){
    char** zeros = new char*[radixHelper[0][10]];
    char** ones = new char*[radixHelper[1][10]];
    char** twos = new char*[radixHelper[2][10]];
    char** threes = new char*[radixHelper[3][10]];
    char** fours = new char*[radixHelper[4][10]];
    char** fives = new char*[radixHelper[5][10]];
    int zerosC = 0;
    int onesC = 0;
    int twosC = 0;
    int threesC = 0;
    int foursC = 0;
    int fivesC = 0;

    //Sorts words based on the digit in the ten's place of the word length
    for (int i = 0; i < sortableSize; i++){
        switch(words[i][0] - '0'){
        case 0:
            zeros[zerosC] = words[i];
            zerosC++;
            break;
        case 1:
            ones[onesC] = words[i];
            onesC++;
            break;
        case 2:
            twos[twosC] = words[i];
            twosC++;
            break;
        case 3:
            threes[threesC] = words[i];
            threesC++;
            break;
        case 4:
            fours[foursC] = words[i];
            foursC++;
            break;
        case 5:
            fives[fivesC] = words[i];
            fivesC++;
            break;
        }
    }

    //Calls innerSort to sort the size arrays into smaller, sub catagories
    //that are sorted based on the digit in the one's place
    innerSort(zeros, zerosC, 0);
    innerSort(ones, onesC, 1);
    innerSort(twos, twosC, 2);
    innerSort(threes, threesC, 3);
    innerSort(fours, foursC, 4);
    innerSort(fives, fivesC, 5);

    //Calls radixMerge to merge all the arrays created in this function
    //into one, full sized array which contains all the words that were sorted
    int location = 0;
    radixMerge(words, zeros, location, zerosC);
    radixMerge(words, ones, location, onesC);
    radixMerge(words, twos, location, twosC);
    radixMerge(words, threes, location, threesC);
    radixMerge(words, fours, location, foursC);
    radixMerge(words, fives, location, fivesC);
    return;

}

//This is the second half of the radixSort functionality.
//This sorts the words into smaller sub catigories than radixSort did
//Each sub catagory is quicksorted  to put it into alphabetical order
void SortingCompetition :: innerSort(char**& words, int size, int biggerNum){
    char** zeros = new char*[radixHelper[biggerNum][0]];
    char** ones = new char*[radixHelper[biggerNum][1]];
    char** twos = new char*[radixHelper[biggerNum][2]];
    char** threes = new char*[radixHelper[biggerNum][3]];
    char** fours = new char*[radixHelper[biggerNum][4]];
    char** fives = new char*[radixHelper[biggerNum][5]];
    char** sixes = new char*[radixHelper[biggerNum][6]];
    char** sevens = new char*[radixHelper[biggerNum][7]];
    char** eights = new char*[radixHelper[biggerNum][8]];
    char** nines = new char*[radixHelper[biggerNum][9]];
    int zerosC = 0;
    int onesC = 0;
    int twosC = 0;
    int threesC = 0;
    int foursC = 0;
    int fivesC = 0;
    int sixesC = 0;
    int sevensC = 0;
    int eightsC = 0;
    int ninesC = 0;

    //Sorts words based on the digit in the one's place of the word length
    for (int i = 0; i < size; i++){
        switch(words[i][1] - '0'){
        case 0:
            zeros[zerosC] = words[i];
            zerosC++;
            break;
        case 1:
            ones[onesC] = words[i];
            onesC++;
            break;
        case 2:
            twos[twosC] = words[i];
            twosC++;
            break;
        case 3:
            threes[threesC] = words[i];
            threesC++;
            break;
        case 4:
            fours[foursC] = words[i];
            foursC++;
            break;
        case 5:
            fives[fivesC] = words[i];
            fivesC++;
            break;
        case 6:
            sixes[sixesC] = words[i];
            sixesC++;
            break;
        case 7:
            sevens[sevensC] = words[i];
            sevensC++;
            break;
        case 8:
            eights[eightsC] = words[i];
            eightsC++;
            break;
        case 9:
            nines[ninesC] = words[i];
            ninesC++;
            break;
        }
    }

    //Each sub array is sorted alphabetically using quick sort
    int location = 0;

    qsort(zeros, zerosC, sizeof(char*), StringCompare);
    radixMerge(words, zeros, location, zerosC);

    qsort(ones, onesC, sizeof(char*), StringCompare);
    radixMerge(words, ones, location, onesC);

    qsort(twos, twosC, sizeof(char*), StringCompare);
    radixMerge(words, twos, location, twosC);

    qsort(threes, threesC, sizeof(char*), StringCompare);
    radixMerge(words, threes, location,threesC);

    qsort(fours, foursC, sizeof(char*), StringCompare);
    radixMerge(words, fours, location,foursC);

    qsort(fives, fivesC, sizeof(char*), StringCompare);
    radixMerge(words, fives, location,fivesC);

    qsort(sixes, sixesC, sizeof(char*), StringCompare);
    radixMerge(words, sixes, location,sixesC);

    qsort(sevens, sevensC, sizeof(char*), StringCompare);
    radixMerge(words, sevens, location,sevensC);

    qsort(eights, eightsC, sizeof(char*), StringCompare);
    radixMerge(words, eights, location,eightsC);

    qsort(nines, ninesC, sizeof(char*), StringCompare);
    radixMerge(words, nines, location,ninesC);
}

//Merges all the sub catagories created by radixSort and innerSort into one, full sized array
void SortingCompetition ::  radixMerge(char**& result, char**& number, int& startLocation, int size){
    int counter = 0;
    for (int i = startLocation; i < startLocation + size; i++){
        result[i] = number[counter];
        counter++;
    }
    startLocation += counter;
}

//Outputs the sorted file to the output file specified
void SortingCompetition :: outputData(const string& outputFileName){
    ofstream fout(outputFileName.c_str());

    fout << "Sorted Array: "<< wordArray.size() << " words" << endl;
    char* buff = new char[3];
    for (int i = 0; i < sortableSize; i++){
        buff[0] = sortableArray[i][0];
        buff[1] = sortableArray[i][1];
        for (int x = 2; x < atoi(buff) + 2; x++){
            fout << sortableArray[i][x];
        }
        fout << endl;
    }
    delete [] buff;
}

//Destructor
SortingCompetition :: ~SortingCompetition(){
    for (int i = 0; i < sortableSize; i++){
        delete [] sortableArray[i];
    }
    delete [] sortableArray;
    wordArray.clear();
}
