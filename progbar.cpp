#include <stdio>
#include <cstring>
#include <ifstream>

using namespace std;

int main(int argc, char const *argv[])
{
    // As of right now, only setting up for one argument
    if(argc <= 0) printf("No file specified.");
    else if (argc >= 2) printf("Too many arguments provided.");

    // Call the wordcount function
    long count = wordcount(argv[0]);

    if(count > -1) printf("There are %ld words in %s.", count, filename);
    else printf("An error has occurred. Word count unknown.");
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
    return -1;
}