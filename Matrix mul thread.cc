#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct{
    int row,col;
}index;

int row1,row2,col1,col2;
int **matrix1, **matrix2, **result;
void read(char* filename){
    FILE *f=fopen(filename,"r");
    if(f==NULL){
        perror("Can't open file");
        exit(EXIT_FAILURE);
    }
    fscanf(f,"%d %d",&row1,&col1);
    matrix1=(int **)malloc(row1 * sizeof(int *));
    for (int i=0;i<row1;i++)
    {
        matrix1[i]=(int *)malloc(col1 * sizeof(int));
        for(int j=0;j<col1;j++)
        {
            fscanf(f,"%d",&matrix1[i][j]);
        }
    }
    fscanf(f,"%d %d",&row2,&col2);
    matrix2=(int **)malloc(row2 * sizeof(int *));
    for (int i=0;i<row2;i++)
    {
        matrix2[i]=(int *)malloc(col2 * sizeof(int));
        for(int j=0;j<col2;j++)
        {
            fscanf(f,"%d",&matrix2[i][j]);
        }
    }
    fclose(f);
    result=(int **)malloc(row1*sizeof(int*));
    for(int i=0;i<row1;i++)
    {
        result[i]=(int *)malloc(col2*sizeof(int));
    }

}
