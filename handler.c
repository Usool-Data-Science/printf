#include "main.h"

/* ====== A FUNCTION TO WRITE HANDLER ======= */
/**
 * write_char_handler - A function for printing string
 * @c: char types.
 * @buff: Character buff array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int write_char_handler(char c, char buff[],
	int flg, int width, int precs, int size)
{
	int i = 0;
	char padding = ' ';

	UNUSED(precs), UNUSED(size);

	if (flg & F_ZERO)
		padding = '0';

	buff[i++] = c;
	buff[i] = '\0';

	if (width > 1)
	{
		buff[BUFFER_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buff[BUFFER_SIZE - i - 2] = padding;

		if (flg & F_MINUS)
			return (write(1, &buff[0], 1) +
					write(1, &buff[BUFFER_SIZE - i - 1], width - 1));
		else
			return (write(1, &buff[BUFFER_SIZE - i - 1], width - 1) +
					write(1, &buff[0], 1));
	}

	return (write(1, &buff[0], 1));
}

/* ======== A FUNCTION TO WRITE NUMBER ========= */
/**
 * number_writer - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buff: Character buff array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int number_writer(int is_negative, int ind, char buff[],
	int flg, int width, int precs, int size)
{
	int len = BUFFER_SIZE - ind - 1;
	char padding = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padding = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flg & F_PLUS)
		extra_ch = '+';
	else if (flg & F_SPACE)
		extra_ch = ' ';

	return (num_writer(ind, buff, flg, width, precs,
		len, padding, extra_ch));
}

/**
 * num_writer - Write a number using a bufffer
 * @ind: Index at which the number starts on the buff
 * @buff: Character buff array to temporarily store chars.
 * @flg:  Compute active flg
 * @len: Length
 * @width: Measurement of Width
 * @prec: Specifier for precs.
 * @padding: Specifier for padding size.
 * @extra_c: Specifier for extra character.
 * Return: The total number of chars printed.
 */
int num_writer(int ind, char buff[],
	int flg, int width, int prec,
	int len, char padding, char extra_c)
{
	int i, padding_start = 1;

	if (prec == 0 && ind == BUFFER_SIZE - 2 && buff[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFFER_SIZE - 2 && buff[ind] == '0')
		buff[ind] = padding = ' ';
	if (prec > 0 && prec < len)
		padding = ' ';
	while (prec > len)
		buff[--ind] = '0', len++;
	if (extra_c != 0)
		len++;
	if (width > len)
	{
		for (i = 1; i < width - len + 1; i++)
			buff[i] = padding;
		buff[i] = '\0';
		if (flg & F_MINUS && padding == ' ')
		{
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[ind], len) + write(1, &buff[1], i - 1));
		}
		else if (!(flg & F_MINUS) && padding == ' ')
		{
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[1], i - 1) + write(1, &buff[ind], len));
		}
		else if (!(flg & F_MINUS) && padding == '0')
		{
			if (extra_c)
				buff[--padding_start] = extra_c;
			return (write(1, &buff[padding_start], i - padding_start) +
				write(1, &buff[ind], len - (1 - padding_start)));
		}
	}
	if (extra_c)
		buff[--ind] = extra_c;
	return (write(1, &buff[ind], len));
}

/**
 * unsigned_writer - A function that writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buff
 * @buff: Character buff array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @precs: Specifier for precs.
 * @size: Specifier for size.
 * Return: The total number of chars printed
 */
int unsigned_writer(int is_negative, int ind,
	char buff[],
	int flg, int width, int precs, int size)
{
	int len = BUFFER_SIZE - ind - 1, i = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precs == 0 && ind == BUFFER_SIZE - 2 && buff[ind] == '0')
		return (0);

	if (precs > 0 && precs < len)
		padding = ' ';

	while (precs > len)
	{
		buff[--ind] = '0';
		len++;
	}

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padding = '0';

	if (width > len)
	{
		for (i = 0; i < width - len; i++)
			buff[i] = padding;

		buff[i] = '\0';

		if (flg & F_MINUS)
		{
			return (write(1, &buff[ind], len) + write(1, &buff[0], i));
		}
		else
		{
			return (write(1, &buff[0], i) + write(1, &buff[ind], len));
		}
	}

	return (write(1, &buff[ind], len));
}

/**
 * pointer_writer - A function to write memory address
 * @padding: Char representing the paddinging
 * @extra_c: Char representing extra char
 * @padding_start: Index at which paddinging should start
 * @buff: Character buff array to temporarily store chars.
 * @flg:  Compute active flg
 * @width: Measurement of Width
 * @ind: Specifier for index.
 * @len: Length
 * Return: The total number of chars printed
 */
int pointer_writer(char buff[], int ind, int len,
	int width, int flg, char padding, char extra_c, int padding_start)
{
	int i;

	if (width > len)
	{
		for (i = 3; i < width - len + 3; i++)
			buff[i] = padding;
		buff[i] = '\0';
		if (flg & F_MINUS && padding == ' ')
		{
			buff[--ind] = 'x';
			buff[--ind] = '0';
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[ind], len) + write(1, &buff[3], i - 3));
		}
		else if (!(flg & F_MINUS) && padding == ' ')
		{
			buff[--ind] = 'x';
			buff[--ind] = '0';
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[3], i - 3) + write(1, &buff[ind], len));
		}
		else if (!(flg & F_MINUS) && padding == '0')
		{
			if (extra_c)
				buff[--padding_start] = extra_c;
			buff[1] = '0';
			buff[2] = 'x';
			return (write(1, &buff[padding_start], i - padding_start) +
				write(1, &buff[ind], len - (1 - padding_start) - 2));
		}
	}
	buff[--ind] = 'x';
	buff[--ind] = '0';
	if (extra_c)
		buff[--ind] = extra_c;
	return (write(1, &buff[ind], BUFFER_SIZE - ind - 1));
}
