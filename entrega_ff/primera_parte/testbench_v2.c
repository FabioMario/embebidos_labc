/**
 * testbench_v2.c — Validador automático del Laboratorio C (versión 2)
 * Fundamentos de Programación
 *
 * Compilar:
 *   gcc -Wall -Wextra -std=c11 -o testbench testbench_v2.c global.c -lm
 *
 * Ejecutar:
 *   ./testbench
 *
 * Cada test imprime [PASS] o [FAIL] con detalle del error.
 * El programa retorna 0 si todos los tests pasaron, 1 si alguno falló.
 */

#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* ═══════════════════════════════════════════════════════════════════
 * Utilidades del testbench
 * ═══════════════════════════════════════════════════════════════════ */

static int tests_run    = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BOLD    "\033[1m"

#define TEST(name, cond, fmt, ...)                                      \
    do {                                                                 \
        tests_run++;                                                     \
        if (cond) {                                                      \
            printf(GREEN "[PASS]" RESET " %s\n", name);                 \
            tests_passed++;                                              \
        } else {                                                         \
            printf(RED   "[FAIL]" RESET " %s — " fmt "\n",             \
                   name, ##__VA_ARGS__);                                 \
            tests_failed++;                                              \
        }                                                                \
    } while (0)

#define SECTION(title) \
    printf("\n" BOLD YELLOW "═══ %s ═══" RESET "\n", title)

/* Comparación con tolerancia para double */
#define DOUBLE_EQ(a, b) (fabs((a) - (b)) < 1e-9)

/* ═══════════════════════════════════════════════════════════════════
 * 1. eq_solver
 * ═══════════════════════════════════════════════════════════════════ */
void test_eq_solver(void) {
    SECTION("eq_solver");

    /* Caso 1: dos raíces reales distintas  x²-5x+6=0 → x=2, x=3 */
    coeff_t c1 = {1, -5, 6};
    root_t *r1 = eq_solver(&c1);
    TEST("raíces reales distintas — no NULL",
         r1 != NULL, "retornó NULL");
    if (r1) {
        TEST("raíces reales distintas — complex=false",
             r1->complex == false, "complex=%d", r1->complex);
        int ok = (DOUBLE_EQ(r1->real1, 2.0) && DOUBLE_EQ(r1->real2, 3.0)) ||
                 (DOUBLE_EQ(r1->real1, 3.0) && DOUBLE_EQ(r1->real2, 2.0));
        TEST("raíces reales distintas — valores (2.0 y 3.0)",
             ok, "real1=%.4f real2=%.4f", r1->real1, r1->real2);
        free(r1);
    }

    /* Caso 2: raíz doble  x²-2x+1=0 → x=1 */
    coeff_t c2 = {1, -2, 1};
    root_t *r2 = eq_solver(&c2);
    TEST("raíz doble — no NULL", r2 != NULL, "retornó NULL");
    if (r2) {
        TEST("raíz doble — complex=false",
             r2->complex == false, "complex=%d", r2->complex);
        TEST("raíz doble — valor 1.0",
             DOUBLE_EQ(r2->real1, 1.0) && DOUBLE_EQ(r2->real2, 1.0),
             "real1=%.4f real2=%.4f", r2->real1, r2->real2);
        free(r2);
    }

    /* Caso 3: raíces complejas  x²+1=0 → ±i */
    coeff_t c3 = {1, 0, 1};
    root_t *r3 = eq_solver(&c3);
    TEST("raíces complejas — no NULL", r3 != NULL, "retornó NULL");
    if (r3) {
        TEST("raíces complejas — complex=true",
             r3->complex == true, "complex=%d", r3->complex);
        TEST("raíces complejas — parte real = 0",
             DOUBLE_EQ(r3->real1, 0.0), "real1=%.4f", r3->real1);
        TEST("raíces complejas — parte imag = ±1",
             DOUBLE_EQ(fabs(r3->imag1), 1.0), "imag1=%.4f", r3->imag1);
        free(r3);
    }

    /* Caso 4: raíces reales no enteras  x²-3=0 → ±√3 */
    coeff_t c4 = {1, 0, -3};
    root_t *r4 = eq_solver(&c4);
    TEST("raíces irracionales — no NULL", r4 != NULL, "retornó NULL");
    if (r4) {
        TEST("raíces irracionales — complex=false",
             r4->complex == false, "complex=%d", r4->complex);
        double expected = sqrt(3.0);
        int ok4 = (DOUBLE_EQ(fabs(r4->real1), expected) &&
                   DOUBLE_EQ(fabs(r4->real2), expected));
        TEST("raíces irracionales — valores ±√3 ≈ ±1.7321",
             ok4, "real1=%.4f real2=%.4f", r4->real1, r4->real2);
        free(r4);
    }
}

/* ═══════════════════════════════════════════════════════════════════
 * 2. bin2dec
 * ═══════════════════════════════════════════════════════════════════ */
void test_bin2dec(void) {
    SECTION("bin2dec");

    TEST("\"1010\" sin signo = 10",
         bin2dec("1010", false) == 10,
         "obtenido %d", bin2dec("1010", false));

    TEST("\"0\" sin signo = 0",
         bin2dec("0", false) == 0,
         "obtenido %d", bin2dec("0", false));

    TEST("\"11111111\" sin signo = 255",
         bin2dec("11111111", false) == 255,
         "obtenido %d", bin2dec("11111111", false));

    TEST("\"00001010\" sin signo = 10",
         bin2dec("00001010", false) == 10,
         "obtenido %d", bin2dec("00001010", false));

    /* Complemento a 2, 8 bits: 10000001 = -127 */
    TEST("\"10000001\" con signo = -127",
         bin2dec("10000001", true) == -127,
         "obtenido %d", bin2dec("10000001", true));

    /* Complemento a 2: 11111111 = -1 */
    TEST("\"11111111\" con signo = -1",
         bin2dec("11111111", true) == -1,
         "obtenido %d", bin2dec("11111111", true));
}

/* ═══════════════════════════════════════════════════════════════════
 * 3. print_reverse_array  (verificación visual + no crash)
 *    No podemos capturar stdout fácilmente sin pipes, así que
 *    verificamos que la función no crashee y aceptamos inspección manual.
 * ═══════════════════════════════════════════════════════════════════ */
void test_print_reverse_array(void) {
    SECTION("print_reverse_array");

    int32_t arr_i[] = {3, 1, 4, 1, 5, 9};
    printf("  [INFO] print_reverse_array int32  → esperado: 9 5 1 4 1 3\n"
           "         salida real: ");
    print_reverse_array(arr_i, TYPE_INT32, 6);
    printf("\n");
    TEST("print_reverse_array TYPE_INT32 no crashea", true, "");

    float arr_f[] = {1.5f, 3.2f, 0.8f};
    printf("  [INFO] print_reverse_array float  → esperado: 0.80 3.20 1.50\n"
           "         salida real: ");
    print_reverse_array(arr_f, TYPE_FLOAT, 3);
    printf("\n");
    TEST("print_reverse_array TYPE_FLOAT no crashea", true, "");

    double arr_d[] = {-1.0, 2.5, 0.0};
    printf("  [INFO] print_reverse_array double → esperado: 0.00 2.50 -1.00\n"
           "         salida real: ");
    print_reverse_array(arr_d, TYPE_DOUBLE, 3);
    printf("\n");
    TEST("print_reverse_array TYPE_DOUBLE no crashea", true, "");
}

/* ═══════════════════════════════════════════════════════════════════
 * 4. max_index / min_index
 * ═══════════════════════════════════════════════════════════════════ */
void test_max_min_index(void) {
    SECTION("max_index / min_index");

    int32_t arr[] = {3, 1, 9, 4, 5, 2};
    /* max = 9 en índice 2 */
    int idx_max = max_index(arr, TYPE_INT32, 6);
    TEST("max_index TYPE_INT32 — índice correcto (2)",
         idx_max == 2, "obtenido %d", idx_max);

    /* min = 1 en índice 1 */
    int idx_min = min_index(arr, TYPE_INT32, 6);
    TEST("min_index TYPE_INT32 — índice correcto (1)",
         idx_min == 1, "obtenido %d", idx_min);

    /* Array con un solo elemento */
    int32_t solo[] = {42};
    TEST("max_index array size=1 → índice 0",
         max_index(solo, TYPE_INT32, 1) == 0,
         "obtenido %d", max_index(solo, TYPE_INT32, 1));
    TEST("min_index array size=1 → índice 0",
         min_index(solo, TYPE_INT32, 1) == 0,
         "obtenido %d", min_index(solo, TYPE_INT32, 1));

    /* NULL / size=0 → debe retornar -1 */
    TEST("max_index NULL → -1",
         max_index(NULL, TYPE_INT32, 6) == -1,
         "obtenido %d", max_index(NULL, TYPE_INT32, 6));
    TEST("max_index size=0 → -1",
         max_index(arr, TYPE_INT32, 0) == -1,
         "obtenido %d", max_index(arr, TYPE_INT32, 0));

    /* Con floats */
    float farr[] = {1.5f, 3.2f, 0.8f, 2.1f};
    TEST("max_index TYPE_FLOAT — índice correcto (1)",
         max_index(farr, TYPE_FLOAT, 4) == 1,
         "obtenido %d", max_index(farr, TYPE_FLOAT, 4));
    TEST("min_index TYPE_FLOAT — índice correcto (2)",
         min_index(farr, TYPE_FLOAT, 4) == 2,
         "obtenido %d", min_index(farr, TYPE_FLOAT, 4));

    /* Con int8 */
    int8_t arr8[] = {10, -5, 20, 3};
    TEST("max_index TYPE_INT8 — índice correcto (2)",
         max_index(arr8, TYPE_INT8, 4) == 2,
         "obtenido %d", max_index(arr8, TYPE_INT8, 4));
    TEST("min_index TYPE_INT8 — índice correcto (1)",
         min_index(arr8, TYPE_INT8, 4) == 1,
         "obtenido %d", min_index(arr8, TYPE_INT8, 4));
}

/* ═══════════════════════════════════════════════════════════════════
 * 5. swap
 * ═══════════════════════════════════════════════════════════════════ */
void test_swap(void) {
    SECTION("swap");

    int a = 5, b = 10;
    int ret = swap(&a, &b, sizeof(int));
    TEST("swap int — retorna 0",    ret == 0, "retornó %d", ret);
    TEST("swap int — a vale 10",    a == 10,  "a=%d", a);
    TEST("swap int — b vale 5",     b == 5,   "b=%d", b);

    double x = 3.14, y = 2.71;
    swap(&x, &y, sizeof(double));
    TEST("swap double — x vale 2.71", DOUBLE_EQ(x, 2.71), "x=%f", x);
    TEST("swap double — y vale 3.14", DOUBLE_EQ(y, 3.14), "y=%f", y);

    char ca = 'A', cb = 'Z';
    swap(&ca, &cb, sizeof(char));
    TEST("swap char — ca vale 'Z'", ca == 'Z', "ca=%c", ca);
    TEST("swap char — cb vale 'A'", cb == 'A', "cb=%c", cb);

    TEST("swap NULL → retorna -1",
         swap(NULL, &b, sizeof(int)) == -1,
         "debería retornar -1");
}

/* ═══════════════════════════════════════════════════════════════════
 * 6. consonantes / vocales
 * ═══════════════════════════════════════════════════════════════════ */
void test_consonantes_vocales(void) {
    SECTION("consonantes / vocales");

    TEST("vocales     \"hola mundo\"   = 4",
         vocales("hola mundo") == 4,
         "obtenido %d", vocales("hola mundo"));
    TEST("consonantes \"hola mundo\"   = 5",
         consonantes("hola mundo") == 5,
         "obtenido %d", consonantes("hola mundo"));
    TEST("vocales     \"AEIOU\"        = 5",
         vocales("AEIOU") == 5,
         "obtenido %d", vocales("AEIOU"));
    TEST("consonantes \"AEIOU\"        = 0",
         consonantes("AEIOU") == 0,
         "obtenido %d", consonantes("AEIOU"));
    TEST("vocales     \"\"             = 0",
         vocales("") == 0,
         "obtenido %d", vocales(""));
    TEST("consonantes \"bcdfg\"        = 5",
         consonantes("bcdfg") == 5,
         "obtenido %d", consonantes("bcdfg"));
    /* Espacios y dígitos no cuentan */
    TEST("vocales     \"123 abc\"      = 1",
         vocales("123 abc") == 1,
         "obtenido %d", vocales("123 abc"));
}

/* ═══════════════════════════════════════════════════════════════════
 * 7. reverse_string
 * ═══════════════════════════════════════════════════════════════════ */
void test_reverse_string(void) {
    SECTION("reverse_string");

    char *r = reverse_string("abcd");
    TEST("reverse_string \"abcd\" = \"dcba\"",
         r != NULL && strcmp(r, "dcba") == 0,
         "obtenido \"%s\"", r ? r : "(null)");
    free(r);

    char *r2 = reverse_string("a");
    TEST("reverse_string \"a\" = \"a\"",
         r2 != NULL && strcmp(r2, "a") == 0,
         "obtenido \"%s\"", r2 ? r2 : "(null)");
    free(r2);

    char *r3 = reverse_string("");
    TEST("reverse_string \"\" = \"\"",
         r3 != NULL && strcmp(r3, "") == 0,
         "obtenido \"%s\"", r3 ? r3 : "(null)");
    free(r3);

    char *r4 = reverse_string("racecar");
    TEST("reverse_string \"racecar\" = \"racecar\" (palíndromo)",
         r4 != NULL && strcmp(r4, "racecar") == 0,
         "obtenido \"%s\"", r4 ? r4 : "(null)");
    free(r4);
}

/* ═══════════════════════════════════════════════════════════════════
 * 8. string_length
 * ═══════════════════════════════════════════════════════════════════ */
void test_string_length(void) {
    SECTION("string_length");

    TEST("string_length \"hello\"  = 5",
         string_length("hello") == 5,
         "obtenido %d", string_length("hello"));
    TEST("string_length \"\"       = 0",
         string_length("") == 0,
         "obtenido %d", string_length(""));
    TEST("string_length \"abc\"    = 3",
         string_length("abc") == 3,
         "obtenido %d", string_length("abc"));
    TEST("string_length NULL     = -1",
         string_length(NULL) == -1,
         "obtenido %d", string_length(NULL));
}

/* ═══════════════════════════════════════════════════════════════════
 * 9. string_words
 * ═══════════════════════════════════════════════════════════════════ */
void test_string_words(void) {
    SECTION("string_words");

    TEST("\"hola mundo\"         = 2",
         string_words("hola mundo") == 2,
         "obtenido %d", string_words("hola mundo"));
    TEST("\"  espacios  extra \" = 2",
         string_words("  espacios  extra ") == 2,
         "obtenido %d", string_words("  espacios  extra "));
    TEST("\"\"                   = 0",
         string_words("") == 0,
         "obtenido %d", string_words(""));
    TEST("\"unapalabra\"         = 1",
         string_words("unapalabra") == 1,
         "obtenido %d", string_words("unapalabra"));
    TEST("\"a b c d\"            = 4",
         string_words("a b c d") == 4,
         "obtenido %d", string_words("a b c d"));
}

/* ═══════════════════════════════════════════════════════════════════
 * 10. string_copy
 * ═══════════════════════════════════════════════════════════════════ */
void test_string_copy(void) {
    SECTION("string_copy");

    char dst[64] = {0};
    int ret = string_copy("fuente", dst);
    TEST("string_copy retorna 0 en éxito",   ret == 0,  "retornó %d", ret);
    TEST("string_copy copia correctamente",
         strcmp(dst, "fuente") == 0, "dst=\"%s\"", dst);

    char dst2[64] = {0};
    string_copy("", dst2);
    TEST("string_copy string vacío",
         strcmp(dst2, "") == 0, "dst2=\"%s\"", dst2);

    TEST("string_copy NULL source → != 0",
         string_copy(NULL, dst) != 0, "debería retornar != 0");
}

/* ═══════════════════════════════════════════════════════════════════
 * 11. find_in_string
 * ═══════════════════════════════════════════════════════════════════ */
void test_find_in_string(void) {
    SECTION("find_in_string");

    TEST("\"abcde\" busca \"cd\"  = 2",
         find_in_string("abcde", "cd") == 2,
         "obtenido %d", find_in_string("abcde", "cd"));
    TEST("\"abcde\" busca \"xy\"  = -1",
         find_in_string("abcde", "xy") == -1,
         "obtenido %d", find_in_string("abcde", "xy"));
    TEST("\"abc\" busca \"\"     = 0",
         find_in_string("abc", "") == 0,
         "obtenido %d", find_in_string("abc", ""));
    TEST("\"abc\" busca \"abc\"  = 0",
         find_in_string("abc", "abc") == 0,
         "obtenido %d", find_in_string("abc", "abc"));
    TEST("\"abc\" busca \"abcd\" = -1",
         find_in_string("abc", "abcd") == -1,
         "obtenido %d", find_in_string("abc", "abcd"));
    TEST("\"aababc\" busca \"ab\" = 1",
         find_in_string("aababc", "ab") == 1,
         "obtenido %d", find_in_string("aababc", "ab"));
}

/* ═══════════════════════════════════════════════════════════════════
 * 12. string_to_caps / string_to_min
 * ═══════════════════════════════════════════════════════════════════ */
void test_string_case(void) {
    SECTION("string_to_caps / string_to_min");

    char s1[] = "hola Mundo 123";
    string_to_caps(s1);
    TEST("string_to_caps \"hola Mundo 123\" = \"HOLA MUNDO 123\"",
         strcmp(s1, "HOLA MUNDO 123") == 0, "obtenido \"%s\"", s1);

    char s2[] = "HOLA Mundo 123";
    string_to_min(s2);
    TEST("string_to_min \"HOLA Mundo 123\" = \"hola mundo 123\"",
         strcmp(s2, "hola mundo 123") == 0, "obtenido \"%s\"", s2);

    /* Ya en mayúsculas → sin cambio */
    char s3[] = "HELLO";
    string_to_caps(s3);
    TEST("string_to_caps ya en mayúsculas → sin cambio",
         strcmp(s3, "HELLO") == 0, "obtenido \"%s\"", s3);
}

/* ═══════════════════════════════════════════════════════════════════
 * 13. sum / prod (complex_t)
 * ═══════════════════════════════════════════════════════════════════ */
void test_complex(void) {
    SECTION("sum / prod (complex_t)");

    complex_t a = {3, 2};   /* 3 + 2i */
    complex_t b = {1, -1};  /* 1 - 1i */

    /* (3+2i) + (1-1i) = 4+1i */
    complex_t *s = sum(a, b);
    TEST("sum — no NULL", s != NULL, "retornó NULL");
    if (s) {
        TEST("sum (3+2i)+(1-1i) → real=4",  s->real == 4, "real=%d", s->real);
        TEST("sum (3+2i)+(1-1i) → imag=1",  s->imag == 1, "imag=%d", s->imag);
        free(s);
    }

    /* (3+2i) * (1-1i) = 3-3i+2i-2i² = 5-i */
    complex_t *p = prod(a, b);
    TEST("prod — no NULL", p != NULL, "retornó NULL");
    if (p) {
        TEST("prod (3+2i)*(1-1i) → real=5",  p->real ==  5, "real=%d", p->real);
        TEST("prod (3+2i)*(1-1i) → imag=-1", p->imag == -1, "imag=%d", p->imag);
        free(p);
    }

    /* (0+0i) + (5+3i) = 5+3i */
    complex_t z = {0, 0};
    complex_t c = {5, 3};
    complex_t *s2 = sum(z, c);
    TEST("sum con cero — real=5", s2 && s2->real == 5, "real=%d", s2 ? s2->real : -999);
    TEST("sum con cero — imag=3", s2 && s2->imag == 3, "imag=%d", s2 ? s2->imag : -999);
    free(s2);
}

/* ═══════════════════════════════════════════════════════════════════
 * 14. days_left
 * ═══════════════════════════════════════════════════════════════════ */
void test_days_left(void) {
    SECTION("days_left");

    date_t d1 = {1, 1, 2025};
    date_t d2 = {1, 1, 2026};
    TEST("1/1/2025 → 1/1/2026 = 365",
         days_left(d1, d2) == 365,
         "obtenido %d", days_left(d1, d2));

    /* 2024 es bisiesto → 366 días */
    date_t d3 = {1, 1, 2024};
    date_t d4 = {1, 1, 2025};
    TEST("1/1/2024 → 1/1/2025 = 366 (bisiesto)",
         days_left(d3, d4) == 366,
         "obtenido %d", days_left(d3, d4));

    /* Mismo mes */
    date_t d5 = {1,  3, 2025};
    date_t d6 = {31, 3, 2025};
    TEST("1/3/2025 → 31/3/2025 = 30",
         days_left(d5, d6) == 30,
         "obtenido %d", days_left(d5, d6));

    /* Misma fecha → 0 */
    date_t d7 = {15, 6, 2025};
    TEST("misma fecha → 0",
         days_left(d7, d7) == 0,
         "obtenido %d", days_left(d7, d7));

    /* Cruce de año bisiesto: 28/2/2024 → 1/3/2024 = 2 días (año bisiesto) */
    date_t d8 = {28, 2, 2024};
    date_t d9 = {1,  3, 2024};
    TEST("28/2/2024 → 1/3/2024 = 2 (feb bisiesto tiene 29 días)",
         days_left(d8, d9) == 2,
         "obtenido %d", days_left(d8, d9));
}

/* ═══════════════════════════════════════════════════════════════════
 * 15. matrix_sub
 * ═══════════════════════════════════════════════════════════════════ */
void test_matrix_sub(void) {
    SECTION("matrix_sub");

    /* A = [[5,3],[1,2]]   B = [[1,1],[1,1]]   A-B = [[4,2],[0,1]] */
    int16_t *pa = malloc(4 * sizeof(int16_t));
    int16_t *pb = malloc(4 * sizeof(int16_t));
    pa[0]=5; pa[1]=3; pa[2]=1; pa[3]=2;
    pb[0]=1; pb[1]=1; pb[2]=1; pb[3]=1;

    matriz_t A = {(int16_t **)pa, 2, 2};
    matriz_t B = {(int16_t **)pb, 2, 2};

    matriz_t *R = matrix_sub(A, B);
    TEST("matrix_sub — no NULL", R != NULL, "retornó NULL");
    if (R && R->data) {
        /* Acceso flat o por filas según implementación */
        int16_t *flat = (int16_t *)R->data;
        TEST("matrix_sub [0][0] = 4", flat[0] == 4, "obtenido %d", flat[0]);
        TEST("matrix_sub [0][1] = 2", flat[1] == 2, "obtenido %d", flat[1]);
        TEST("matrix_sub [1][0] = 0", flat[2] == 0, "obtenido %d", flat[2]);
        TEST("matrix_sub [1][1] = 1", flat[3] == 1, "obtenido %d", flat[3]);
        free(R->data);
        free(R);
    }
    free(pa);
    free(pb);
}

/* ═══════════════════════════════════════════════════════════════════
 * Resumen final
 * ═══════════════════════════════════════════════════════════════════ */
int main(void) {
    printf(BOLD "\n╔══════════════════════════════════════════╗\n"
                "║   TESTBENCH — Laboratorio Lenguaje C     ║\n"
                "║            versión 2                     ║\n"
                "╚══════════════════════════════════════════╝\n" RESET);

    test_eq_solver();
    test_bin2dec();
    test_print_reverse_array();
    test_max_min_index();
    test_swap();
    test_consonantes_vocales();
    test_reverse_string();
    test_string_length();
    test_string_words();
    test_string_copy();
    test_find_in_string();
    test_string_case();
    test_complex();
    test_days_left();
    test_matrix_sub();

    printf(BOLD "\n╔══════════════════════════════════════════╗\n" RESET);
    if (tests_failed == 0) {
        printf(BOLD GREEN
               "║  ✓ TODOS LOS TESTS PASARON: %2d / %2d      ║\n"
               RESET, tests_passed, tests_run);
    } else {
        printf(BOLD RED
               "║  ✗ RESULTADO: %2d passed, %2d failed / %2d  ║\n"
               RESET, tests_passed, tests_failed, tests_run);
    }
    printf(BOLD "╚══════════════════════════════════════════╝\n\n" RESET);

    return (tests_failed == 0) ? 0 : 1;
}

