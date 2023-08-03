/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 13:23:42 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/30 14:53:43 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(char *src)
{
	int		x;
	char	*des;

	des = malloc(sizeof(char) * (ft_strlen(src) + 1));
	x = 0;
	if (!des)
		return (0);
	while (src[x] != '\0')
	{
		des[x] = src[x];
		x++;
	}
	des[x] = '\0';
	return (des);
}
