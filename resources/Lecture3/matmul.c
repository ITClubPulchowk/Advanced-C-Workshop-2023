#include <assert.h>
#include <emmintrin.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define timing(a)                                                              \
  do {                                                                         \
    clock_t start = clock();                                                   \
    a;                                                                         \
    clock_t stop = clock();                                                    \
    printf("Took %.2f milliseconds\n",                                         \
           (double)(stop - start) * 1000.0f / CLOCKS_PER_SEC);                 \
  } while (0)

// set all matrix elements to zero
void clear_matrix(int m, int n, float mat[m][n]) {
  memset((void *)mat, 0, sizeof(float) * m * n);
}

// allocate an unaligned float matrix
float *alloc_matrix_naive(int m, int n) {
  float(*a)[n] = (float(*)[n])malloc(sizeof(float) * m * n);
  clear_matrix(m, n, a);
  return (float *)a;
}

// allocate an aligned float matrix
float *alloc_matrix(int m, int n) {
  float *a = (float *)aligned_alloc(64, sizeof(float) * m * n);
  memset((void *)a, 0, sizeof(float) * m * n);
  return a;
}

// generate a random float from U[min, max]
float randfloat(float min, float max) {
  float range = (max - min);
  float div = RAND_MAX / range;
  return min + (rand() / div);
}

// populate a matrix with random values
void make_interesing(int n, float array[n]) {
  for (int i = 0; i < n; i++)
    array[i] = randfloat(-5.0, 5.0);
}

// ... transpose. be sure to free afterwards.
float *transpose_matrix(int m, int n, float a[m][n]) {
  float(*temp)[m] = (float(*)[m])alloc_matrix(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      temp[j][i] = a[i][j];
  return (float *)temp;
}

// naive matrix multiplication
void matmul(int m, int n, int o, float a[m][n], float b[n][o],
            float result[m][o]) {
  for (int i = 0; i < m; i++)
    for (int j = 0; j < o; j++)
      for (int k = 0; k < n; k++)
        result[i][j] += a[i][k] * b[k][j];
}

// multiplication but with the right matrix transposed
void matmul_transposed(int m, int n, int o, float a[m][n], float b[o][n],
                       float result[m][o]) {
  for (int i = 0; i < m; i++)
    for (int j = 0; j < o; j++)
      for (int k = 0; k < n; k++)
        result[i][j] += a[i][k] * b[j][k]; // notice the indices on b
}

// interchange the j and k loops
void matmul_reorder(int m, int n, int o, float a[m][n], float b[n][o],
                    float result[m][o]) {
  for (int i = 0; i < m; i++)
    for (int k = 0; k < n; k++)
      for (int j = 0; j < o; j++)
        result[i][j] += a[i][k] * b[k][j];
}

// multiply in blocks in all three indices
#define BLOCK_SIZE 32
void matmul_block(int m, int n, int o, float a[m][n], float b[n][o],
                  float result[__restrict_arr m][o]) {
  for (int i = 0; i < m; i += BLOCK_SIZE)
    for (int j = 0; j < o; j += BLOCK_SIZE)
      for (int k = 0; k < n; k += BLOCK_SIZE)
        for (int ii = i; ii < i + BLOCK_SIZE && ii < m; ++ii)
          for (int kk = k; kk < k + BLOCK_SIZE && kk < n; ++kk)
            for (int jj = j; jj < j + BLOCK_SIZE && jj < o; ++jj)
              result[ii][jj] += a[ii][kk] * b[kk][jj];
}

// use sse intrinsices to multiply 4 float pairs in parallel
// and add them up. will abort (or silently lie) for matrices
// if o is not a multiple of 4
void matmul_simd(int m, int n, int o, float a[m][n], float b[n][o],
                 float result[__restrict_arr m][o]) {

  for (int i = 0; i < m; i += BLOCK_SIZE)
    for (int j = 0; j < o; j += BLOCK_SIZE)
      for (int k = 0; k < n; k += BLOCK_SIZE)
        for (int ii = i; ii < i + BLOCK_SIZE && ii < m; ++ii) {
          for (int kk = k; kk < k + BLOCK_SIZE && kk < n; ++kk) {
            __m128 m1d = _mm_set1_ps(a[ii][kk]);
            for (int jj = j; jj < j + BLOCK_SIZE && jj < o; jj += 4) {
              __m128 m2 = _mm_load_ps(&b[kk][jj]);
              __m128 r2 = _mm_load_ps(&result[ii][jj]);
              _mm_store_ps(&result[ii][jj],
                           _mm_add_ps(_mm_mul_ps(m2, m1d), r2));
            }
          }
        }
}

// make sure a and b are "equal"
void test_equal(float *a, float *b, int n) {
  float error = 0.0;
  for (int i = 0; i < n; i++) {
    error += fabs(a[i] - b[i]);
  }
  // abort if arrays arent equal
  assert((error / (float)n) < 0.0001);
}

int main() {

  srand(time(NULL));

  // modify these to see how the matrix sizes influence time
  // be careful about O, see the simd multiplication function
  int M = 1024;
  int N = 1024;
  int O = 1024;

  // allocate input matrices
  float(*a)[N] = (float(*)[N])alloc_matrix(M, N);
  float(*b)[O] = (float(*)[O])alloc_matrix(N, O);

  // fill random values
  make_interesing(M * N, (float *)a);
  make_interesing(N * O, (float *)b);

  // store matmul results
  float(*true_result)[O] = (float(*)[O])alloc_matrix(M, O);
  float(*c)[O] = (float(*)[O])alloc_matrix(M, O);

  // slow but correct: we use this to make sure other
  // methods produce the correct output
  printf("Using Naive method: ");
  timing(matmul(M, N, O, a, b, true_result));

  // transpose matrix b
  printf("Using transpose: ");
  float(*transposed)[O] = (float(*)[O])transpose_matrix(N, O, b);
  timing(matmul_transposed(M, N, O, a, transposed, c));
  free(transposed);
  test_equal((float *)true_result, (float *)c, M * O);

  // better loop ordering
  printf("Using reorder: ");
  clear_matrix(M, O, c);
  timing(matmul_reorder(M, N, O, a, b, c));
  test_equal((float *)true_result, (float *)c, M * O);

  // block multiplication -- slower, but need this for simd
  printf("Using block multiply: ");
  clear_matrix(M, O, c);
  timing(matmul_block(M, N, O, a, b, c));
  test_equal((float *)true_result, (float *)c, M * O);

  // use sse (128bit) instructions
  printf("Using simd: ");
  clear_matrix(M, O, c);
  timing(matmul_simd(M, N, O, a, b, c));
  test_equal((float *)true_result, (float *)c, M * O);
  clear_matrix(M, O, c);

  return 0;
}
