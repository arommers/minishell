/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   va_makers.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 14:21:39 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/04/18 20:43:32 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	u_maker(int fd, char chr, long n, int i)
{
	unsigned int	u;

	if (n < 0)
	{
		n = -n;
		u = (2147483648 - n) * 2 + n;
		if (chr == 'x' || chr == 'X')
			return (x_printer(fd, chr, u, i));
		n = u;
	}
	i = int_printer(fd, n, i);
	return (i);
}

int	p_maker(int fd, va_list ap, int i)
{
	void	*p;
	int		w;

	p = va_arg(ap, void *);
	w = write(fd, "0x", 2);
	if (w == -1)
		return (-1);
	i += 2;
	if (p < 0)
		return (u_maker(fd, 'x', (long) p, i));
	return (x_printer(fd, 0, (unsigned long) p, i));
}
