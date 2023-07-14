/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 17:46:59 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2022/10/27 18:15:57 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memo;

	memo = malloc(count * size);
	if (!memo)
		return (0);
	ft_bzero(memo, count * size);
	return (memo);
}
