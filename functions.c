#include "main.h"
/* ========== CHARACTER PRINTER FUNCTION ============ */
/**
 * char_printer - A function that prints characters
 * @list_args: The full list of all arguments
 * @buffer: Character buffer array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int char_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	char c = va_arg(list_args, int);

	return (write_char_handler(c, buffer, flg, width, precs, size));
}
/* ====== A function for printing a string ======== */
/**
 * string_printer - Function to print string.
 * @list_args: Complete list of all arguments
 * @buffer: Character buffer array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int string_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	int len = 0, i;
	char *str = va_arg(list_args, char *);

	UNUSED(buffer), UNUSED(flg), UNUSED(width), UNUSED(precs);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precs >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precs >= 0 && precs < len)
		len = precs;

	if (width > len)
	{
		if (flg & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * percent_printer - Prints a percent sign
 * @list_args: Lista of arguments
 * @flg:  Compute active flg
 * @buffer: Character buffer array to temporarily store chars.
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int percent_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	UNUSED(list_args);
	UNUSED(buffer);
	UNUSED(flg);
	UNUSED(width);
	UNUSED(precs);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * int_printer - Print int
 * @list_args: Lista of arguments
 * @buffer: Character buffer array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int int_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	int i = BUFFER_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(list_args, long int);
	unsigned long int num;

	n = num_size_converter(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (number_writer(is_negative, i, buffer, flg, width, precs, size));
}

/************************* PRINT BINARY *************************/
/**
 * binary_printer - Prints an unsigned number
 * @list_args: Lista of arguments
 * @buffer: Character buffer array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int binary_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flg);
	UNUSED(width);
	UNUSED(precs);
	UNUSED(size);

	n = va_arg(list_args, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
