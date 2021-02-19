/*
I the undersigned promise that the attached assignment is my own work. 
While I was free to discuss ideas with others, the work contained is my own.
I recognize that should this not be the case, I will be subject to penalties 
as outlined in the course syllabus.
Cole Ferguson, RedID - 820562542
*/
#include <iostream>     // i/o
#include <fstream>      // file handling
#include <pthread.h>      // thread
#include <sys/stat.h>   // stat

#define FILE_ERR -2

using namespace std;


typedef struct {
        long *CurrentStatus;
        long InitialValue;
        long TerminationValue;
} PROGRESS_STATUS;


void * progress_monitor(void *arg) {
    // typedef struct {
    //     long *CurrentStatus;
    //     long InitialValue;
    //     long TerminationValue;
    // } PROGRESS_STATUS;
    PROGRESS_STATUS status = &((PROGRESS_STATUS*)arg);
    cout << "ValueInitial: " << status.InitialValue;
    return NULL;
}


long wordcount(const char *filename) {
    int fileSize = 0;
    struct stat fileDetails;
    pthread_t id;

    // Set up PROGRESS_STATUS structure
    typedef struct {
        long *CurrentStatus;
        long InitialValue;
        long TerminationValue;
    } PROGRESS_STATUS;
    // Create a new PROGRESS_STATUS
    PROGRESS_STATUS status;

    try
    {
        // Populate our file stat object
        stat(filename, &fileDetails);
        // Get the size from the file stat structure
        fileSize = (int) fileDetails.st_size;
    }
    catch(const exception &e)
    {
        cerr << e.what() << '\n';
    }

    status.CurrentStatus = 0;
    status.InitialValue = 0;
    status.TerminationValue = fileSize;

    ifstream file(filename);

    pthread_create(&id, NULL, progress_monitor, (void *)&status);

    // If we cannot open the file, return the corresponding error
    if ( !file.is_open() ) return FILE_ERR;


    // Wait for progress_monitor() to finish
    pthread_join(id, NULL);
    return -1;  // If we make it all the way to the end without returning anything, return an error
}


int main(int argc, char const *argv[])
{
    // Conditional test for argument count
    if(argc <= 0) cout << "No file specified.";
    else if (argc >= 2) cout << "Too many arguments provided.";

    // Call the wordcount function
    long count = wordcount(argv[0]);

    if( count > -1 ) cout << "There are " << count << " words in " << argv[0] << ".";
    else if ( count == FILE_ERR ) cout << "Could not open file.";
    else cout << "An error has occurred. Word count unknown.";
}