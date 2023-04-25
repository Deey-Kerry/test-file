#include <stdio.h>
#include "main.h"
/**
 * get_flags - function that Calculates active flags.
 * @x: take a parameter.
 * @format: Formatted string in which to print the arguments
 * Return: Flags:
 */
int get_flags(const char *format, int *x)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int a, curr_x;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	curr_x = *x + 1;
	while (format[curr_x] != '\0')
	{
		for (a = 0; FLAGS_CH[a] != '\0'; a++)
		{
			if (format[curr_x] == FLAGS_CH[a])
			{
				flags |= FLAGS_ARR[a];
				break;
			}
		}
		if (FLAGS_CH[a] == '\0')
			break;

		curr_x++;
	}

	*x = curr_x - 1;

	return (flags);
}
