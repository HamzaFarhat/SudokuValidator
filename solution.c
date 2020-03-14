#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int solution[9][9]; //Set as global array
int valid = 0;

void *rowChecker(void)
{
    // int *arr=(int *)received_arr; 
    for (int ROWNUMB=0; ROWNUMB<9; ROWNUMB++) 
    {
		for (int ii = 0; ii < 9; ii++)
        {
			//check for duplicate #'s
            for(int k = ii + 1; k < 9; k++) {    
				if(solution[ROWNUMB][ii] == solution[ROWNUMB][k])  
					   //if thers a duplicate set valid to 1 (which means invalid)
					   valid = 1;
			}    
        }
    }
}

void *colChecker(void)
{
    // int *arr=(int *)received_arr; 
    for (int COLNUMB=0; COLNUMB<9; COLNUMB++) 
    {
		for (int ii = 0; ii < 9; ii++)
        {
			//check for duplicate #'s
            for(int k = ii + 1; k < 9; k++) {    
				if(solution[ii][COLNUMB] == solution[k][COLNUMB])  
					   //if thers a duplicate set valid to 1 (which means invalid)
					   valid = 1;
			}    
        }
    }
}

void *grid1_Checker(void)
{
	//initializes array for the counter of digits 0 to 9
    int grid[10] = {0};
	
	for (int jj = 0; jj < 3; jj++)
    {
        for (int ii = 0; ii < 3; ii++)
        {
			if(solution[jj][ii] != 0){

				//Add one to the counter for the digit
				grid[solution[jj][ii]] += 1;
            }
			
			//if a digit appears twice then sub grid is unvalid
            if(grid[solution[jj][ii]] >= 2){
                    valid = 1;
			}
		}
    }
}

void *grid2_Checker(void){
    int grid[10] = {0};
	for (int jj = 0; jj < 3; jj++){
        for (int ii = 3; ii < 6; ii++){
			if(solution[jj][ii] != 0)
				grid[solution[jj][ii]] += 1;
            if(grid[solution[jj][ii]] >= 2)
                    valid = 1;
		}
    }
}
void *grid3_Checker(void){
    int grid[10] = {0};
	for (int jj = 0; jj < 3; jj++){
        for (int ii = 6; ii < 9; ii++){
			if(solution[jj][ii] != 0)
				grid[solution[jj][ii]] += 1;
            if(grid[solution[jj][ii]] >= 2)
                    valid = 1;
		}
    }
}
void *grid4_Checker(void){
    int grid[10] = {0};
	for (int jj = 3; jj < 6; jj++){
        for (int ii = 0; ii < 3; ii++){
			if(solution[jj][ii] != 0)
				grid[solution[jj][ii]] += 1;
            if(grid[solution[jj][ii]] >= 2)
                    valid = 1;
		}
    }
}
void *grid5_Checker(void){
    int grid[10] = {0};
	for (int jj = 3; jj < 6; jj++){
        for (int ii = 3; ii < 6; ii++){
			if(solution[jj][ii] != 0)
				grid[solution[jj][ii]] += 1;
            if(grid[solution[jj][ii]] >= 2)
                    valid = 1;
		}
    }
}
void *grid6_Checker(void){
    int grid[10] = {0};
	for (int jj = 3; jj < 6; jj++){
        for (int ii = 6; ii < 9; ii++){
			if(solution[jj][ii] != 0)
				grid[solution[jj][ii]] += 1;
            if(grid[solution[jj][ii]] >= 2)
                    valid = 1;
		}
    }
}
void *grid7_Checker(void){
    int grid[10] = {0};
	for (int jj = 6; jj < 9; jj++){
        for (int ii = 0; ii < 3; ii++){
			if(solution[jj][ii] != 0)
				grid[solution[jj][ii]] += 1;
            if(grid[solution[jj][ii]] >= 2)
                    valid = 1;
		}
    }
}
void *grid8_Checker(void){
    int grid[10] = {0};
	for (int jj = 6; jj < 9; jj++){
        for (int ii = 3; ii < 6; ii++){
			if(solution[jj][ii] != 0)
				grid[solution[jj][ii]] += 1;
            if(grid[solution[jj][ii]] >= 2)
                    valid = 1;
		}
    }
}
void *grid9_Checker(void){
    int grid[10] = {0};
	for (int jj = 6; jj < 9; jj++){
        for (int ii = 6; ii < 9; ii++){
			if(solution[jj][ii] != 0)
				grid[solution[jj][ii]] += 1;
            if(grid[solution[jj][ii]] >= 2)
                    valid = 1;
		}
    }
}

int main(void)
{
    FILE *f;
    int ii, jj, column = 9, row = 9;

    if ((f = fopen("puzzle.txt", "r")) == NULL)
        exit(1);

    //jj is the row
	//ii is the column
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


 for (jj = 0; jj < row; jj++)
    {
        for (ii = 0; ii < column; ii++)
        {
            printf("%d ", solution[jj][ii]);
			//checking if there are any 0's, if ther are it is invalid
			if (solution[jj][ii] <= 0 || solution[jj][ii] > 9)
				valid = 1;
        }
        printf("\n");
    } 
	printf("\n^Sudoku File Read^\n\n");

    pthread_t row_tid, col_tid;
	pthread_t g_tid[9];
	
	//11 threads
    pthread_create(&row_tid, NULL, rowChecker, NULL); 
	pthread_create(&col_tid, NULL, colChecker, NULL);

	pthread_create(&(g_tid[0]), NULL, grid1_Checker, NULL);
	pthread_create(&(g_tid[1]), NULL, grid2_Checker, NULL);
	pthread_create(&(g_tid[2]), NULL, grid3_Checker, NULL);
	pthread_create(&(g_tid[3]), NULL, grid4_Checker, NULL);
	pthread_create(&(g_tid[4]), NULL, grid5_Checker, NULL);
	pthread_create(&(g_tid[5]), NULL, grid6_Checker, NULL);
	pthread_create(&(g_tid[6]), NULL, grid7_Checker, NULL);
	pthread_create(&(g_tid[7]), NULL, grid8_Checker, NULL);
	pthread_create(&(g_tid[8]), NULL, grid9_Checker, NULL);

	pthread_join(row_tid, NULL); 
	pthread_join(col_tid, NULL);
	for (int z=0; z<9; z++){
		pthread_join(g_tid[z], NULL);
	}


	if (valid == 1)
		printf("\n It is a invalid solution \n\n");
	else
		printf("\n It is a valid solution \n\n");
    return 0;
}
