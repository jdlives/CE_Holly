    /*

     * C Program to Perform Matrix Multiplication using Recursion

     */

    #include <stdio.h>
    #include <math.h>
    #include<stdbool.h>
    #include<string.h>


     

    void multiply (int m1, int n1, float x[10][10], int m2, int n2, float y[10][10], float xy[10][10],bool recur);

    void display(int m1, int n1, float[10][10],char message[30]);

    void diagonal(int m1, int n1, float a[10][10], float c[10][10]);

    void subtraction(int m1, int n1, float a[10][10], int m2, int n2, float b[10][10], float c[10][10]);

    void addition(int m1, int n1, float a[10][10], int m2, int n2, float b[10][10], float c[10][10]);

    float determinant(float a[10][10], float k);

    void cofactor(float num[10][10], float f, float inverse[10][10]);

    void transpose(float num[10][10], float fac[10][10], float r, float inverse[10][10]);

    void inverse(int m1, int n1, float d[10][10], float inverse[10][10]);

    void remain(int m1, int n1, float a[10][10], float c[10][10]);

    void Jacobi(int m1, int n1, float A[10][10], int m2, int n2, float b[10][10], float x[10][10],float tolerance);

    void clean(int m1,int n1, float c[10][10]);

    void L(int m1, int n1, float a[10][10], float c[10][10]);

    void U(int m1, int n1, float a[10][10], float c[10][10]);

    void Guass_Seidal(int m1, int n1, float A[10][10], int m2, int n2, float b[10][10], float x[10][10],float tolerance);

    void SOR(int m1, int n1, float A[10][10], int m2, int n2, float b[10][10], float x[10][10],float tolerance);

    void addn(int m1, int n1, float a[10][10], float w,float c[10][10]);

    FILE *fp;
    FILE *ip;
    


    int main()

    {
        fp = fopen("output.txt", "w");
        ip = fopen("input.txt","r");
        float dt, a[10][10]={0}, b[10][10]={0}, /*c[10][10] = {0},*/d[10][10] = {0}, e[10][10] = {0};
        int m1, n1, m2, n2, i, j, k, choice;
        float c[10][10] = {0};

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
            printf("Enter method of choise: (1)Jacobi , (2) Guass Seidal, (3)SOR\n");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                    Jacobi(m1,n1,a,m2,n2,b,c,0.00001);
                break;
                case 2:
                    Guass_Seidal(m1,n1,a,m2,n2,b,d,0.00001);
                break;
                case 3:
                    SOR(m1, n1, a, m2, n2, b, e,0.00001);
                break;
             
            }
            
            
            
            // remain(m1,n1,a,d);
            // inverse(m1,n1,d,d);
           

        }
        display(m1, n2, c, "Matrix C");
        // display(m1, n1, d, "Matrix D");
        printf("Done\n");
        fclose(fp);

    }
    /*Genral matrix function*/
    /*where m1 -> # of rows of first matrix , n1 -> # of columns of first matrix , a -> first matrix, 
    m2 -> # of rows of second matrix , n2 -> # of columns of second matrix ,b -> second matrix, c -> result matrix*/
    void multiply (int m1, int n1, float x[10][10], int m2, int n2, float y[10][10], float xy[10][10],bool recur)
    {
        static int i = 0, j = 0, k = 0;
        if(!recur){
            i -= i;
            j -= j;
            k -= k;
            memset(xy,0,sizeof(float)*10*10);
        }
        float r = 0;
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
                    xy[i][j] += x[i][k] * y[k][j];
                    
                    k++;
                    multiply(m1, n1, x, m2, n2, y, xy,true);
                }
                k = 0;
                j++;
                multiply(m1, n1, x, m2, n2, y, xy,true);
            }
            j = 0;
            i++;
            multiply(m1, n1, x, m2, n2, y, xy,true);
        }
        // if(!recur){
        //     display(m1,n1,x,"First:");
        //     display(m2,n2,y,"Second:");
        //     display(m1,n2,xy,"Result Mult:");
        // }
    }
    /*General Matrix function*/
    /*where m1 -> # of rows of first matrix , n1 -> # of columns of first matrix , a -> first matrix, 
    m2 -> # of rows of second matrix , n2 -> # of columns of second matrix ,b -> second matrix, c -> result matrix*/
    void subtraction(int m1, int n1, float a[10][10], int m2, int n2, float b[10][10], float c[10][10])
     {
        int i, j;
        for (i = 0; i < m1; i++)
        {
            for (j = 0; j < n1; j++)
            {
                c[i][j]=a[i][j]-b[i][j];        
                // printf("%f  ", c[i][j]);
            }
            // printf("\n");
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
                // printf("%f  ", c[i][j]);
            }
            // printf("\n");
        }
     }

     void addn(int m1, int n1, float a[10][10], float w,float c[10][10])
     {
        int i, j;
        for (i = 0; i < m1; i++)
        {
            for (j = 0; j < n1; j++)
            {
                c[i][j]=a[i][j]*w;
            }
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
    void copy(int m1, int n1, float a[10][10], float b[10][10] )

    {
        int i, j;
        for (i = 0; i < m1; i++)
        {
            for (j = 0; j < n1; j++)
            {
                b[i][j] = a[i][j];
            }
        }
        
    }
    /*To display a matrix.*/
    /*where m1 -> # of rows , n1 -> # of columns , c -> matrix to be displayed, message-> description of matrix*/
    void display(int m1, int n2, float c[10][10], char message[30])

    {

        clean(m1,n2,c);
        int i, j;
        fprintf(fp, "\n%s\n",message);
        // printf("\n%s\n",message);
        for (i = 0; i < m1; i++)
        {
            for (j = 0; j < n2; j++)
            {
                fprintf(fp, "%f  ", c[i][j]);
                // printf("%f  ", c[i][j]);
            }
            fprintf(fp,"\n");
            // printf("\n");
        }
        
    }
    void iteration(int m1, int n2, float c[10][10], int itr)
    {

        clean(m1,n2,c);
        int i, j, k;
        
        // printf("\n%s\n",message);
        if(itr==0)
        {
            printf("\ni  ");
            for (k = 1; k <= m1; k++){
                printf("    x%d    ",k);
            }
            
        }
        else
        {
            printf("\n%d  ",itr);
            for (i = 0; i < m1; i++)
            {
                for (j = 0; j < n2; j++)
                {
                    printf("%f  ", c[i][j]);
                    // printf("%f  ", c[i][j]);
                }
                // printf("\n");
            }
        }    
            
        fprintf(fp,"\n");
        
    }
    void clean(int m1,int n1, float c[10][10])
    {
        int i, j;
        for (i = 0; i < m1; i++)
        {
            for (j = 0; j < n1; j++)
            {
                c[i][j] +=0.0;
            }
        }
    }

    void reset(int m1, int n1, float c[10][10])

    {
        clean(m1,n1,c);
        int i, j;
        for (i = 0; i < m1; i++)
        {
            for (j = 0; j < n1; j++)
            {
                c[i][j] = 0;
            }
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
    bool hasConverged (int k, float a[10][10], float b[10][10], float tolerance){
        int i;
        // printf("\n%s\n",message);
        for (i = 0; i < k; i++)
        {
            if(fabs(a[i][0]-b[i][0])<tolerance){
                continue;
            }
            else
            {
                return false;
            }
        }
        return true;
    } 
    void Jacobi(int m1, int n1, float A[10][10], int m2, int n2, float b[10][10], float x[10][10],float tolerance)
    {
        int i = 2;//adjusted for the primer
        float D[10][10]= {0};
        float R[10][10]= {0};
        float Rx[10][10]= {0};
        float bRx[10][10]= {0};
        float invD[10][10]={0};
        float temp[10][10]={0};
        /*Constants factors*/
        diagonal(m1,n1,A,D);
        inverse(m1,n1,D,invD);
        remain(m1,n1,A,R);
        iteration(m1,n2,x,0);
        /*Dynamic*/
        display(m1,n1,invD,"invD:\n");
        display(m1,n2,temp,"Temp:\n");

        /*Primer(0,0,0)*/
        copy(m1,n2,x,temp);
        multiply(m1,n1,R,m2,n2,x,Rx,false);
        subtraction(m2,n2,b,m2,n2,Rx,bRx);
        memset(x,0,sizeof(float)*10*10);
        multiply(m1,n1,invD,m2,n2,bRx,x,false);
        iteration(m1,n2,x,1);
        /*end*/
        while(i<1000 && !hasConverged(m1,x,temp,tolerance))
        {   
            display(m1,n2,Rx,"Rx:\n");
            display(m1,n2,temp,"Temp:\n");
            
            copy(m1,n2,x,temp);
            i +=1;
            multiply(m1,n1,R,m2,n2,x,Rx,false);
            subtraction(m2,n2,b,m2,n2,Rx,bRx);
            memset(x,0,sizeof(float)*10*10);
            multiply(m1,n1,invD,m2,n2,bRx,x,false);
            iteration(m1,n2,x,i);
            
        }
       
    
    }

    void L(int m1, int n1, float a[10][10], float c[10][10])

    {
        if(m1 != n1)
        {
             printf("Getting L not possible.\n");
        }
        else
        {
            int i, j;
            for (i = 0; i < m1; i++)
            {
                for (j = 0; j < n1; j++)
                {
                    if (j > i)
                    {
                        c[i][j] = 0;
                    }
                    else
                    {
                        c[i][j] = a[i][j];
                    }
                }
            }

        }
        
    }

    void Upper(int m1, int n1, float a[10][10], float c[10][10])

    {
        if(m1 != n1)
        {
             printf("Getting L not possible.\n");
        }
        else
        {
            int i, j;
            for (i = 0; i < m1; i++)
            {
                for (j = 0; j < n1; j++)
                {
                    if (j <= i)
                    {
                        c[i][j] = 0;
                    }
                    else
                    {
                        c[i][j] = a[i][j];
                    }
                }
            }

        }
        
    }

    void Low(int m1, int n1, float a[10][10], float c[10][10])

    {
        if(m1 != n1)
        {
             printf("Getting L not possible.\n");
        }
        else
        {
            int i, j;
            for (i = 0; i < m1; i++)
            {
                for (j = 0; j < n1; j++)
                {
                    if (j >= i)
                    {
                        c[i][j] = 0;
                    }
                    else
                    {
                        c[i][j] = a[i][j];
                    }
                }
            }

        }
        
    }

    

    void Guass_Seidal(int m1, int n1, float A[10][10], int m2, int n2, float b[10][10], float x[10][10],float tolerance)
    {
        int i = 2;//adjusted for the primer
        float D[10][10]= {0};
        float R[10][10]= {0};
        float Rx[10][10]= {0};
        float bRx[10][10]= {0};
        float invD[10][10]={0};
        float temp[10][10]={0};
        /*Constants factors*/
        L(m1,n1,A,D);
        inverse(m1,n1,D,invD);
        Upper(m1,n1,A,R);
        iteration(m1,n2,x,0);
        /*Dynamic*/
        display(m1,n2,x,"x:\n");
        display(m1,n2,temp,"Temp:\n");

        /*Primer(0,0,0)*/
        copy(m1,n2,x,temp);
        multiply(m1,n1,R,m2,n2,x,Rx,false);
        subtraction(m2,n2,b,m2,n2,Rx,bRx);
        memset(x,0,sizeof(float)*10*10);
        multiply(m1,n1,invD,m2,n2,bRx,x,false);
        iteration(m1,n2,x,1);
        /*end*/
        while(i<1000 && !hasConverged(m1,x,temp,tolerance))
        {   
            display(m1,n2,x,"x:\n");
            display(m1,n2,temp,"Temp:\n");
            
            copy(m1,n2,x,temp);
            i +=1;
            multiply(m1,n1,R,m2,n2,x,Rx,false);
            subtraction(m2,n2,b,m2,n2,Rx,bRx);
            memset(x,0,sizeof(float)*10*10);
            multiply(m1,n1,invD,m2,n2,bRx,x,false);
            iteration(m1,n2,x,i);
            
        }

    }

    void SOR(int m1, int n1, float A[10][10], int m2, int n2, float b[10][10], float x[10][10],float tolerance)
    {
        
        int i = 2;//adjusted for the primer
        float D[10][10]= {0};
        float change[10][10]= {0};
        float w1D[10][10] = {0};
        float L[10][10]= {0};
        float U[10][10]= {0};
        float wL[10][10] = {0};
        float wb[10][10] = {0};
        float wU[10][10] = {0};
        float DwL[10][10] = {0};
        float R[10][10]= {0};
        float Rx[10][10]= {0};
        float bRx[10][10]= {0};
        float invD[10][10]={0};
        float temp[10][10]={0};
        /*Constants factors*/
        diagonal(m1,n1,A,D);
        Low(m1,n1,A,L);
        Upper(m1,n1,A,U);
        addn(m1,n1,L,1.5,wL);
        addn(m1,n2,b,1.5,wb);
        addn(m1,n1,U,1.5,wU);
        addn(m1,n1,D,1.5-1,w1D);
        
        addition(m1,n1,D,m1,n1,wL,DwL);
        addition(m1,n1,wU,m1,n1,w1D,change);
        
        inverse(m1,n1,DwL,invD);
        // remain(m1,n1,A,R);
        iteration(m1,n2,x,0);
        /*Dynamic*/
        display(m1,n2,x,"x:\n");
        display(m1,n2,temp,"Temp:\n");

        /*Primer(0,0,0)*/
        copy(m1,n2,x,temp);
        multiply(m1,n1,change,m2,n2,x,Rx,false);
        subtraction(m2,n2,wb,m2,n2,Rx,bRx);
        memset(x,0,sizeof(float)*10*10);
        multiply(m1,n1,invD,m2,n2,bRx,x,false);
        iteration(m1,n2,x,1);
        /*end*/
        while(i<1000 && !hasConverged(m1,x,temp,tolerance))
        {   
            copy(m1,n2,x,temp);
            memset(Rx,0,sizeof(float)*10*10);
            multiply(m1,n1,change,m2,n2,x,Rx,false);
            subtraction(m2,n2,wb,m2,n2,Rx,bRx);
            memset(x,0,sizeof(float)*10*10);
            multiply(m1,n1,invD,m2,n2,bRx,x,false);
            iteration(m1,n2,x,i);
            i +=1;
            
        }
    }

    






