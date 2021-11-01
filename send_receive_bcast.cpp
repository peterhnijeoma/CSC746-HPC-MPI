#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int the_number = -1;
    if (rank == 0)
    {
       the_number = 42;
    }

    //everyone participates in MPI_Bcast.
    int sender_rank = 0;
    MPI_Bcast(&the_number, 1, MPI_INT, sender_ransk, MPI_COMM_WORLD);
    
    // now the receivers will add one to the number and send results back to primary
    if (rank != 0)
    {
        printf("I am rank %d of %d total ranks, I am sending %d to all the other ranks.\n", rank, size, the_number);
        
        // now add rank to the received number and send ot back to the primary
        the_number += rank;
        MPI_Send(&the_number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else // rank == 0
    {
        int return_values[size];
        MPI_Status status;

        // now receive results back from each of the other ranks
        return_values[0] = 0; // no sender at this index
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&(return_values[i]), 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            printf("Primary rank received %d from rank %d.\n", return_values[i], i);
        }
    }
    
    MPI_Finalize();
}