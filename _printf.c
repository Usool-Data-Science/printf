#include "main.h"
/**
 * buffer_printer - Prints the contents of the buffer if it exist
 * @buffer: The array of chars to add to buffer.
 * @buff_ind: Starting index for next character.
 */
void buffer_printer(char buffer[], int *buff_ind)
{
	if (*buff_ind)
		write(1, &buffer[0], *buff_ind);
	*buff_ind = 0;
}
/**
 * _printf - A clone of printf function
 * @format: The format to print.
 * Return: The characters to print.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list arg_list;
	char buffer[BUFFER_SIZE];

	if (format == NULL || !format)
		return (-1);
	va_start(arg_list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFFER_SIZE)
				buffer_printer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			buffer_printer(buffer, &buff_ind);
			flags = flag_getter(format, &i);
			width = width_getter(format, &i, arg_list);
			precision = precision_getter(format, &i, arg_list);
			size = size_getter(format, &i), ++i;
			printed = print_handler(format, &i, arg_list, buffer,
				flags, width, precision, size);
			if (printed == -1)
			{
				return (-1);
			}
			printed_chars += printed;
		}
	}
	buffer_printer(buffer, &buff_ind), va_end(arg_list);
	return (printed_chars);
}
