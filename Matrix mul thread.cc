#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct{
    int row,col;
}index;

int row1,row2,col1,col2;
int **matrix1, **matrix2, **result;
void read(const char* filename){
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
void *element(void *elements)
{
    index *element_index=(index*)elements;
    int sum=0;
    for(int k=0;k<col1;k++)
    {
        sum+=matrix1[element_index->row][k]*matrix2[k][element_index->col];
    }
    result[element_index->row][element_index->col]=sum;
    free(elements);
    return NULL;
}
void matrixmul(){
    pthread_t threads[row1*col2];
    int counter=0;
    clock_t start_time=clock();
    for(int i=0;i<row1;i++)
    {
        for(int j=0;j<col2;j++)
        {
            index *indexx=(index*)malloc(sizeof(index));
            indexx->row=i;
            indexx->col=j;
            pthread_create(&threads[counter++],NULL,element,indexx);
        }
    }
    for(int i=0;i<counter;i++)
    {
        pthread_join(threads[i],NULL);
    }
    clock_t end_time=clock();
    printf("Time taken is: %f seconds\n",(double)(end_time-start_time)/CLOCKS_PER_SEC);
}
void free_matrices() {
    for (int i = 0; i < row1; i++) free(matrix1[i]);
    for (int i = 0; i < row2; i++) free(matrix2[i]);
    for (int i = 0; i < row1; i++) free(result[i]);
    free(matrix1);
    free(matrix2);
    free(result);
}
int main()
{
    read("test.txt");
    if(col1!=row2)
    {
        printf("incompatible matrices sizes");
        free_matrices();
        return 1;

    }
    matrixmul();
    free_matrices();
    return 0;
}
