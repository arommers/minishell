/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:16:16 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2022/10/25 12:10:52 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ndllen;
	size_t	x;

	ndllen = ft_strlen(needle);
	x = 0;
	if (needle[x] == '\0')
		return (((char *) haystack));
	while (haystack[x] != '\0' && x + ndllen <= len)
	{
		if (ft_strncmp(&haystack[x], needle, ndllen) == 0)
			return (&((char *)haystack)[x]);
		x++;
	}
	return (0);
}
