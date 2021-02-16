#include <stdio>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[])
{
    // As of right now, only setting up for one argument
    if(argc <= 0) printf("No file specified.");
    else if (argc >= 2) printf("Too many arguments provided.");

    // Call the wordcount function
    long count = wordcount();
    if(count == nullptr) printf("An error has occurred. Word count unknown.");
    string filename = "placeholder.txt";
    else printf("There are %ld words in %s.", count, filename);
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
    return 55;
}