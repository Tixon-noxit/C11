#include <math.h>

#include "s21_matrix.h"

// Эта функция заполняет одну строку минора из исходной матрицы, пропуская
// определенный столбец.
// Она принимает указатель на исходную строку src_row, указатель на строку
// минора dest_row,
// индекс column пропускаемого столбца и размер a_size исходной матрицы.
// Функция проходит по всем элементам исходной строки, копирует элементы,
// пропуская элемент с индексом column,
// в строку минора.
static void s21_populate_minor_row(double *src_row, double *dest_row,
                                   int column, int a_size) {
  int m = 0;

  for (int j = 0; j < a_size; j++) {
    if (j != column) {
      dest_row[m] = src_row[j];
      m++;
    }
  }
}

// Эта функция заполняет весь минор из исходной матрицы, пропуская определенную
// строку и столбец. Она принимает двумерные массивы src и dest, представляющие
// исходную и целевую матрицы, соответственно, а также индексы row и column
// пропускаемой строки и столбца и размер a_size исходной матрицы. Функция
// проходит по всем строкам исходной матрицы, пропуская строку с индексом row,
// и вызывает s21_populate_minor_row для заполнения соответствующих строк
// минора.
static void s21_populate_minor(double **src, double **dest, int row, int column,
                               int a_size) {
  int k = 0;

  for (int i = 0; i < a_size; i++) {
    if (i != row) {
      s21_populate_minor_row(src[i], dest[k], column, a_size);
      k++;
    }
  }
}

// Минор матрицы и матрица алгебраических дополнений
// Эта функция вычисляет матрицу алгебраических дополнений для заданной матрицы
// A. В начале проверяется корректность входных параметров. Создается временный
// массив temp_minor, который будет использоваться для хранения миноров.
// Создается пустая матрица result, в которую будут записаны алгебраические
// дополнения. Затем для каждого элемента матрицы A вычисляется соответствующий
// минор, после чего вычисляется его определитель с помощью функции
// s21_determinant_array. Полученный определитель умножается на (-1)^(i + j),
// где i и j - координаты элемента в матрице, и записывается в соответствующий
// элемент матрицы result. После завершения цикла освобождается память,
// выделенная для временного массива temp_minor.
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int result_code = RES_OK;
  int n = A->rows;
  (void)result;

  if (!result || IS_NOT_VALID_MATRIX(A) || A->rows != A->columns) {
    result_code = RES_INCORRECT;
  }

  if (result_code == RES_OK) {
    double **temp_minor = s21_create_matrix_array(n - 1, n - 1);
    int result_code = s21_create_matrix(n, n, result);
    for (int i = 0; i < n && result_code == RES_OK; i++) {
      for (int j = 0; j < n; j++) {
        s21_populate_minor(A->matrix, temp_minor, i, j, n);
        double determinant = 0;
        result_code =
            s21_determinant_array(temp_minor, n - 1, n - 1, &determinant);
        if (result_code != RES_OK) {
          break;
        }
        result->matrix[i][j] = determinant * pow(-1, i + j);
      }
    }
    s21_free_matrix_array(temp_minor, n - 1);
  }
  return result_code;
}