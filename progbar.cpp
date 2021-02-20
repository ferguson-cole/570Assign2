/*
I the undersigned promise that the attached assignment is my own work. 
While I was free to discuss ideas with others, the work contained is my own.
I recognize that should this not be the case, I will be subject to penalties 
as outlined in the course syllabus.
Cole Ferguson, RedID - 820562542
*/
#include <iostream>     // i/o
#include <fstream>      // file handling
#include <pthread.h>    // thread
#include <sys/stat.h>   // stat
#include <string>       // strings
#include <cwctype>      // iswspace
#include <stdlib.h>       // malloc/free

#define FILE_ERR -2

using namespace std;

// Set up PROGRESS_STATUS struct
typedef struct {
        long *CurrentStatus;
        long InitialValue;
        long TerminationValue;
} PROGRESS_STATUS;

/* progress_monitor()
 * Prints a 'progress bar' to the console, indicating the progress
 * made by wordcount(). Prints 50 characters total, with a '+'
 * indicator every 10 characters (20% of bar).
 * Example:
 * ---------+---------+---------+---------+---------+
 *
 * Arguments:
 * arg - pointer to a PROGRESS_STATUS object for retrieving progress
 */
void * progress_monitor(void *arg) {
    PROGRESS_STATUS status = *((PROGRESS_STATUS*)arg);
    int charsPrinted = 0;
    
    while( (*status.CurrentStatus < status.TerminationValue)  || (charsPrinted < 50) ) { // Loop while we're still counting OR we haven't printed the whole bar
        double ratio = (*status.CurrentStatus) / double(status.TerminationValue);
        int charsToPrint = (int) (ratio * 50);
        // Print the progress bar here:
        while( charsPrinted < charsToPrint && charsPrinted < 50) { // print while we still have characters to print AND we haven't printed the whole bar
            if( (charsPrinted+1)%10 == 0) { // If the upcoming printed character is div by 10, print a seperator: '+'
                cout << "+" << flush;
            }
            else { // Otherwise we print the std '-' part of our bar
                cout << "-" << flush;
            }
            charsPrinted++; // increment the number of characters that have been printed
        }
    }
    // Print a newline to cout, as specified in the assignment...
    cout << endl;
    return NULL;
}

/* wordcount()
 * Counts the number of words in a file, and stores its progress in
 * a PROGRESS_STATUS structure. Creates a seperate thread for
 * progress_monitor().
 *
 * Arguments:
 * filename - File that will be used to simulate the device.
 * 
 * Returns:
 * the number of words in the file.
 */
long wordcount(const char *filename) {
    int fileSize = 0;
    struct stat fileDetails;
    pthread_t id;

    try {
        // Populate our file stat object
        stat(filename, &fileDetails);
        // Get the size from the file stat structure
        fileSize = (int) fileDetails.st_size;
    }
    catch(const exception &e) {
        cerr << e.what() << '\n';
    }

    // Create a new PROGRESS_STATUS
    PROGRESS_STATUS status;
    long zero = 0;
    status.CurrentStatus = &zero;
    status.InitialValue = 0;
    status.TerminationValue = fileSize;

    // Create the progress bar thread
    pthread_create(&id, NULL, progress_monitor, (void *)&status); 

    ifstream file(filename);
    string currentLine;
    long numWords = 0;
    int nonWhitespaceCount;

    // If we cannot open the file, return the corresponding error
    if ( !file.is_open() ) return FILE_ERR;

    // Loop through the file line by line
    while ( getline(file, currentLine) ) {
        nonWhitespaceCount = 0; // At the start of new line, reset non whitespace char count

        /*  Use string::size_type bc it can hold a str of any size
            Using size() instead of length() to get the amount of bytes in the string */
        for (string::size_type i = 0; i < currentLine.size(); i++) { 

            /*  Could update currentstatus line by line as opposed to character by character for better performance...
                I chose to do char by char to have more frequent updates to the prog bar (only matters for smaller files really)
                This gives the impression of a 'smoother' progress bar */

            (*status.CurrentStatus)++; // Increment the current status to advance the progress bar

            if ( iswspace( currentLine[i] ) ) {
                if ( nonWhitespaceCount > 0 ) {
                    numWords++;             // increment the total number of words
                    nonWhitespaceCount = 0; // reset number of non WS chars
                }
            }
            else {
                nonWhitespaceCount++;
            }
        }
        /*  If we're here, we've reached the end of a line...
            If we still have non whitespace chars left, increment our total word count
            This only applys when our line ends without a whitespace e.g. "this is a test"
            w/out this check the above line will return 3 words because we only hit 3 whitespaces... */
        if ( nonWhitespaceCount > 0 ) numWords++; // Don't need to reset nonWS count, will be reset next line (top of loop)

        // Since getline() removes a deliminitor ('\n' in our case), add an additional byte to currentstatus to account for it
        (*status.CurrentStatus)++; 
    }
    file.close(); // We need to close the file stream after we're done...

    pthread_join(id, NULL);   // Wait for progress_monitor() to finish

    return numWords;
}

/* main()
 * Entry point of the program, handles all errors with the exception of file permission errors (handled in wordcount()).
 * Calls wordcount() with the filename provided when program is called.
 *
 * Arguments:
 * argc - number of command line arguments
 * argv - array of provided command line arguments
 */
int main(int argc, char const *argv[]) {
    // Handle argument count errors:
    if(argc <= 1) cout << "No file specified." << "\n";
    else if (argc >= 3) cout << "Too many arguments provided." << "\n";
    
    // Call the wordcount function
    long count = wordcount(argv[1]);

    // Handle word count errors (or output if successful):
    if( count > -1 ) cout << "There are " << count << " words in " << argv[1] << "." << "\n";
    else if ( count == FILE_ERR ) cout << "Could not open file." << "\n";
    else cout << "An error has occurred. Word count unknown." << "\n";
}
