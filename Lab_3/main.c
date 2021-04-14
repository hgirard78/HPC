#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void gen_rand(double *vector, size_t size, int min, int max)
{

    double r;
    for (size_t i = 0; i < size; i++)
    {
        r = (double) rand() / ((double) RAND_MAX + 1);
        r = r * (max - min) + min;
        vector[i] = r;
    }
}
void create_matrix(double **array, size_t nb_row, size_t nb_col, int k)
{
    size_t i, j;
    double *diagonal_value, *other_values;
    if (nb_row < nb_col)
    {
        diagonal_value = malloc(nb_row * sizeof(double));
        gen_rand(diagonal_value, nb_row, 1, 2);
    }
    else
    {
        diagonal_value = malloc(nb_col * sizeof(double));
        gen_rand(diagonal_value, nb_col, 1, 2);
    }
    other_values = malloc((nb_row * nb_col) * sizeof(double));

    gen_rand(other_values, nb_row * nb_col, 0, 1);

    int diago = 0;
    int other = 0;
    int nb_zero = nb_row - k - 1;
    for (i = 0; i < nb_row; i++)
    {
        int count_zero = 0;
        int k2 = k;
        for (j = 0; j < nb_col; j++)
        {  
            if (i == j)
            {
                array[i][j] = diagonal_value[diago];
                diago++;
            }
            else
            {   
                int zero = rand() % 2;
                if (k2 > 0 && zero == 0)
                {
                    array[i][j] = other_values[other];
                    other++;
                    k2--;
                }
                else if (count_zero + 1 != nb_zero)
                {
                    array[i][j] = 0;
                    count_zero++;
                }
                else if (k2 > 0)
                {
                    array[i][j] = other_values[other];
                    other++;
                    k2--;
                }
                else
                {
                    array[i][j] = 0;
                }
            }

        }
    }
    free(diagonal_value);
    free(other_values);
}

void print_matrix(double **array, size_t nb_row, size_t nb_col)
{
    size_t i, j;
    for (i = 0; i < nb_row; i++)
    {
        for (j = 0; j < nb_col; j++)
        {
            printf("array[%ld][%ld] = %lf ", i, j, array[i][j]);
        }
        printf("\n");
    }

}

void create_vector(double **array, double *val, int *col_ind, int *raw_ptr, size_t nb_row, size_t nb_col)
{
    size_t i, j;
    int new_line = 0;
    size_t size_ptr = 0;
    size_t size_val = 0;
    size_t size_col = 0;
    for (i = 0; i < nb_row; i++)
    {
        new_line = 1;
        for (j = 0; j < nb_col; j++)
        {

            if (array[i][j] != 0)
            {
                val[size_val] = array[i][j];
                if (new_line)
                {
                    raw_ptr[size_ptr] = size_val;
                    size_ptr++;
                    new_line = 0;
                }
                size_val++;
                col_ind[size_col] = j;
                size_col++;
            }
        }
    }
    raw_ptr[size_ptr] = size_val;
    size_ptr++;
    printf("raw_ptr: ");
    for (i = 0; i < size_ptr; i++)
    {
        printf("| %d ", raw_ptr[i]);
    }
    printf("\nval: ");
    for (i = 0; i < size_val; i++)
    {
        printf("| %lf ", val[i]);
    }
    printf("\ncol_ind: ");
    for (i = 0; i < size_col; i++)
    {
        printf("| %d ", col_ind[i]);
    }
    printf("\n");

}

void matrix_vector_product(double *result, double *x, double *val, int* col_ind, int* raw_ptr, size_t nb_row)
{
    size_t i;
    int j;

    for (i = 0; i < nb_row; i++)
    {
        for (j = raw_ptr[i]; j < raw_ptr[i + 1] ; j++)
        {
            result[i] += val[j] * x[col_ind[j]];
        }
    }
    for (i = 0; i < nb_row; i++)
        printf("result[%ld] = %lf\n", i, result[i]);
}

void test_product(double **array, double* old_result, double *x, size_t nb_row, size_t nb_col)
{
    size_t i, j;
    double *result = (double *) calloc(nb_row, sizeof(double));
    for(i = 0; i < nb_row; i++)
    {
        for(j = 0; j < nb_col; j++)
            result[i] += array[i][j] * x[j];
    }
    for (i = 0; i < nb_row; i++)
    {
        if (result[i] != old_result[i])
            printf("bad product\n");
    }
    free(result);
}

void free_all(double **array, double *result, double *val, 
        int *raw_ptr, int *col_ind, double *x, size_t nb_row)
{
    free(val);
    free(col_ind);
    free(raw_ptr);
    free(x);
    free(result);
    for (size_t i = 0; i < nb_row; i++)
        free(array[i]);
    free(array);
}
int main(void)
{

    srand(time(NULL));
    size_t nb_row, nb_col, i;
    int k;
    printf("Enter the desired matrix row numbers: ");
    scanf("%lu", &nb_row);
    printf("Enter the desired matrix column numbers: ");
    scanf("%lu", &nb_col);
    printf("matrix size: %lux%lu\n", nb_row, nb_col);
    printf("How much non-zero elements in each row? ");
    scanf("%d", &k);

    double **array = (double **) calloc(nb_row, sizeof(double *));
    for (i = 0; i < nb_row; i++)
    {
        array[i] = (double *) calloc(nb_col, sizeof(double));
    }

    double *val = (double *) calloc(nb_row * nb_col, sizeof(double));
    int *col_ind = (int *) calloc(nb_row * nb_col, sizeof(int));
    int *raw_ptr = (int *) calloc(nb_row + 1, sizeof(int));
    double *x;
    if (nb_row < nb_col)
    {
        x = (double *) calloc(nb_col, sizeof(double));
        gen_rand(x, nb_col, 1, 20);
    }
    else
    {
        x = (double *) calloc(nb_row, sizeof(double));
        gen_rand(x, nb_row, 1, 20);
    }
    double *result = (double *) calloc(nb_row, sizeof(double));

    create_matrix(array, nb_row, nb_col, k);
    print_matrix(array, nb_row, nb_col);
    create_vector(array, val, col_ind, raw_ptr, nb_row, nb_col);
    matrix_vector_product(result, x, val, col_ind, raw_ptr, nb_row);
    test_product(array, result, x, nb_row, nb_col);
    free_all(array, result, val, raw_ptr, col_ind, x, nb_row);
    sleep(10000);
    return 0;
}
