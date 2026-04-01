#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Coefficients of the quadratic equation (ax^2 + bx + c = 0).
typedef struct coeff_t
{
    // Quadratic coefficient.
    int32_t a;
    // Linear coefficient.
    int32_t b;
    // Independent term.
    int32_t c;
} coeff_t;

// Roots of the quadratic equation.
typedef struct root_t
{
    // Real part of the first root.
    int32_t real1;
    // Imaginary part of the first root.
    int32_t imag1;
    // Real part of the second root.
    int32_t real2;
    // Imaginary part of the second root.
    int32_t imag2;
    // True if the  roots are complex conjugates.
    bool complex;
} root_t;

// Complex number.
typedef struct complex_t
{
    // Real part.
    int32_t real;
    // Imaginary part.
    int32_t imag;
} complex_t;

// Date.
typedef struct date_t
{
    // Day of the month (1-31).
    int8_t day;
    // Month of the year (1-12).
    int8_t month;
    // Year (e.g. 2025).
    int16_t year;
} date_t;

// Dynamic matrix.
typedef struct matriz_t
{
    // Pointer to the values of the matrix (row * column).
    int16_t **data;
    // Number of rows.
    size_t rows;
    // Number of columns.
    size_t cols;
} matriz_t;

// Prints the name of the group members.
void init_lab();

// Resolves the quadratic equation (ax^2 + bx + c = 0). Supports complex roots.
root_t *eq_solver(coeff_t *coeficientes);

// Converts a binary number (given as a string) to decimal.
// Provide sign = true if the binary number is signed.
int32_t bin2dec(char *binary, bool sign);

// Prints the array in reverse order, using a generic pointer.
void print_reverse_array(void *array, size_t data_type, size_t array_size);

// Prints the maximum value and its index in the array.
void max_index(void *array, size_t data_type, size_t array_size);

// Prints the minimum value and its index in the array.
void min_index(void *array, size_t data_type, size_t array_size);

// Returns the sub A - B. The matrices must have the same dimensions.
matriz_t *matrix_sub(matriz_t *A, matriz_t *B);

// Swaps the values of two pointers. Returns 0 on success, -1 on failure.
int swap(void *elem_1, void *elem_2, size_t data_type);

// Counts the number of consonants in a string.
int consonantes(char *string);

// Counts the number of vowels in a string.
int vocales(char *string);

// Prints and returns a reversed copy of the input string.
char *reverse_string(char *string);

// Returns the length of the input string. Returns -1 on failure.
int32_t string_length(char *string);

// Counts the number of words in a string.
int32_t string_words(char *string);

// Copy the source string.
int string_copy(char *source, char *destination);

// Searches the needle in the haystack string.
// Returns the index or -1 if not found.
int find_in_string(char *haystack, char *needle);

// Converts the string to uppercase in place.
void string_to_caps(char *string);

// Converts the string to lowercase in place.
void string_to_min(char *string);

// Returns the sum of two complex numbers.
complex_t sum(complex_t a, complex_t b);

// Returns the product of two complex numbers.
complex_t prod(complex_t a, complex_t b);

// Calculates the difference in days between two dates.
int days_left(date_t start, date_t finish);
