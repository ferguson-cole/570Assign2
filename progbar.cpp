/*
I the undersigned promise that the attached assignment is my own work. 
While I was free to discuss ideas with others, the work contained is my own.
I recognize that should this not be the case, I will be subject to penalties 
as outlined in the course syllabus.
Cole Ferguson, RedID - 820562542
*/
#include <stdio>
#include <cstring>
#include <ifstream>
#define FILE_ERR -2

using namespace std;

int main(int argc, char const *argv[])
{
    // As of right now, only setting up for one argument
    if(argc <= 0) cout << "No file specified.";
    else if (argc >= 2) cout << "Too many arguments provided.";

    // Call the wordcount function
    long count = wordcount(argv[0]);

    if(count > -1) cout << "There are " << count << " words in " << argv[0] << ".";
    else if (count == FILE_ERR) cout << "Could not open file.";
    else cout << "An error has occurred. Word count unknown.";
}

void * progress_monitor(void *) {
    typedef struct {
        long *CurrentStatus;
        long InitialValue;
        long TerminationValue;
    } PROGRESS_STATUS;
    return;
}

long wordcount(char *fd) {
    try
    {
        fstream;
    }
    catch(const exception& e)
    {
        return FILE_ERR;
    }
    
    return -1;
}