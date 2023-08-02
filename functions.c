#include "main.h"

/**
 * print_char - prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: digit of chars printed
 */
int print_char(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        char c = va_arg(types, int);

        return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string - prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: digit of chars printed
 */
int print_string(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        int length = 0, f;
        char *str = va_arg(types, char *);

        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);
        if (str == NULL)
        {
                str = "(null)";
                if (precision >= 6)
                        str = "      ";
        }

        while (str[length] != '\0')
                length++;

        if (precision >= 0 && precision < length)
                length = precision;

        if (width > length)
        {
                if (flags & F_MINUS)
                {
                        write(1, &str[0], length);
                        for (f = width - length; f > 0; f--)
                                write(1, " ", 1);
                        return (width);
                }
                else
                {
                        for (f = width - length; f > 0; f--)
                                write(1, " ", 1);
                        write(1, &str[0], length);
                        return (width);
                }
        }

        return (write(1, str, length));
}

/**
 * print_percent - prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: digits of chars printed
 */
int print_percent(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        UNUSED(types);
        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);
        return (write(1, "%%", 1));
}

/**
 * print_int - print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: digits of chars printed
 */
int print_int(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        int f = BUFF_SIZE - 2;
        int is_negative = 0;
        long int j = va_arg(types, long int);
        unsigned long int num;

        n = convert_size_number(j, size);

        if (j == 0)
                buffer[f--] = '0';

        buffer[BUFF_SIZE - 1] = '\0';
        num = (unsigned long int)j;

        if (j < 0)
        {
                num = (unsigned long int)((-1) * j);
                is_negative = 1;
        }

        while (num > 0)
        {
                buffer[f--] = (num % 10) + '0';
                num /= 10;
        }

        f++;

        return (write_number(is_negative, f, buffer, flags, width, precision, size));
}
/**
 * print_binary - prints an unsigned digit
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: digits of char printed.
 */
int print_binary(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        unsigned int j, m, f, sum;
        unsigned int a[32];
        int count;

        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);

        n = va_arg(types, unsigned int);
        m = 2147483648; /* (2 ^ 31) */
        a[0] = j / m;
        for (f = 1; f < 32; f++)
        {
                m /= 2;
                a[f] = (j / m) % 2;
        }
        for (f = 0, sum = 0, count = 0; f < 32; f++)
        {
                sum += a[f];
                if (sum || f == 31)
                {
                        char z = '0' + a[f];

                        write(1, &z, 1);
                        count++;
                }
        }
        return (count);
}
  
