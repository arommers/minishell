/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 17:57:55 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2022/10/25 12:10:11 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*test;
	int		i;

	test = malloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	if (!test)
		return (0);
	while (s[i] != '\0')
	{
		test[i] = f(i, s[i]);
		i++;
	}
	test[i] = '\0';
	return (test);
}
