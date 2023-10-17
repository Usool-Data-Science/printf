#include "main.h"

/**
 * prcs_getter - Calculates the prcs for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @arg_lists: arg_lists of arguments.
 *
 * Return: Precision.
 */
int prcs_getter(const char *format, int *i, va_arg_lists arg_lists)
{
	int curr_i = *i + 1;
	int prcs = -1;

	if (format[curr_i] != '.')
		return (prcs);

	prcs = 0;

	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			prcs *= 10;
			prcs += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			prcs = va_arg(arg_lists, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (prcs);
}
