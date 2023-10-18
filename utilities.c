#include "main.h"

/**
 * is_printable - Check printability of a character
 * @c: Character to be evaluated.
 *
 * Return: 1 mean Character is printable, 0 means not printable
 */
int is_printable(char c)
{
	if (c >= 32 && c <= 126)
	{
		return (1);
	}

	return (0);
}

/**
 * hexa_appender - A function to ppend ascii in hexadecimal code to buffer
 * @buffer: The array of characters.
 * @i: Start point for appending.
 * @ascii: ASCII CODE.
 * Return: Always 3
 */
int hexa_appender(char ascii, char buffer[], int i)
{
	char to_map[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii < 0)
		ascii *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = to_map[ascii / 16];
	buffer[i] = to_map[ascii % 16];

	return (3);
}

/**
 * is_numeric - A function that checks if a char is a digit
 * @c: The character to be evaluated
 *
 * Return: 1 means that C is a digit, 0 means that it is not
 */
int is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * num_size_converter - A function to typecasts a num to specified size
 * @num: The num specified for casting.
 * @size: Casting Size.
 *
 * Return: Casting Result.
 */
long int num_size_converter(long int num, int size)
{
	if (size == SIZE_LONG)
		return (num);
	else if (size == SIZE_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * unsigned_size_converter - Casts a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int unsigned_size_converter(unsigned long int num, int size)
{
	if (size == SIZE_LONG)
		return (num);
	else if (size == SIZE_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
