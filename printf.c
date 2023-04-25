#include <stdio.h>
#include "main.h"


void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: string to be inputed
 * Return: number of chars to be printed.
 */
int _printf(const char *format, ...)
{
	int j, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);
	va_start(list, format);

	int j = 0;

	while (format[j] != '\0')
	{
		if (format[j] != '%')
		{
			buffer[buff_ind++] = format[j];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &j);
			width = get_width(format, &j, list);
			precision = get_precision(format, &j, list);
			size = get_size(format, &j);
			++j;
			printed = handle_print(format, &j, list, buffer,
					flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
		j++;
	}

	print_buffer(buffer, &buff_ind);

	a_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of characters
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
