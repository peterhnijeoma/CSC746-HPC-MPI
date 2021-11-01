#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char hostname[256];
    gethostname(hostname, sizeof(hostname)); // linux -only call

    printf("I am rank %d of %d total ranks running on <%s>.\n", rank, size, hostname);
    MPI_Finalize();
}