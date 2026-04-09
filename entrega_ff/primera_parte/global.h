#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/** Coefficients of the quadratic equation (ax^2 + bx + c = 0). */
typedef struct coeff_t
{
    /** Quadratic coefficient. */
    int32_t a;
    /** Linear coefficient. */
    int32_t b;
    /** Independent term. */
    int32_t c;
} coeff_t;

/** Roots of the quadratic equation. */
typedef struct root_t
{
    /** Real part of the first root. */
    double real1;
    /** Imaginary part of the first root. */
    double imag1;
    /** Real part of the second root. */
    double real2;
    /** Imaginary part of the second root. */
    double imag2;
    /** True if the roots are complex conjugates. */
    bool complex;
} root_t;

/** Complex number. */
typedef struct complex_t
{
    /** Real part. */
    int32_t real;
    /** Imaginary part. */
    int32_t imag;
} complex_t;

/** Date. */
typedef struct date_t
{
    /** Day of the month (1-31). */
    int8_t day;
    /** Month of the year (1-12). */
    int8_t month;
    /** Year (e.g. 2025). */
    int16_t year;
} date_t;

/** Dynamic matrix. */
typedef struct matriz_t
{
    /** Pointer to the values of the matrix (row * column). */
    int16_t **data;
    /** Number of rows. */
    size_t rows;
    /** Number of columns. */
    size_t cols;
} matriz_t;

/** Supported data types for functions using generic pointers. */
typedef enum data_type_t
{
    TYPE_INT8,
    TYPE_INT32,
    TYPE_FLOAT,
    TYPE_DOUBLE,
} data_type_t;

void print_coeff(coeff_t *coeff);
void print_root(root_t *root);
void print_complex(complex_t *complex);
void print_date(date_t *date);
void print_matriz(matriz_t *matriz);

/** Prints the name of the group members **/
void init_lab();

/**
 * Resolves the quadratic equation (ax^2 + bx + c = 0). Supports complex roots.
 * @param coeficientes (a, b, c) of the equation.
 * @returns the roots of the equation or NULL if there was an error.
 */
root_t *eq_solver(coeff_t *coeficientes);

/**
 * Converts a binary number (given as a string) to decimal.
 * @param binary number as a string.
 * @param sign if the binary number is signed.
 * @returns the value as an integer.
 */
int32_t bin2dec(char *binary, bool sign);

/**
 * Prints the array in reverse order, using a generic pointer.
 * @param array pointer to the first element of the array.
 * @param type of the elements in the array.
 * @param array_size number of elements in the array.
 */
void print_reverse_array(void *array, data_type_t type, size_t array_size);

/**
 * Prints the maximum value and its index in the array.
 * @param array pointer to the first element of the array.
 * @param type of the elements in the array.
 * @param array_size number of elements in the array.
 * @returns the index of the maximum value, or -1 if the array is NULL or empty.
 */
int max_index(void *array, data_type_t type, size_t array_size);

/**
 * Prints the minimum value and its index in the array.
 * @param array pointer to the first element of the array.
 * @param type of the elements in the array.
 * @param array_size number of elements in the array.
 * @returns the index of the minimum value, or -1 if the array is NULL or empty.
 */
int min_index(void *array, data_type_t type, size_t array_size);

/**
 * Returns the sub A - B. The matrices must have the same dimensions.
 * @param A first matrix.
 * @param B second matrix.
 * @returns the resulting matrix, or NULL if `A` and `B` have different dimensions or on other error.
 */
matriz_t *matrix_sub(matriz_t A, matriz_t B);

/**
 * Swaps the values of two pointers. Returns 0 on success, -1 on failure.
 * @param elem_1 pointer to the first element.
 * @param elem_2 pointer to the second element.
 * @param data_type size of the elements.
 * @returns 0 on success, -1 on failure.
 */
int swap(void *elem_1, void *elem_2, size_t data_type);

/**
 * Counts the number of consonants in a string.
 * @param string to analyze.
 * @returns the number of consonants, or -1 if the string is NULL.
 */
int consonantes(char *string);

/**
 * Counts the number of vowels in a string.
 * @param string to analyze.
 * @returns the number of vowels, or -1 if the string is NULL.
 */
int vocales(char *string);

/**
 * Prints and returns a reversed copy of the input string.
 * @param string to reverse.
 * @returns the reversed string, or NULL on failure. The caller is responsible for freeing the returned string.
 */
char *reverse_string(char *string);

/**
 * Returns the length of the input string.
 * @param string to analyze.
 * @returns the length of the string, or -1 if the string is NULL or the count overflows.
 */
int32_t string_length(char *string);

/**
 * Counts the number of words in a string.
 * @param string to analyze.
 * @returns the number of words, or -1 if the string is NULL.
 */
int32_t string_words(char *string);

/**
 * Copies the string.
 * @param source string to copy.
 * @param destination to place the copy.
 * @returns 0 on success, -1 if either soruce or destination is NULL.
 */
int string_copy(char *source, char *destination);

/**
 * Searches the needle in the haystack string.
 * @param haystack string to search in.
 * @param needle string to look for.
 * @returns the index of the first occurrence, or -1 if not found.
 */
int find_in_string(char *haystack, char *needle);

/**
 * Converts the string to uppercase in place.
 * @param string to convert.
 */
void string_to_caps(char *string);

/**
 * Converts the string to lowercase in place.
 * @param string to convert.
 */
void string_to_min(char *string);

/**
 * Adds two complex numbers.
 * @param a first complex number.
 * @param b second complex number.
 * @returns the sum of the two complex numbers, or NULL on failure. The caller is responsible for freeing the returned number.
 */
complex_t *sum(complex_t a, complex_t b);

/**
 * Multiplies two complex numbers.
 * @param a first complex number.
 * @param b second complex number.
 * @returns the product of the two complex numbers, or NULL on failure. The caller is responsible for freeing the returned number.
 */
complex_t *prod(complex_t a, complex_t b);

/**
 * Calculates the number of days between two dates.
 * @param start date.
 * @param finish date.
 * @returns positive if `finish` is later than `start`, negative if earlier, or 0 if they are the same date.
 */
int days_left(date_t start, date_t finish);
