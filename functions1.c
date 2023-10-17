#include "main.h"

/* ====== A FUNCTION FOR PRINTING UNSIGNED NUMBER ======= */
/**
 * unsigned_printer - Prints an unsigned number
 * @list_args: List a of arguments
 * @buffer: Character buffer array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int unsigned_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(list_args, unsigned long int);

	num = unsigned_size_converter(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (unsigned_writer(0, i, buffer, flg, width, precs, size));
}

/* == A FUNCTION TO PRINT UNSIGNED NUMBER IN OCTAL ======== */
/**
 * octal_printer - Prints an unsigned number in octal notation
 * @list_args: Lista of arguments
 * @buffer: Character buffer array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int octal_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{

	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(list_args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = unsigned_size_converter(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flg & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (unsigned_writer(0, i, buffer, flg, width, precs, size));
}

/* ===== PRINT UNSIGNED NUMBER IN HEXADECIMAL ======= */
/**
 * hexa_printer - Prints an unsigned number in hexadecimal notation
 * @list_args: Lista of arguments
 * @buffer: Character buffer array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int hexa_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	return (hexadecimal_printer(list_args, "0123456789abcdef", buffer,
		flg, 'x', width, precs, size));
}

/* ====== A FUNCTION FOR PRINTING UNSIGNED NUMBER IN UPPER HEXA ==== */
/**
 * upper_hexa_printer - Prints an unsigned number in upper hexadecimal notation
 * @list_args: Lista of arguments
 * @buffer: Character buffer array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int upper_hexa_printer(va_list list_args, char buffer[],
	int flg, int width, int precs, int size)
{
	return (hexadecimal_printer(list_args, "0123456789ABCDEF", buffer,
		flg, 'X', width, precs, size));
}

/* ======== A FUNCTION FOR PRINTING HEXA NUM IN LOWER OR UPPER === */
/**
 * hexadecimal_printer - Prints a hexadecimal number in lower or upper
 * @list_args: Lista of arguments
 * @map_to: Array of values to map the number to
 * @flag_ch: Calculates active flg
 * @buffer: Character buffer array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int hexadecimal_printer(va_list list_args, char map_to[], char buffer[],
	int flg, char flag_ch, int width, int precs, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(list_args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = unsigned_size_converter(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flg & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (unsigned_writer(0, i, buffer, flg, width, precs, size));
}
