/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 12:18:52 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/03/28 17:43:33 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*bigstr;
	int		x;
	int		y;

	if (!s1)
		return (ft_strdup((char *) s2));
	if (!s2)
		return (ft_strdup((char *) s1));
	bigstr = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!bigstr)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[x] != '\0')
	{
		bigstr[x] = s1[x];
		x++;
	}
	while (s2[y] != '\0')
	{
		bigstr[x + y] = s2[y];
		y++;
	}
	bigstr[x + y] = '\0';
	return (bigstr);
}
