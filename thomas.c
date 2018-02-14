#include <stdio.h>
#include <math.h>
#include<stdbool.h>
#include<string.h>

void get_c_prime(float A[10][10],float d[10], int iteration, float c_prime[10]);

void get_d_prime(float A[10][10],float d[10], int iteration, float c_prime[10], float d_prime[10]);

void get_x(int lin_equat, float c_prime[10], float d_prime[10], float x[10]);

bool is_diagonal_dominant( float A[10][10], int lin_equat);

void display(int m, int n, float matrix[10][10], char message[30]);

int main(){

    // FOR TESTING
    // int lin_equat = 4;
    // float A[10][10] = { { 2.04, -1, 0, 0},
    //                     { -1, 2.04, -1, 0},
    //                     { 0, -1, 2.04, -1},
    //                     { 0, 0, -1, 2.04} };
    // float d[10] = { 40.8,
    //                 0.8,
    //                 0.8,
    //                 200.8 };
    // float x[10] = {0};
    // float c_prime[10] = {0};
    // float d_prime[10] = {0};
    // END TESTING

    float A[10][10] = {0},d[10] = {0}, x[10] = {0}, c_prime[10] = {0}, d_prime[10] = {0};
    int lin_equat = 0;




    int i,j,k,p;
    bool repeat = true;
    int yes_no;
    while(repeat){
        //INPUT
        printf("Enter number of linear equations to be solved:\n");
        scanf("%d", &lin_equat);
        printf("Enter the variable coefficients of matrix [A] from top left to bottom right:\n");
        for (i = 0; i < lin_equat; i++){
            for (j = 0; j < lin_equat; j++)
            {
                scanf("%f", &A[i][j]);
            }
        }
        printf("Enter the constants of the equations [B]:\n");
        for (j = 0; j < lin_equat; j++)
        {
            scanf("%f", &d[j]);
        }
        //END INPUT
        


        //Print A
        display(lin_equat,lin_equat,A,"Matrix A:");
        //Print B
        printf("\nMatrix B:\n");
        for (k = 0; k < lin_equat; k++)
        {
            printf("%f\n", d[k]);
        }
        //end Print B

        if(is_diagonal_dominant(A,lin_equat)){
            printf("\nValid\n");
            for( i = 0 ; i < lin_equat; i++) {
                get_c_prime(A,d,i,c_prime);
            }

            for( i = 0 ; i < lin_equat; i++) {
                get_d_prime(A,d,i,c_prime,d_prime);
            }

            get_x(lin_equat, c_prime, d_prime, x);

            //Print D prime and C prime
            // for( p = 0; p < lin_equat; p++){
            //     printf("%f\n",c_prime[p]);
            // }

            // for( p = 0; p < lin_equat; p++){
            //     printf("%f\n",d_prime[p]);
            // }

            for( p = 0; p < lin_equat; p++){
                printf("x%d: %f\n",p+1,x[p]);
            }
        }
        else
        {
            printf("NO SOLUTION\n");
        }

        printf("\nWould you like to solve another system of linear equations? ( Yes - 1 | No - 0 )\n");
        scanf("%d",&yes_no);
        switch(yes_no){
            case 1:
                repeat = true;
            break;
            case 0:
                repeat = false;
            break;
            default:
            break;
            
        }

    }




}

void get_c_prime(float A[10][10],float d[10], int iteration, float c_prime[10]){
    int a = iteration - 1;
    int b =  iteration;
    int c =  iteration + 1;
    
    if( iteration == 0 ){
        c_prime[ iteration ] = A[iteration][c] / A[iteration][b];
    }
    else
    {
        c_prime[ iteration ] = A[iteration][c] / ( A[iteration][b] - ( A[iteration][a] * c_prime[iteration-1] ) );
    }
}

void get_d_prime(float A[10][10],float d[10], int iteration, float c_prime[10], float d_prime[10]){
    int a = iteration - 1;
    int b =  iteration;
    int c =  iteration + 1;
    if( iteration == 0 ){
        d_prime[ iteration ] = d[iteration] / A[iteration][b];
    }
    else
    {
        d_prime[ iteration ] = ( d[iteration] - (A[iteration][a] * d_prime[iteration-1]) ) / ( A[iteration][b] - ( A[iteration][a] * c_prime[iteration-1] ) );
    }
}

void get_x(int lin_equat, float c_prime[10], float d_prime[10], float x[10]){
    int i;
    x[lin_equat-1] = d_prime[lin_equat-1];
    for( i = lin_equat-2 ; i > -1 ; i--) {
        x[i] = d_prime[i] - ( c_prime[i] * x[i+1] );
    }
}

bool is_diagonal_dominant( float A[10][10], int lin_equat){
    int iteration;
    int a;
    int b;
    int c;
    
    for( iteration = 0; iteration < lin_equat; iteration++){
        a = iteration - 1;
        b =  iteration;
        c =  iteration + 1;
        if( iteration == 0 ) {
            if(fabs(A[iteration][b]) <= fabs(A[iteration][c])){
                return false;
                
            }
        } 
        else if( iteration == lin_equat-1)
        {
            if(fabs(A[iteration][b]) <= fabs(A[iteration][a])){
                return false;
                
            }       
        }
        else
        {
            if(fabs(A[iteration][b]) <= fabs(A[iteration][a]) + fabs(A[iteration][c])){
                return false;
                
            }       
            
        }
    }
    
    return true;
}

void display(int m, int n, float matrix[10][10], char message[30])
{
    int i, j;
    printf("\n%s\n",message);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%f  ", matrix[i][j]);
        }
        printf("\n");
    }
    
}

