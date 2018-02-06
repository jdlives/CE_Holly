    /*

     * C Program to Perform Matrix Multiplication using Recursion

     */

    #include <stdio.h>

     

    void multiply(int, int, float [][10], int, int, float [][10], float [][10]);

    void display(int, int, float[][10]);

    void diagonal(int m1, int n1, float a[10][10], float c[10][10]);

    void subtraction(int m1, int n1, float a[10][10], int m2, int n2, float b[10][10], float c[10][10]);

    void addition(int m1, int n1, float a[10][10], int m2, int n2, float b[10][10], float c[10][10]);



     

    int main()

    {

        float a[10][10], b[10][10], c[10][10] = {0}, d[10][10] = {0};
        int m1, n1, m2, n2, i, j, k;

        printf("Enter rows and columns for Matrix A respectively: ");

        scanf("%d%d", &m1, &n1);

        printf("Enter rows and columns for Matrix B respectively: ");

        scanf("%d%d", &m2, &n2);

        if (n1 != m2)
        {
            printf("Matrix multiplication not possible.\n");
        }
        else
        {
            printf("Enter elements in Matrix A:\n");
            for (i = 0; i < m1; i++)
            for (j = 0; j < n1; j++)
            {
                scanf("%f", &a[i][j]);
            }
            printf("\nEnter elements in Matrix B:\n");
            for (i = 0; i < m2; i++)
            for (j = 0; j < n2; j++)
            {
                scanf("%f", &b[i][j]);
            }

            subtraction(m1, n1, a, m2, n2, b, c);
            diagonal(m1,n1,a,d);
        }
        printf("On matrix multiplication of A and B the result is:\n");
        display(m1, n2, c);
        display(m1, n1, d);

    }

    void multiply (int m1, int n1, float a[10][10], int m2, int n2, float b[10][10], float c[10][10])
    {
        static int i = 0, j = 0, k = 0;
        if (i >= m1)
        {
            return;
        }
        else if (i < m1)
        {
            if (j < n2)
            {
                if (k < n1)
                {
                    c[i][j] += a[i][k] * b[k][j];
                    k++;
                    multiply(m1, n1, a, m2, n2, b, c);
                }
                k = 0;
                j++;
                multiply(m1, n1, a, m2, n2, b, c);
            }
            j = 0;
            i++;
            multiply(m1, n1, a, m2, n2, b, c);
        }
    }

     void subtraction(int m1, int n1, float a[10][10], int m2, int n2, float b[10][10], float c[10][10])
     {
        int i, j;
        for (i = 0; i < m1; i++)
        {
            for (j = 0; j < n2; j++)
            {
                c[i][j]=a[i][j]-b[i][j];        
                printf("%f  ", c[i][j]);
            }
            printf("\n");
        }
     }

     void addition(int m1, int n1, float a[10][10], int m2, int n2, float b[10][10], float c[10][10])
     {
        int i, j;
        for (i = 0; i < m1; i++)
        {
            for (j = 0; j < n2; j++)
            {
                c[i][j]=a[i][j]+b[i][j];
                printf("%f  ", c[i][j]);
            }
            printf("\n");
        }
     }

     void diagonal(int m1, int n1, float a[10][10], float c[10][10])
     {
         if(m1 != n1)
         {
             printf("Getting diagonal not possible.\n");
         }
         else
         {
            int i, j;
            for (i = 0; i < m1; i++)
            {
                for (j = 0; j < n1; j++)
                {
                    if (i == j)
                    {
                        c[i][j] = a[i][j];
                    }
                    else
                    {
                        c[i][j] = 0;
                    }
                }
            }

         }
        
     }


    void display(int m1, int n2, float c[10][10])

    {
        int i, j;
        for (i = 0; i < m1; i++)
        {
            for (j = 0; j < n2; j++)
            {
                printf("%f  ", c[i][j]);
            }
            printf("\n");
        }
    }




