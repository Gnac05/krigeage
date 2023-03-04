#include "main.h"

// Même si dans le suite on a parlé de plusieurs dimensions on va prendre pour ce projet la dimension 1 pour des problèmes de simplification

/*
Function : metho_Krigeage
Input :
 g --> is function which take xi and xj
 nbDim --> is the dimension of the function f e.i. dim 1 = (x, f(x)), dim 2 = ((x1, x2), f(x1,x2)) dim 3= ((x1, x2, x3), f(x1,x2,x3))
 deg --> is degre of the polynome without considered g
 X --> is the matrix which contain xi i.e. x1, x2, x3, ... in dim 1
 F --> is the matrix which contain the solution of the xi e.i. f(x1), f(x2), f(x3), ... in dim 1
*/
void metho_krigeage(callback_g g, int nbDim, int deg, double *X, double *F, int nbPoint)
{
  // In first time nbDim = 1
  nbDim = 1; // this line force to be in dimension 1
  int i, j;
  int n = nbPoint;

  // Generation of matrix K : nxn
  double K[n][n];
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      K[i][j] = g(X[i], X[j]);
    }
  }

  // Generation of A : nx(deg+1)
  double A[n][deg + 1];
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < deg + 1; j++)
    {
      A[i][j] = power(X[i], j);
    }
  }

  // Generation of transpose of A, TA : (deg+1)xn
  double TA[deg + 1][n];
  // A: mxn
  // transpose(A, TA, n, deg+1);
  for (i = 0; i < deg + 1; i++)
  {
    for (j = 0; j < n; j++)
    {
      TA[i][j] = A[j][i];
    }
  }

  // Generation of matrix Zero : (deg+1)x(deg+1)
  double Zero[deg + 1][deg + 1];
  for (i = 0; i < deg + 1; i++)
  {
    for (j = 0; j < deg + 1; j++)
    {
      Zero[i][j] = 0;
    }
  }

  // Generation of TheBig matrix which containt K, A, TA, Zero
  double TheBig[n + deg + 1][n + deg + 1];
  for (i = 0; i < n + deg + 1; i++)
  {
    for (j = 0; j < n + deg + 1; j++)
    {
      if (i < n)
      {
        if (j < n)
        {
          TheBig[i][j] = K[i][j];
        }
        else
        {
          TheBig[i][j] = A[i][j - n];
        }
      }
      else
      {
        if (j < n)
        {
          TheBig[i][j] = TA[i - n][j];
        }
        else
        {
          TheBig[i][j] = Zero[i - n][j - n];
        }
      }
    }
  }

  // Generation of matrix Fx which content :(n+deg+1)x1
  double Fx[n + deg + 1];
  for (i = 0; i < n + deg + 1; i++)
  {
    if (i < n)
    {
      Fx[i] = F[i];
    }
    else
    {
      Fx[i] = 0;
    }
  }

  double info, *a, *y;
  int N, nrhs, ldb, *ipiv, lda;
  N = n + deg + 1; // The number of Columns
  nrhs = 1;
  ldb = N;
  lda = N; // Leading dimension of matrix
  ipiv = (lapack_int *)malloc(n * sizeof(lapack_int));
  a = (double *)malloc(sizeof(double) * N * N);
  y = (double *)malloc(N * nrhs * sizeof(double));

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      a[i * N + j] = TheBig[i][j];
    }
    y[i] = Fx[i];
  }

  // It is this function which resolve the systeme
  info = LAPACKE_dgesv(LAPACK_COL_MAJOR, N, nrhs, a, lda, ipiv, y, ldb);

  if (info == 0)
  {
    printf("We have find the solution.\n");

    for (j = 0; j < N; j++)
    {
      if (j < n)
      {
        printf("alpha(%d) = %.3f \n", j + 1, y[j]);
      }
      else
      {
        printf("a(%d) = %.3f \n", j + 1, y[j]);
      }
    }
  }
}
