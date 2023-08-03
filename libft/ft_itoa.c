/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 14:29:36 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2022/11/07 12:32:48 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strmaker(int n, int x, int y)
{
	char	*str;

	str = malloc(sizeof(char) * (x + 1));
	y = 0;
	if (!str)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
		y++;
	}
	str[x] = '\0';
	x--;
	while ((x - y) >= 0)
	{
		str[x] = (n % 10) + '0';
		n /= 10;
		x--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		x;
	int		y;

	x = 0;
	y = n;
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		y = -y;
		x++;
	}
	if (n == 0)
		return (ft_strdup("0"));
	while (y > 0)
	{
		y /= 10;
		x++;
	}
	number = strmaker(n, x, y);
	return (number);
}
