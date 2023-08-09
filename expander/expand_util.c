/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_util.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/24 15:07:25 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/09 15:38:55 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*free_chrarray(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

// takes temporary array and joins it in new string
char	*join_new_str(char **tmp_array)
{
	char	*tmp_str;
	char	*new_str;
	int		i;

	new_str = NULL;
	i = 0;
	while (tmp_array[i])
	{
		tmp_str = ft_strjoin(new_str, tmp_array[i]);
		if (!tmp_str)
		{
			if (new_str)
				free(new_str);
			return (free_chrarray(tmp_array));
		}
		free(new_str);
		new_str = tmp_str;
		i++;
	}
	free_chrarray(tmp_array);
	return (new_str);
}

// loops through cmd_argv and expands each string
int	expand_cmd(char **cmd_argv)
{
	int		i;

	if (!cmd_argv)
		return (0);
	i = 0;
	while (cmd_argv[i])
	{
		if (quote_strchr(cmd_argv[i]) || ft_strchr(cmd_argv[i], '$'))
		{
			cmd_argv[i] = expand_str(cmd_argv[i], 0);
			if (!cmd_argv[i])
				return (1);
		}
		i++;
	}
	return (0);
}
