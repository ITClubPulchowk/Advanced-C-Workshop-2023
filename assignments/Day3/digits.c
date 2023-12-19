#include <assert.h>
#include <curses.h>
#include <emmintrin.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// store the results in `input`
void relu(int n, float input[n]) {
  // TODO implement this
}

// store the results in `a`
void vector_sum(int n, float a[n], float b[n]) {
  // TODO implement this
}

// return the index of the maximum element in `a`
int argmax(int n, float a[n]) {
  return -1; // TODO implement this
}

void matmul(int m, int n, int o, float a[m][n], float b[n][o],
            float result[m][o]) {
  for (int i = 0; i < m; i++)
    for (int k = 0; k < n; k++)
      for (int j = 0; j < o; j++)
        result[i][j] += a[i][k] * b[k][j];
}

void read_mat(char *file_path, float *mat, int size) {
  FILE *file = fopen(file_path, "rb");
  // Read the matrix from the file
  fread(mat, size, sizeof(float), file);
}

float *alloc_matrix(int m, int n) {
  float *a = (float *)aligned_alloc(sizeof(float), sizeof(float) * m * n);
  memset((void *)a, 0, sizeof(float) * m * n);
  return a;
}

void clear_array(float *arr) { memset(arr, 0, 32 * 32 * 4); }

int predict(float *image, float **p, float **i) {
  int dims[] = {256, 256, 128, 10};
  matmul(dims[0], 1024, 1, p[0], image, i[0]);
  vector_sum(dims[0], i[0], p[1]);
  relu(dims[0], i[0]);

  matmul(dims[1], dims[0], 1, p[2], i[0], i[1]);
  vector_sum(dims[1], i[1], p[3]);
  relu(dims[1], i[1]);

  matmul(dims[2], dims[1], 1, p[4], i[1], i[2]);
  vector_sum(dims[2], i[2], p[5]);
  relu(dims[2], i[2]);

  matmul(dims[3], dims[2], 1, p[6], i[2], i[3]);
  vector_sum(dims[3], i[3], p[7]);

  return argmax(dims[3], i[3]);
}

int main() {

  float *l1_w = alloc_matrix(256, 32 * 32);
  float *l1_b = alloc_matrix(256, 1);

  float *l2_w = alloc_matrix(256, 256);
  float *l2_b = alloc_matrix(256, 1);

  float *l3_w = alloc_matrix(256, 128);
  float *l3_b = alloc_matrix(128, 1);

  float *l4_w = alloc_matrix(10, 128);
  float *l4_b = alloc_matrix(10, 1);

  read_mat("params/l1_w.bin", l1_w, 256 * 32 * 32);
  read_mat("params/l1_b.bin", l1_b, 256 * 1);
  read_mat("params/l2_w.bin", l2_w, 256 * 256);
  read_mat("params/l2_b.bin", l2_b, 256 * 1);
  read_mat("params/l3_w.bin", l3_w, 128 * 256);
  read_mat("params/l3_b.bin", l3_b, 128 * 1);
  read_mat("params/l4_w.bin", l4_w, 10 * 128);
  read_mat("params/l4_b.bin", l4_b, 10 * 1);

  float *parameters[] = {l1_w, l1_b, l2_w, l2_b, l3_w, l3_b, l4_w, l4_b};

  float *i1 = alloc_matrix(256, 1);
  float *i2 = alloc_matrix(256, 1);
  float *i3 = alloc_matrix(128, 1);
  float *i4 = alloc_matrix(10, 1);
  float *intermediates[] = {i1, i2, i3, i4};

  initscr();
  cbreak();
  noecho();

  // Enable mouse events
  keypad(stdscr, TRUE);
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

  int n_preds = 0;

  float arr[32][32] = {0.0};
  predict((float *)arr, parameters, intermediates);
  int x;
  int y;
  float fill = 0.0;
  nodelay(stdscr, TRUE);

  int result = -1;
  int is_clear = 1;

  printf("\033[?1003h\n");
  int ch;
  while (1) {
    MEVENT event;
    while ((ch = getch()) == ERR) {
    }
    if (ch == 'q')
      break;
    for (int i = 0; i < 32; i++) {
      for (int j = 0; j < 32; j++) {
        mvaddch(i, j, arr[i][j] > 0.2 ? ' ' : '#');
      }
    }
    if (ch == KEY_MOUSE) {
      if (getmouse(&event) == OK) {
        x = event.x;
        y = event.y;
        if (fill > 0.00) {
          arr[y][x] = fill;
          is_clear = 0;
        }
      }
    } else if (ch == 'c') {
      clear();
      clear_array((float *)arr);
      is_clear = 1;
      result = -1;
    } else if (ch == 'f') {
      fill = 1.0;
    } else if (ch == 'g') {
      fill = 0.0;
      result = predict((float *)arr, parameters, intermediates);
    }
    flushinp();
    n_preds++;
    char buffer[100];
    move(33, 0);
    if (is_clear) {
      result = 0;
    }
    snprintf(buffer, 100, "Predicted: %d", result);
    addstr(buffer);
    move(0, 0);
    napms(1000 / 60);
  }
  endwin();
  printf("\033[?1003l\n"); // Disable mouse movement events, as l = low

  return 0;
}
