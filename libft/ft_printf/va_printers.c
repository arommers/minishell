/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   va_printers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 14:27:17 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/04/18 20:44:47 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	s_printer(int fd, char *s, int i)
{
	int	w;

	if (s == 0)
	{
		w = write(fd, "(null)", 6);
		if (w == -1)
			return (-1);
		return (i + 6);
	}
	while (*s)
	{
		w = write(fd, s, 1);
		if (w == -1)
			return (-1);
		i++;
		s++;
	}
	return (i);
}

int	int_printer(int fd, long n, int i)
{
	char	c;

	c = 0;
	i++;
	if (n > 9)
	{
		i = int_printer(fd, n / 10, i);
		if (i == -1)
			return (-1);
		i = int_printer(fd, n % 10, i - 1);
	}
	if (n < 0)
	{
		c = write(fd, "-", 1);
		if (c == -1)
			return (-1);
		i = int_printer(fd, -n, i);
	}
	if (n >= 0 && n <= 9)
		c = n + 48;
	if (c >= 48)
		c = (char) write(fd, &c, 1);
	if (c == -1)
		return (-1);
	return (i);
}

int	x_printer(int fd, char chr, unsigned long x, int i)
{
	char	c;

	c = 0;
	i++;
	if (x >= 16)
	{
		i = x_printer(fd, chr, x / 16, i);
		if (i == -1)
			return (-1);
		i = x_printer(fd, chr, x % 16, i - 1);
	}
	if (x > 9 && x < 16)
	{
		if (chr == 'X')
			c = x + 55;
		else
			c = x + 87;
	}
	if (x <= 9)
		c = x + 48;
	if (c != 0)
		c = (char) write(fd, &c, 1);
	if (c == -1)
		return (-1);
	return (i);
}
