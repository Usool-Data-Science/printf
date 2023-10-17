#include "main.h"

/* === A FUNCTION THAT PRINTS POINTER ========= */
/**
 * pointer_printer - Prints the value of a pointer variable
 * @list_args: List a of arguments
 * @buffer: Buffer array to handle print
 * @flg:  Calculates active flg
 * @width: get width
 * @precs: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int pointer_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, len = 2, padd_start = 1; /* len=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(list_args, void *);

	UNUSED(width), UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precs);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		len++;
	}

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padd = '0';
	if (flg & F_PLUS)
		extra_c = '+', len++;
	else if (flg & F_SPACE)
		extra_c = ' ', len++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (pointer_writer(buffer, ind, len,
		width, flg, padd, extra_c, padd_start));
}

/* === A FUNCTION THAT PRINTS NON PRINTABLE =========== */
/**
 * non_printable_printer - Prints ascii codes in hexa of non printable chars
 * @list_args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flg:  Calculates active flg
 * @width: get width
 * @precs: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int non_printable_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(list_args, char *);

	UNUSED(flg);
	UNUSED(width);
	UNUSED(precs);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/* === A FUNCTION THAT PRINTS IN REVERSE ======== */
/**
 * print_reverse - Prints reverse string.
 * @list_args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flg:  Calculates active flg
 * @width: get width
 * @precs: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flg);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(list_args, char *);

	if (str == NULL)
	{
		UNUSED(precs);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/* ===== PRINT A STRING IN ROT13 ======= */
/**
 * rot13string_printer - Print a string in rot13.
 * @list_args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flg:  Calculates active flg
 * @width: get width
 * @precs: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int rot13string_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(list_args, char *);
	UNUSED(buffer);
	UNUSED(flg);
	UNUSED(width);
	UNUSED(precs);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
