/*
I the undersigned promise that the attached assignment is my own work. 
While I was free to discuss ideas with others, the work contained is my own.
I recognize that should this not be the case, I will be subject to penalties 
as outlined in the course syllabus.
Cole Ferguson, RedID - 820562542
*/
#include <iostream>     // i/o
#include <fstream>      // file handling
#include <thread>       // thread
#include <sys/stat.h>   // stat

#define FILE_ERR -2

using namespace std;


typedef struct {
        long *CurrentStatus;
        long InitialValue;
        long TerminationValue;
} PROGRESS_STATUS;


void * progress_monitor(void *) {
    // typedef struct {
    //     long *CurrentStatus;
    //     long InitialValue;
    //     long TerminationValue;
    // } PROGRESS_STATUS;
}


long wordcount(const char *filename) {
    int fileSize = 0;
    struct stat fileDetails;
    try
    {
        // Populate our file stat object
        stat(filename, &fileDetails);
        // Get the size from the file stat structure
        fileSize = (int) fileDetails.st_size;
    }
    catch(const exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    
    struct {
        long *CurrentStatus;
        long InitialValue = 0;
        long TerminationValue;
    } PROGRESS_STATUS;

    PROGRESS_STATUS.TerminationValue = fileSize;

    ifstream file(filename);

    thread progressMonitor(progress_monitor, PROGRESS_STATUS);

    // Error handling (no arguments handled in main, file errors handled here)
    if ( !file.is_open() ) return FILE_ERR;


    // Wait for progress_monitor() to finish
    progressMonitor.join();
    return -1;
}


int main(int argc, char const *argv[])
{
    // As of right now, only setting up for one argument
    if(argc <= 0) cout << "No file specified.";
    else if (argc >= 2) cout << "Too many arguments provided.";

    // Call the wordcount function
    long count = wordcount(argv[0]);

    if( count > -1 ) cout << "There are " << count << " words in " << argv[0] << ".";
    else if ( count == FILE_ERR ) cout << "Could not open file.";
    else cout << "An error has occurred. Word count unknown.";
}