#include "global.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_lab()
{
    printf("*** Grupo FF ***\n");
    printf("Fabio Luzzatto, Franco Pereira\n\n");
}

root_t *eq_solver(coeff_t *coeficientes)
{
    // We have to allocate memory for the pointer we are going to return.
    // It's the caller's responsibility to free it when no longer needed.
    root_t *roots = malloc(sizeof(root_t));

    // "->" is used here instead of "." because `coeficientes` is a pointer to,
    // not the struct value itself.
    int32_t a = coeficientes->a;
    int32_t b = coeficientes->b;
    int32_t c = coeficientes->c;

    int32_t discriminant = b * b - 4 * a * c;

    if (discriminant >= 0)
    {
        // Real roots.
        roots->real1 = (-b + sqrt(discriminant)) / (2 * a);
        roots->real2 = (-b - sqrt(discriminant)) / (2 * a);
        roots->imag1 = 0;
        roots->imag2 = 0;
        roots->complex = false;
    }
    else
    {
        // Complex roots.
        roots->real1 = -b / (2 * a);
        roots->real2 = -b / (2 * a);
        roots->imag1 = sqrt(-discriminant) / (2 * a);
        roots->imag2 = -sqrt(-discriminant) / (2 * a);
        roots->complex = true;
    }

    return roots;
}

int32_t bin2dec(char *binary, bool sign)
{
    int32_t result = 0;
    int32_t i = 0;
    int32_t power = 1;

    for (; binary[i] != '\0'; i++)
    {
        result = result * 2 + (binary[i] != '0' ? 1 : 0);
        if (sign)
        {
            power *= 2;
        }
    }
    if (sign && binary[0] == '1')
    {
        result -= power; // Corrects the value (two's complement).
    }

    return result;
}

// Prints the element pointed by `elem` according to its data type.
// Assumes data_type is a char or an integer.
void print_element(void *elem, size_t data_type, char *suffix)
{
    if (data_type == sizeof(char))
    {
        printf("%c%s", *(char *)elem, suffix);
    }
    else if (data_type == sizeof(int16_t))
    {
        printf("%d%s", *(int16_t *)elem, suffix);
    }
    else if (data_type == sizeof(int32_t))
    {
        printf("%d%s", *(int32_t *)elem, suffix);
    }
    else if (data_type == sizeof(int64_t))
    {
        printf("%lld%s", (long long)*(int64_t *)elem, suffix);
    }
}

// Returns > 0 if a > b, < 0 if a < b, 0 if equal.
// Assumes data_type is a char or an integer.
int compare_elements(void *a, void *b, size_t data_type)
{
    if (data_type == sizeof(char))
        return (int)(*(char *)a) - (int)(*(char *)b);
    if (data_type == sizeof(int16_t))
        return (int)(*(int16_t *)a) - (int)(*(int16_t *)b);
    if (data_type == sizeof(int32_t))
    {
        int32_t aa = *(int32_t *)a, bb = *(int32_t *)b;
        return (aa > bb) - (aa < bb);
    }
    if (data_type == sizeof(int64_t))
    {
        int64_t aa = *(int64_t *)a, bb = *(int64_t *)b;
        return (aa > bb) - (aa < bb);
    }
    return 0;
}

void print_reverse_array(void *array, size_t data_type, size_t array_size)
{
    // We can't do pointer arithmetic with void*, so we need to cast it to char*.
    char *ptr = (char *)array;

    for (size_t i = array_size; i > 0; i--)
    {
        print_element(ptr + (i - 1) * data_type, data_type, " ");
    }
    printf("\n");
}

void max_index(void *array, size_t data_type, size_t array_size)
{
    char *ptr = (char *)array;
    size_t max_i = 0;

    for (size_t i = 1; i < array_size; i++)
    {
        void *current = ptr + i * data_type;
        void *max = ptr + max_i * data_type;
        if (compare_elements(current, max, data_type) > 0)
        {
            max_i = i;
        }
    }

    printf("Max index: %zu, Value: ", max_i);
    print_element(ptr + max_i * data_type, data_type, "\n");
}

void min_index(void *array, size_t data_type, size_t array_size)
{
    char *ptr = (char *)array;
    size_t min_i = 0;

    for (size_t i = 1; i < array_size; i++)
    {
        void *current = ptr + i * data_type;
        void *min = ptr + min_i * data_type;
        if (compare_elements(current, min, data_type) < 0)
        {
            min_i = i;
        }
    }

    printf("Min index: %zu, Value: ", min_i);
    print_element(ptr + min_i * data_type, data_type, "\n");
}

matriz_t *matrix_sub(matriz_t *A, matriz_t *B)
{
    if (A->rows != B->rows || A->cols != B->cols)
    {
        fprintf(stderr, "Error: Matrices not matching dimensions");
        return NULL;
    }

    matriz_t *result = malloc(sizeof(matriz_t));
    result->rows = A->rows;
    result->cols = A->cols;
    // `matriz_t->data` is a pointer to a pointer; `data` points to rows, and the rows point to columns.
    // That means the rows live outside the struct itself, so we need a separate allocation for them.
    result->data = malloc(result->rows * sizeof(int16_t *));

    for (size_t i = 0; i < result->rows; i++)
    {
        result->data[i] = malloc(result->cols * sizeof(int16_t));
        for (size_t j = 0; j < result->cols; j++)
        {
            result->data[i][j] = A->data[i][j] - B->data[i][j];
        }
    }
    return result;
}

int swap(void *elem_1, void *elem_2, size_t data_type)
{
    void *temp = malloc(data_type);
    if (temp == NULL)
        return -1;

    memcpy(temp, elem_1, data_type);
    memcpy(elem_1, elem_2, data_type);
    memcpy(elem_2, temp, data_type);
    free(temp);
    return 0;
}

int consonantes(char *string)
{
    int count = 0;
    for (size_t i = 0; string[i] != '\0'; i++)
    {
        char c = string[i];
        // Not all characters are letters, so checking if they are not AEIOU is not enough.
        if ((c >= 'b' && c <= 'z') || (c >= 'B' && c <= 'Z'))
        {
            if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' &&
                c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U')
            {
                count++;
            }
        }
    }
    return count;
}

int vocales(char *string)
{
    int count = 0;
    for (size_t i = 0; string[i] != '\0'; i++)
    {
        char c = string[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        {
            count++;
        }
    }
    return count;
}

char *reverse_string(char *string)
{
    size_t len = strlen(string);
    char *reversed = malloc(len + 1); // `strlen` does not include the last "\0" character.
    if (reversed == NULL)
        return NULL;

    for (size_t i = len; i > 0; i--)
    {
        reversed[len - i] = string[i - 1];
    }
    reversed[len] = '\0';
    printf("Reversed: %s\n", reversed);
    return reversed;
}

int32_t string_length(char *string)
{
    int32_t length = 0;
    while (string[length] != '\0')
    {
        length++;
        if (length < 0) // Too large strings would overflow.
            return -1;
    }
    return length;
}

int32_t string_words(char *string)
{
    int32_t separators = 0;
    int32_t len = string_length(string);
    for (size_t i = 0; i < len; i++)
    {
        if (string[i] == ' ')
        {
            // If the string start with a space, it should not count as a separator.
            if (i == 0)
                continue;
            // Consider consecutive spaces as a single separator.
            else if (string[i - 1] == ' ')
                continue;
            separators++;
        }
    }

    return separators + 1;
}

int string_copy(char *source, char *destination)
{
    if (source == NULL || destination == NULL)
        return -1;

    size_t i = 0;
    while (source[i] != '\0')
    {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
    return 0;
}

int find_in_string(char *haystack, char *needle)
{
    char first_char = needle[0];
    int i = 0;
    while (haystack[i] != '\0')
    {
        // Check until we find the first character of the needle.
        if (haystack[i] == first_char)
        {
            // Check if the rest matches.
            size_t j = 1;
            while (needle[j] != '\0' && haystack[i + j] == needle[j])
                j++;

            if (needle[j] == '\0')
                // We found the whole needle, return it's starting index in the haystack.
                return i;
        }
        i++;
    }
    return -1;
}

void string_to_caps(char *string)
{
    for (size_t i = 0; string[i] != '\0'; i++)
    {
        if (string[i] >= 'a' && string[i] <= 'z')
        {
            string[i] = string[i] - ('a' - 'A'); // Difference in the ASCII table.
        }
    }
}

void string_to_min(char *string)
{
    for (size_t i = 0; string[i] != '\0'; i++)
    {
        if (string[i] >= 'A' && string[i] <= 'Z')
        {
            string[i] = string[i] + ('a' - 'A'); // Difference in the ASCII table.
        }
    }
}

complex_t sum(complex_t a, complex_t b)
{
    complex_t result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

complex_t prod(complex_t a, complex_t b)
{
    complex_t result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}

// Returns number of days since 1970-01-01.
// Howard Hinnant's algorithm: https://howardhinnant.github.io/date_algorithms.html#days_from_civil
int days_from_civil(date_t date)
{
    int y = date.year;
    int m = date.month;
    int d = date.day;

    if (m <= 2)
        y--;

    int era = (y >= 0 ? y : y - 399) / 400;
    unsigned yoe = (unsigned)(y - era * 400);
    unsigned doy = (153 * (m > 2 ? m - 3 : m + 9) + 2) / 5 + d - 1;
    unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + (int)doe - 719468;
}

int days_left(date_t start, date_t finish)
{
    int start_days = days_from_civil(start);
    int finish_days = days_from_civil(finish);
    return finish_days - start_days;
}