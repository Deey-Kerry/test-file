#include <stdio.h>
#include "main.h"

/** PRINT UNSIGNED NUMBER */
/**
 * print_unsigned - function that Prints an unsigned number
 * @flags:  Calculates active flags
 * @size: Used to specify the size
 * @precision: specifies the Precision
 * @width: gets the width
 * @buffer: Buffer array that handles print
 * @types: List a of arguments
 * Return: Number of chars to be printed.
 */

int print_unsigned(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	do {
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}	while (num > 0);

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

/** PRINT UNSIGNED NUMBER IN OCTAL FORMAT */
/**
 * print_octal - function that Prints an unsigned number in octal form
 * @precision: Precision specification
 * @size: Size specifier
 * @buffer: Buffer array to handle print
 * @width: get width
 * @types: Lista of arguments
 * @flags:  Calculates active flags
 *
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	do {
		buffer[j--] = (num % 8) + '0';
		num /= 8;
	} while (num > 0);

	if (flags & F_HASH && init_num != 0)
		buffer[j--] = '0';

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

/** PRINT UNSIGNED NUMBER IN HEXADECIMAL FORMAT */
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @precision: Precision specification
 * @flags:  Calculates active flags
 * @buffer: Buffer array to handle print
 * @types: Lista of arguments
 * @size: Size specifier
 * @width: get width
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}
/** PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL */
/**
 * print_hexa_upper - function that Prints an unsigned no in upper hexadecimal
 * @size: Size specifier
 * @flags:  Calculates active flags
 * @buffer: Buffer array to handle print
 * @precision: Precision specification
 * @types: Lista of arguments
 * @width: get width
 *
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}
/**PRINT HEXADECIMAL NUMBERS IN LOWER OR UPPER CASE FORMAT */
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @size: Size specifier
 * @precision: Precision specification
 * @map_to: Array of values to map the number to
 * @flags:  Calculates active flags
 * @buffer: Buffer array to handle print
 * @width: get width
 * @types: List of arguments to be passsed
 * @flag_ch: Calculates active flags
 *
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
		int flags, char flag_ch, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	/* LOOP that Count the number of hexadecimal digits */
	int num_digits = 0;
	unsigned long int temp = num;

	while (temp > 0)
	{
		num_digits++;
		temp /= 16;
	}
	/* loop that Iterate over the digits in reverse order */
	for (int j = num_digits - 1; j >= 0; j--)
	{
		buffer[j--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[j--] = flag_ch;
		buffer[j--] = '0';
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}
