/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 18:49:46 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2022/10/24 12:12:45 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	x;
	unsigned char	y;

	if (n == 0)
		return (0);
	i = 0;
	while (((char *) s1)[i] == ((char *) s2)[i] && i < n - 1)
		i++;
	x = ((unsigned char *)s1)[i];
	y = ((unsigned char *)s2)[i];
	i = x - y;
	return ((int) i);
}
