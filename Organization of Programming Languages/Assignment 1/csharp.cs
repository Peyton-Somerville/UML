// Peyton Somerville
// Source: https://www.tutorialspoint.com/chash-program-to-multiply-two-matrices

// To compile: type 'mcs csharp.cs'
// To run: type 'mono csharp.exe'

using System;                                               // importing library, like #include <...> in C++
namespace MatrixMultiplicationDemo
{
    class Example
    {
        static void Main(string[] args)                     // main function
        {
            int m = 2, n = 3, p = 3, q = 3, i, j;           // declaring dimensions and iterators
            int[,] a = { { 1, 4, 2 },                                  
                        { 2, 5, 1 } };                      // 2D array to represent matrix 1
            int[,] b = { { 3, 4, 2 }, 
                        { 3, 5, 7 }, 
                        { 1, 2, 1 } };                      // 2D array to represent matrix 2
            Console.WriteLine("Matrix a:");                 // C# version of print/ printf/ cout
            for (i = 0; i < m; i++)
            {                                               // double for-loop to access each element to display matrix 1
                for (j = 0; j < n; j++)
                {
                    Console.Write(a[i, j] + " ");           // writing to output stream
                }
                Console.WriteLine();                        // displaying output
            }
            Console.WriteLine("Matrix b:");
            for (i = 0; i < p; i++)
            {                                               // double for-loop to access each element to display matrix 2
                for (j = 0; j < q; j++)
                {
                    Console.Write(b[i, j] + " ");           // writing to output stream
                }
                Console.WriteLine();                        // displaying output
            }
            if (n != p) {                                   // if the dimensions are invalid for matrix multiplication
                Console.WriteLine("Matrix multiplication not possible");
            } else {                                        // if dimenstion are valid
                int[,] c = new int[m, q];                   // create new empty 2D array to represent result matrix
                for (i = 0; i < m; i++)
                {                                   
                    for (j = 0; j < q; j++)
                    {
                        c[i, j] = 0;                        // init each element of result matrix to 0                     
                        for (int k = 0; k < n; k++)         // triple for-loop to access each element of all 3 matrices
                        {
                            c[i, j] += a[i, k] * b[k, j];   // matrix multiplication formula
                        }
                    }
                }
                Console.WriteLine("The product of the two matrices is :");
                for (i = 0; i < m; i++)
                {                                           // double for-loop to access each element to display result matrix
                    for (j = 0; j < n; j++)
                    {
                        Console.Write(c[i, j] + "\t");      // writing to output stream
                    }
                    Console.WriteLine();                    // displaying output
                }
            }
        }
    }
}