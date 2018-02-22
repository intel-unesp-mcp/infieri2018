#include <stdint.h>
#include <stdio.h>

int main()
{
    char hostname[1024];
    printf("Running on host: ");
    gethostname(hostname, 1024);
    puts(hostname);

    #pragma omp target
    {
        printf("Running on target: ");
        gethostname(hostname, 1024);
        puts(hostname);

    }

    return 0;
}

