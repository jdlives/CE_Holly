    /*

     * C Program to Perform Matrix Multiplication using Recursion

     */

    #include <stdio.h>
    #include <math.h>

     

    void multiply(int m1, int n1, float a[10][10], int m2, int n2, float b[10][10], float c[10][10]);

    void display(int m1, int n1, float[10][10],char message[30]);

    void diagonal(int m1, int n1, float a[10][10], float c[10][10]);

    void subtraction(int m1, int n1, float a[10][10], int m2, int n2, float b[10][10], float c[10][10]);

    void addition(int m1, int n1, float a[10][10], int m2, int n2, float b[10][10], float c[10][10]);

    float determinant(float a[10][10], float k);

    void cofactor(float num[10][10], float f, float inverse[10][10]);

    void transpose(float num[10][10], float fac[10][10], float r, float inverse[10][10]);

    void inverse(int m1, int n1, float d[10][10], float inverse[10][10]);

    void remain(int m1, int n1, float a[10][10], float c[10][10]);

    void Jacobi(int m1, int n1, float A[10][10], int m2, int n2, float b[10][10], float x[10][10]);

    int main()

    {

        float dt, a[10][10], b[10][10], /*c[10][10] = {0},*/d[10][10] = {0}, e[10][10];
        int m1, n1, m2, n2, i, j, k;
        float c[10][10] = {{0},{0},{0}};

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

            Jacobi(m1, n1, a, m2, n2, b, c);
            // remain(m1,n1,a,d);
            // inverse(m1,n1,d,d);
           

        }
        display(m1, n2, c, "Matrix C");
        // display(m1, n1, d, "Matrix D");

    }
    /*Genral matrix function*/
    /*where m1 -> # of rows of first matrix , n1 -> # of columns of first matrix , a -> first matrix, 
    m2 -> # of rows of second matrix , n2 -> # of columns of second matrix ,b -> second matrix, c -> result matrix*/
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
    /*General Matrix function*/
    /*where m1 -> # of rows of first matrix , n1 -> # of columns of first matrix , a -> first matrix, 
    m2 -> # of rows of second matrix , n2 -> # of columns of second matrix ,b -> second matrix, c -> result matrix*/
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
    /*General Matrix function*/
    /*where m1 -> # of rows of first matrix , n1 -> # of columns of first matrix , a -> first matrix, 
    m2 -> # of rows of second matrix , n2 -> # of columns of second matrix ,b -> second matrix, c -> result matrix*/
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
    /*General Matrix function*/
    /*where m1 -> # of rows , n1 -> # of columns , a -> first matrix, c -> result matrix*/
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

    /*To display a matrix.*/
    /*where m1 -> # of rows , n1 -> # of columns , c -> matrix to be displayed, message-> description of matrix*/
    void display(int m1, int n2, float c[10][10], char message[30])

    {
        int i, j;
        printf("\n%s\n",message);
        for (i = 0; i < m1; i++)
        {
            for (j = 0; j < n2; j++)
            {
                printf("%f  ", c[i][j]);
            }
            printf("\n");
        }
    }

    /*This is for calculating Determinant of the Matrix */
     /*where k -> degree of the matrix, a -> matrix */
    float determinant(float a[10][10], float k)

    {
        float s = 1, det = 0, b[10][10];
        int i, j, m, n, c;
        if (k == 1)
        {
            return (a[0][0]);
        }
        else
        {
            det = 0;
            for (c = 0; c < k; c++)
            {
                m = 0;
                n = 0;
                for (i = 0;i < k; i++)
                {
                    for (j = 0 ;j < k; j++)
                    {
                        b[i][j] = 0;
                        if (i != 0 && j != c)
                        {
                            b[m][n] = a[i][j];
                            if (n < (k - 2))
                            {
                                n++;
                            }    
                            else
                            {
                                n = 0;
                                m++;
                            }
                        }
                    }
                }
                det = det + s * (a[0][c] * determinant(b, k - 1));
                s = -1 * s;
            }
        }
            return (det);
    }
    
    /*This is for calculating Determinant of the Matrix */
    /*num -> matrix to be processed, f -> the degree if the matrix, 
    inverse -> where the resultant inverse matrix will be stored*/
    void cofactor(float num[10][10], float f, float inverse[10][10])
    {
        float b[10][10], fac[10][10];
        int p, q, m, n, i, j;
        for (q = 0;q < f; q++)
        {
            for (p = 0;p < f; p++)
            {
                m = 0;
                n = 0;
                for (i = 0;i < f; i++)
                {
                    for (j = 0;j < f; j++)
                    {
                        if (i != q && j != p)
                        {
                            b[m][n] = num[i][j];
                            if (n < (f - 2))
                            {
                                n++;
                            }
                            else
                            {
                                n = 0;
                                m++;
                            }
                        }
                    }
                }
                fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
            }
        }
        transpose(num, fac, f,inverse);
    }

    /*Finding transpose of matrix*/ 
    /*num -> matrix to be processed, f -> the degree if the matrix, 
    inverse -> where the resultant inverse matrix will be stored*/
    void transpose(float num[10][10], float fac[10][10], float r, float inverse[10][10])
    {
        int i, j;
        float b[10][10], d;

        for (i = 0;i < r; i++)
        {
            for (j = 0;j < r; j++)
            {
                b[i][j] = fac[j][i];
            }
        }
        d = determinant(num, r);
        for (i = 0;i < r; i++)
        {
            for (j = 0;j < r; j++)
            {
                inverse[i][j] = b[i][j] / d;
            }
        }
    }

    /*d -> matrix to be processed, m1 and n1 -> rows and columns of the matrix, 
    inverse -> where the resultant inverse matrix will be stored*/
    void inverse(int m1, int n1, float d[10][10], float inverse[10][10])
    {

        if(m1 != n1)
        {
             printf("Getting inverse is not possible.\n");
        }
        else
        {
            float dt;
            /*Getting the inverse*/
            dt = determinant(d, m1);

            if (dt == 0)
            {
                printf("\nInverse of Entered Matrix is not possible\n");
            }
            else
            {
                cofactor(d, m1,inverse);
            }
            /*end*/
        }
        
    }

    /*This is for the Jacobi Method*/
    /*where m1 -> # of rows , n1 -> # of columns , a -> first matrix, c -> result matrix*/
    void remain(int m1, int n1, float a[10][10], float c[10][10])
    {
        if(m1 != n1)
        {
             printf("Getting remainder not possible.\n");
        }
        else
        {
            int i, j;
            for (i = 0; i < m1; i++)
            {
                for (j = 0; j < n1; j++)
                {
                    if (i != j)
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

    void Jacobi(int m1, int n1, float A[10][10], int m2, int n2, float b[10][10], float x[10][10])
    {
        float D[10][10]= {0};
        float R[10][10]= {0};
        float Rx[10][10]= {0};
        float bRx[10][10]= {0};
        float iteration[10][10]= {0};
        diagonal(m1,n1,A,D);
        
        inverse(m1,n1,D,D);

        display(m1,n1,D,"Inverse of Diagonal of A:");
        remain(m1,n1,A,R);
        display(m1,n1,R,"Remainder of A:");
        multiply(m1,n1,R,m2,n2,x,Rx);
        display(m2,n2,Rx,"Rx:");
        subtraction(m2,n2,b,m2,n2,Rx,bRx);
        display(m2,n2,bRx,"b minus Rx:");
        multiply(m1,n1,D,m2,n2,bRx,iteration);
        display(5,5,iteration,"Jacobi:");
    }




