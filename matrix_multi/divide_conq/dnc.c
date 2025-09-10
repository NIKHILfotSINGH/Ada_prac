#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void add(int n,int A[][n],int B[][n],int C[][n]){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j]=A[i][j]+B[i][j];
}

void subtract(int n,int A[][n],int B[][n],int C[][n]){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j]=A[i][j]-B[i][j];
}

void multiply_divide(int n,int A[][n],int B[][n],int C[][n]){
    if(n==1){C[0][0]=A[0][0]*B[0][0];return;}
    int mid=n/2;
    int A11[mid][mid],A12[mid][mid],A21[mid][mid],A22[mid][mid];
    int B11[mid][mid],B12[mid][mid],B21[mid][mid],B22[mid][mid];
    int C11[mid][mid],C12[mid][mid],C21[mid][mid],C22[mid][mid];
    int T1[mid][mid],T2[mid][mid];

    for(int i=0;i<mid;i++) for(int j=0;j<mid;j++){
        A11[i][j]=A[i][j]; A12[i][j]=A[i][j+mid];
        A21[i][j]=A[i+mid][j]; A22[i][j]=A[i+mid][j+mid];
        B11[i][j]=B[i][j]; B12[i][j]=B[i][j+mid];
        B21[i][j]=B[i+mid][j]; B22[i][j]=B[i+mid][j+mid];
    }

    multiply_divide(mid,A11,B11,T1); multiply_divide(mid,A12,B21,T2); add(mid,T1,T2,C11);
    multiply_divide(mid,A11,B12,T1); multiply_divide(mid,A12,B22,T2); add(mid,T1,T2,C12);
    multiply_divide(mid,A21,B11,T1); multiply_divide(mid,A22,B21,T2); add(mid,T1,T2,C21);
    multiply_divide(mid,A21,B12,T1); multiply_divide(mid,A22,B22,T2); add(mid,T1,T2,C22);

    for(int i=0;i<mid;i++) for(int j=0;j<mid;j++){
        C[i][j]=C11[i][j]; C[i][j+mid]=C12[i][j];
        C[i+mid][j]=C21[i][j]; C[i+mid][j+mid]=C22[i][j];
    }
}

int main(){
    srand(time(NULL));
    FILE *fp=fopen("divide.txt","w"); if(!fp) return 1;

    int sizes[]={2,4,8,16,32,64,128,256};
    int num=sizeof(sizes)/sizeof(sizes[0]);
    int trials=5;

    for(int s=0;s<num;s++){
        int n=sizes[s];
        int (*A)[n]=malloc(sizeof(int[n][n]));
        int (*B)[n]=malloc(sizeof(int[n][n]));
        int (*C)[n]=malloc(sizeof(int[n][n]));
        if(!A||!B||!C) continue;

        double total=0.0;
        for(int t=0;t<trials;t++){
            for(int i=0;i<n;i++) for(int j=0;j<n;j++){A[i][j]=rand()%10;B[i][j]=rand()%10;}
            clock_t start=clock();
            multiply_divide(n,A,B,C);
            clock_t end=clock();
            total+=(double)(end-start)/CLOCKS_PER_SEC;
        }
        double avg=total/trials;
        printf("%d x %d -> %.9f sec\n",n,n,avg);
        fprintf(fp,"%d %.9f\n",n,avg);
        free(A); free(B); free(C);
    }
    fclose(fp);
    return 0;
}
