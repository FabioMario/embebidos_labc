#include "global.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    init_lab();

    // eq_solver
    // THIS EXAMPLE PRODUCES A WRONG OUTPUT BECAUSE THE ROOTS SHOULD BE FLOATS!!!
    // THE RESULT IS GETTING TRUNCATED, LOSING THE DECIMAL PART.
    int32_t a = 1;
    int32_t b = -2;
    int32_t c = 3;
    coeff_t coefficients = {a, b, c};
    printf("Resolving the equation: %dx^2 + %dx + %d = 0\n", a, b, c);
    root_t *roots = eq_solver(&coefficients);
    printf("The roots are:\n");
    if (roots->complex)
    {
        printf("Root 1: %d + %di\n", roots->real1, roots->imag1);
        printf("Root 2: %d + %di\n", roots->real2, roots->imag2);
    }
    else
    {
        printf("Root 1: %d\n", roots->real1);
        printf("Root 2: %d\n", roots->real2);
    }

    printf("\n");

    // bin2dec
    // unsigned 10
    char *binary = "1010";
    int32_t decimal = bin2dec(binary, false);
    printf("Binary %s -> Decimal %d\n", binary, decimal);

    // signed -10
    binary = "11111111111111111111111111110110";
    decimal = bin2dec(binary, true);
    printf("Binary %s -> Decimal %d\n", binary, decimal);

    // signed 10
    binary = "00000000000000000000000000001010";
    decimal = bin2dec(binary, true);
    printf("Binary %s -> Decimal %d\n", binary, decimal);

    printf("\n");

    // print_reverse_array
    int32_t to_reverse[] = {1, 2, 3};
    printf("Original array: 1 2 3\n");
    printf("Reversed array: ");
    print_reverse_array(to_reverse, sizeof(int32_t), 3);

    // max_index
    int32_t to_get_max[] = {1, 3, 2};
    printf("Array: 1 3 2 | ");
    max_index(to_get_max, sizeof(int32_t), 3);

    // min_index
    int32_t to_get_min[] = {1, 3, 2};
    printf("Array: 1 3 2 | ");
    min_index(to_get_min, sizeof(int32_t), 3);

    printf("\n");

    // matrix_sub
    // 1 2 3 - 1 2 3
    // 4 5 6   4 5 6
    matriz_t A;
    A.rows = 2;
    A.cols = 3;
    A.data = malloc(A.rows * sizeof(int16_t *));
    A.data[0] = malloc(A.cols * sizeof(int16_t));
    A.data[1] = malloc(A.cols * sizeof(int16_t));
    A.data[0][0] = 1;
    A.data[0][1] = 2;
    A.data[0][2] = 3;
    A.data[1][0] = 4;
    A.data[1][1] = 5;
    A.data[1][2] = 6;

    matriz_t B;
    B.rows = 2;
    B.cols = 3;
    B.data = malloc(B.rows * sizeof(int16_t *));
    B.data[0] = malloc(B.cols * sizeof(int16_t));
    B.data[1] = malloc(B.cols * sizeof(int16_t));
    B.data[0][0] = 1;
    B.data[0][1] = 2;
    B.data[0][2] = 3;
    B.data[1][0] = 4;
    B.data[1][1] = 5;
    B.data[1][2] = 6;

    matriz_t *sub = matrix_sub(&A, &B);
    printf("Matrix A:\n");
    for (size_t i = 0; i < A.rows; i++)
    {
        for (size_t j = 0; j < A.cols; j++)
        {
            printf("%d ", A.data[i][j]);
        }
        printf("\n");
    }
    printf("Matrix B:\n");
    for (size_t i = 0; i < B.rows; i++)
    {
        for (size_t j = 0; j < B.cols; j++)
        {
            printf("%d ", B.data[i][j]);
        }
        printf("\n");
    }
    printf("A - B:\n");
    for (size_t i = 0; i < sub->rows; i++)
    {
        for (size_t j = 0; j < sub->cols; j++)
        {
            printf("%d ", sub->data[i][j]);
        }
        printf("\n");
    }

    free(A.data[0]);
    free(A.data[1]);
    free(A.data);
    free(B.data[0]);
    free(B.data[1]);
    free(B.data);
    free(sub->data[0]);
    free(sub->data[1]);
    free(sub->data);
    free(sub);

    printf("\n");

    // swap
    int32_t swap_a = 1;
    int32_t swap_b = 2;
    printf("Before swap: a = %d, b = %d\n", swap_a, swap_b);
    swap(&swap_a, &swap_b, sizeof(int32_t));
    printf("After swap: a = %d, b = %d\n", swap_a, swap_b);

    printf("\n");

    char *hello = "Hello!";

    // consonantes y vocales
    int consonants = consonantes(hello);
    printf("\"%s\" has %d consonants\n", hello, consonants);
    int vowels = vocales(hello);
    printf("\"%s\" has %d vowels\n", hello, vowels);

    // reverse_string
    char *reversed = reverse_string(hello);
    if (reversed != NULL)
        free(reversed);

    // string_length
    int32_t length = string_length(hello);
    printf("Length: %d\n", length);

    // string_words
    char hello_world[] = "  Hello, world!";
    int32_t words = string_words(hello_world);
    printf("\"%s\" has %d words\n", hello_world, words);

    printf("\n");

    // string_copy
    char *original = "Hello!";
    char copy[7];
    string_copy(original, copy);
    printf("Original: %s | Copy: %s\n", original, copy);

    printf("\n");

    // find_in_string
    char *needle = "world";
    int index = find_in_string(hello_world, needle);
    printf("\"%s\" is in \"%s\" at index %d\n", needle, hello_world, index);

    printf("\n");

    // string_to_caps
    string_to_caps(hello_world);
    printf("Uppercase: %s\n", hello_world);

    // string_to_min
    string_to_min(hello_world);
    printf("Lowercase: %s\n", hello_world);

    printf("\n");

    // sum y prod
    complex_t c1 = {1, 2};
    complex_t c2 = {3, 4};
    complex_t sum_result = sum(c1, c2);
    printf("Sum: (%d + %di) + (%d + %di) = (%d + %di)\n", c1.real, c1.imag, c2.real, c2.imag, sum_result.real, sum_result.imag);
    complex_t prod_result = prod(c1, c2);
    printf("Product: (%d + %di) * (%d + %di) = (%d + %di)\n", c1.real, c1.imag, c2.real, c2.imag, prod_result.real, prod_result.imag);

    return 0;
}