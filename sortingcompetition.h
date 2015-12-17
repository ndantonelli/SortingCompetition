#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H
#include <string>
#include <vector>

using std :: string;
using std :: vector;

class SortingCompetition
{
public:
    SortingCompetition(const string&);
    void setFileName(const string&);
    bool readData();
    bool prepareData();
    void sortData();
    void outputData(const string&);
    ~SortingCompetition();
private:
    static int StringCompare(const void*, const void*);
    void radixSort(char**&);
    void innerSort(char**&, int, int);
    void radixMerge(char**&, char**&, int&, int);
    int sortableSize;
    int** radixHelper;
    char** sortableArray;
    vector <char*> wordArray;
    string fileName;
};

#endif // SORTINGCOMPETITION_H
