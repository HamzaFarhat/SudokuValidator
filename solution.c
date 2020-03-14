#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int solution[9][9]; //Set as global array

void* rowChecker(void)
{
    // int *arr=(int *)received_arr; 
    for (int i=0; i<9; i++) //just checking one row
    {
        int num = *solution[i]; 
        if(num<1 || num >9)
        {
            printf("Invalid");
        }
        else
        {
            printf("valid"); 
        }
        
    }
}

// void *columnChecker(void *args)
// {
//     printf("Goodbye\n");
//     sleep(2);
// }

int main(void)
{
    FILE *f;
    int ii, jj, column = 9, row = 9;
    int solution[9][9];

    if ((f = fopen("puzzle.txt", "r")) == NULL)
        exit(1);

    
    //This saves it to the 2D array as int not char 
    for (jj = 0; jj < row; jj++)
    {
        for (ii = 0; ii < column; ii++)
        {
            if (fscanf(f, "%d", &solution[jj][ii]) != 1)
                exit(1);
        }
    }
    fclose(f);

    //ii reads all the columns and jj is row
    for (jj = 0; jj < row; jj++)
    {
        for (ii = 0; ii < column; ii++)
        {
            // printf("%d ", solution[jj][ii]);
        }
        // printf("\n");
    }

    pthread_t firstThread, secondThread;
    pthread_create(&firstThread, NULL, rowChecker, NULL); 

    // if (pthread_create(&secondThread, NULL, &columnChecker, NULL))
    // {
    //     printf("Could not create thread\n");
    //     return -1;
    // }

    return 0;
}
