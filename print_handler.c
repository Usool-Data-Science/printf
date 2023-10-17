#include "main.h"
/**
 * print_handler - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @args_list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precs: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int print_handler(const char *fmt, int *ind, va_list args_list, char buffer[],
	int flags, int width, int precs, int size)
{
	int i, unknow_len = 0, printed_chars = -1;

	fmt_t fmt_types[] = {{'c', char_printer}, {'s', string_printer}, {'%', percent_printer}, {'i', int_printer}, {'d', int_printer}, {'b', binary_printer}, {'u', unsigned_printer}, {'o', octal_printer}, {'x', hexa_printer}, {'X', upper_hexa_printer}, {'p', pointer_printer}, {'S', non_printable_printer}, {'r', reverse_printer}, {'R', rot13string_printer}, {'\0', NULL}};

	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(args_list, buffer, flags, width, precs, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
