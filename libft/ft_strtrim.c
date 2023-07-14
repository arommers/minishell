/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:32:14 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2022/10/24 16:44:54 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	startfinder(char const *s1, char const *set, int i)
{
	int	x;

	x = 0;
	while (s1[x] != '\0' && set[i] != '\0')
	{
		i = 0;
		while (set[i] != '\0')
		{
			if (s1[x] == set[i])
				break ;
			i++;
		}
		x++;
	}
	if (s1[x] == '\0')
		return (0);
	return (x - 1);
}

static int	endfinder(char const *s1, char const *set, int i)
{
	int	y;

	y = ft_strlen(s1);
	if (y == 0)
		return (0);
	while (y >= 0 && set[i] != '\0')
	{
		i = 0;
		while (set[i] != '\0')
		{
			if (s1[y - 1] == set[i])
				break ;
			i++;
		}
		y--;
	}
	return (y + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = startfinder(s1, set, i);
	y = endfinder(s1, set, i);
	if (*s1 == '\0')
		return (ft_strdup(""));
	if (*set == '\0')
		return (ft_strdup((char *) s1));
	if (y - x >= 0)
		return (ft_substr(s1, x, y - x));
	return (0);
}
