/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 12:24:04 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2022/10/25 14:38:08 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*lilstr;
	size_t	memsize;
	size_t	x;

	if (start >= (unsigned int) ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (len > (size_t) ft_strlen(s))
		len = ft_strlen(s) - start;
	memsize = len + 1;
	if (start + len > (size_t) ft_strlen(s))
		memsize--;
	lilstr = malloc(sizeof(char) * memsize);
	if (!lilstr)
		return (0);
	x = 0;
	while (x < len)
	{
		lilstr[x] = s[start];
		x++;
		start++;
	}
	if (lilstr[x - 1] != '\0')
		lilstr[x] = '\0';
	return (lilstr);
}
