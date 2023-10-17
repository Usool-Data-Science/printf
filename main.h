#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFFER_SIZE 1024

/* FLAGS */
#define F_SPACE 16
#define F_HASH 8
#define F_ZERO 4
#define F_PLUS 2
#define F_MINUS 1

/* SIZES */
#define SIZE_SHORT 1
#define SIZE_LONG 2

/**
 * struct fmt - Struct operator
 *
 * @fmt: The format specifier.
 * @fn: The associated function.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct operator
 *
 * @fmt: The format specifier.
 * @fm_t: The associated function.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int print_handler(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

int upper_hexa_printer(va_list list_args, char buffer[], int flg, int width, int precs, int size);
/*================= FUNCTIONS ===================================*/

/* Funtions to print chars and strings */
int char_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int string_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int percent_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Functions to print numbers */
int int_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int binary_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int unsigned_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int octal_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int hexa_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int hexa_upper_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int hexadecimal_printer(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Function to print non printable characters */
int non_printable_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Funcion to print memory address */
int pointer_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Funciotns to handle other specifiers */
int flag_getter(const char *format, int *i);
int width_getter(const char *format, int *i, va_list list);
int precision_getter(const char *format, int *i, va_list list);
int size_getter(const char *format, int *i);

/* ============== Function to print string in reverse ================= */
int reverse_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* ================ Function to print a string in rot 13 =========== */
int rot13string_printer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* =================== width handler ========================== */
int write_char_handler(char c, char buffer[],
	int flags, int width, int precision, int size);
int number_writer(int is_positive, int ind, char buffer[],
	int flags, int width, int precision, int size);
int num_writer(int ind, char bff[], int flags, int width, int precision,
	int length, char padd, char extra_c);
int pointer_writer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start);

int unsigned_writer(int is_negative, int ind,
char buffer[],
	int flags, int width, int precision, int size);

/*==================== UTILS ==============================**/
int is_printable(char);
int hexa_appender(char, char[], int);
int is_digit(char);

long int num_size_converter(long int num, int size);
long int unsigned_size_converter(unsigned long int num, int size);

#endif /* MAIN_H */

