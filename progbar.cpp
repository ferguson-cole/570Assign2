#include <stdio.h>

int main(int argc, char const *argv[])
{
    if(argc <= 0) printf("No file specified.");
}



void * progress_monitor(void *) {
    typedef struct {
        long *CurrentStatus;
        long InitialValue;
        long TerminationValue;
    } PROGRESS_STATUS;
}