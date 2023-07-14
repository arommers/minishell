/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 13:22:54 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2022/10/21 17:31:17 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	m;
	int		x;
	int		y;

	n = dstsize;
	m = (size_t) ft_strlen(dst);
	x = 0;
	y = 0;
	while (dst[x] != '\0' && n > 1)
	{
		x++;
		n--;
	}
	if (dst[x] != '\0')
		return (dstsize + (size_t) ft_strlen(src));
	while (src[y] != '\0' && n > 1)
	{
		dst[x] = src[y];
		x++;
		y++;
		n--;
	}
	dst[x] = '\0';
	return ((m + (size_t) ft_strlen(src)));
}
