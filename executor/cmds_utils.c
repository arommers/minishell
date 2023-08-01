/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 17:22:01 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/01 12:45:15 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// gets size of commands list
int	cmds_size(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		cmds = cmds->next;
		i++;
	}
	return (i);
}

// finds last command in list
t_cmd	*find_last_cmd(t_cmd *cmds)
{
	while (cmds)
	{
		if (!cmds->next)
			return (cmds);
		cmds = cmds->next;
	}
	return (NULL);
}
