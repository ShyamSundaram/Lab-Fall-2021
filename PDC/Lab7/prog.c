#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define M 1000
#define N 1000
#define I 1000
#define V 10000000

int** initArray(int r,int c,int u,int l)
{
    srand(time(0));

    int** arr=(int**)malloc(r*sizeof(int*));
    for(int i=0;i<r;++i)
        arr[i]=(int*)malloc(c*sizeof(int));


    if(u!=l && l!=0 && u!=0)                            //initializes each element to a random array if lower (l) and uper (u) vales are different
    for(int i=0;i<r;++i)
        for(int j=0;j<c;++j)
            arr[i][j]=(rand()%(u-l+1))+l;


    if(l==0 && u==0)                                    //initialize elements to 0 if l and u are 0
    for(int i=0;i<r;++i)
        for(int j=0;j<c;++j)
            arr[i][j]=0;
    
    return arr;
}

void freeArray(int** arr,int r)
{
    for(int i=0;i<r;++i)
    free(arr[i]);

    free(arr);
}

void MatAdd()
{
    //init array
    printf("Starting Matrix addition...\n");

    printf("Initialising arrays...\n");
    int** a=initArray(M,N,100,1);
    int** b=initArray(M,N,100,1);
    int** c=initArray(M,N,1,1);

    printf("Performing addition...\n");
    for(int i=0;i<M;++i)
        for(int  j=0;j<N;++j)
            c[i][j]=a[i][j]+b[i][j];

    printf("Finished addition...\n");
    printf("Freeing Arrays...\n\n");
    freeArray(a,M);
    freeArray(b,M);
    freeArray(c,M);
}

void MatMul()
{
    //init array
    printf("Starting Matrix Multiplication...\n");

    printf("Initialising arrays...\n");
    int** a=initArray(M,I,100,1);
    int** b=initArray(I,N,100,1);
    int** c=initArray(M,N,0,0);

    printf("Performing Multiplication...\n");
    for(int i=0;i<M;++i)
        for(int j=0;j<N;++j)
            for(int k=0;k<I;++k)
                c[i][j]+=a[i][k]*b[k][j];


    printf("Finished Multiplication...\n");
    printf("Freeing Arrays...\n\n");
    freeArray(a,M);
    freeArray(b,M);
    freeArray(c,M);
}

void MatSub()
{
    //init array
    printf("Starting Matrix Subtraction...\n");

    printf("Initialising arrays...\n");
    int** a=initArray(M,N,100,1);
    int** b=initArray(M,N,100,1);
    int** c=initArray(M,N,1,1);

    printf("Performing subtraction...\n");
    for(int i=0;i<M;++i)
        for(int  j=0;j<N;++j)
            c[i][j]=a[i][j]-b[i][j];

    printf("Finished subtraction...\n");
    printf("Freeing Arrays...\n\n");
    freeArray(a,M);
    freeArray(b,M);
    freeArray(c,M);
}

void isDiagonal()
{
    //init array
    printf("Starting isDiagonal...\n");
    int flag=1;
    printf("Initialising array...\n");
    int** a=initArray(N,N,100,1);

    printf("Examining...\n");
    for(int i=0;i<N;++i)
    {
        for(int  j=0;j<N;++j)
        if(i!=j && a[i][j]!=0)
        {
            flag=1;
            break;
        }
        if(flag==1)
        break;
    }
    if(flag==1)
    printf("Not a diagonal matrix\n");
    else
    printf("Is a diagoal matrix\n");
    printf("Freeing Array...\n\n");
    freeArray(a,N);
}

void isSymmetric()
{
    //init array
    printf("Starting isSymmetric...\n");
    int flag=1;
    printf("Initialising array...\n");
    int** a=initArray(N,N,100,1);

    printf("Examining...\n");
    for(int i=0;i<N;++i)
    {
        for(int  j=0;j<N;++j)
        if(a[i][j]!=a[j][i])
        {
            flag=1;
            break;
        }
        if(flag==1)
        break;
    }
    if(flag==1)
    printf("Not a symmetric matrix\n");
    else
    printf("Is a symmetric matrix\n");
    printf("Freeing Array...\n\n");
    freeArray(a,N);
}


void prefix()
{
    printf("Initialising arrays...\n");
    long *x=(long*)malloc(V*sizeof(long));
    for(int i=0;i<V;++i)
    x[i]=i;

    long *y=(long*)malloc(V*sizeof(long));

    y[0]=x[0];

    printf("Summing prefixes...\n");
    for(int i=1;i<V;++i)
    y[i]=y[i-1]+x[i];

    printf("Summation done. Freeing arrays...\n\n");
    free(x);
    free(y);
}

int main()
{
    MatMul();
    MatAdd();
    MatSub();
    isSymmetric();
    isDiagonal();
    prefix();
    
    return 0;
}