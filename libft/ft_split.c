/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 14:37:55 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/09 17:25:09 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	counter(char const *s, char c)
{
	size_t	count;
	int		i;

	count = 1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	if (s[0] != c && s[0] != '\0')
		count++;
	return (count);
}

static char	**freedomgiver(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

static char	**strender(char **lilstrs, char const *s, char c, int y)
{
	if (!ft_strchr(s, c) && s[0] != '\0')
	{
		lilstrs[0] = ft_strdup((char *) s);
		if (!lilstrs[0])
			return (freedomgiver(lilstrs));
		y = 1;
	}
	lilstrs[y] = 0;
	return (lilstrs);
}

static char	**strmaker(char **lilstrs, char const *s, char c, int y)
{
	int	x;

	x = 0;
	while (s[x] != '\0' || (c == '\0' && s[x]))
	{
		if (s[x] == c)
		{
			while (s[x] == c)
				x++;
			if (s[x] == '\0')
				return (strender(lilstrs, s, c, y));
			if (ft_strchr(&s[x], c))
			{
				lilstrs[y] = ft_substr(s, x, ft_strlen(&s[x])
						- ft_strlen(ft_strchr(&s[x], c)));
			}
			else
				lilstrs[y] = ft_substr(s, x, ft_strlen(&s[x]));
			if (!lilstrs[y])
				return (freedomgiver(lilstrs));
			y++;
		}
		x++;
	}
	return (strender(lilstrs, s, c, y));
}

char	**ft_split(char const *s, char c)
{
	char	**lilstrs;
	int		y;

	lilstrs = malloc(sizeof(char *) * counter(s, c));
	if (!lilstrs)
		return (0);
	y = 0;
	if (!ft_strchr(s, c))
		return (strender(lilstrs, s, c, y));
	if (s[0] != c)
	{
		lilstrs[0] = ft_substr(s, 0, ft_strlen(s) - ft_strlen(ft_strchr(s, c)));
		if (!lilstrs[0])
			return (freedomgiver(lilstrs));
		y++;
	}
	return (strmaker(lilstrs, s, c, y));
}
