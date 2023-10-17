#include "main.h"

/**
 * flag_getter - A function to determine which formatting flg are active
 * @format: The formatted string in which arguments are printed
 * @i: The current position in the format string
 * Return: The active flg
 */
int flag_getter(const char *format, int *i)
{
    /* Flags: '-' '+' '0' '#' ' ' */
    /* Corresponding values: 1 2 4 8 16 */
    int j, curr_i;
    int flg = 0;
    const char CHARACTER_FLAGS[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_VALUES[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
    {
        for (j = 0; CHARACTER_FLAGS[j] != '\0'; j++)
        {
            if (format[curr_i] == CHARACTER_FLAGS[j])
            {
                flg |= FLAGS_VALUES[j];
                break;
            }
        }

        if (CHARACTER_FLAGS[j] == 0)
            break;
    }

    *i = curr_i - 1;

    return flg;
}
