/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/24 15:07:25 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/01 12:19:53 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static void	free_array(char **tmp_array)
{
	int	i;

	i = 0;
	while (tmp_array[i])
	{
		free(tmp_array[i]);
		i++;
	}
	free(tmp_array);
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
			exit_error(NULL, NULL, 1);
		free(new_str);
		new_str = tmp_str;
		i++;
	}
	free_array(tmp_array);
	return (new_str);
}

// loops through cmd_argv and expands each string
void	expand_cmd(char **cmd_argv)
{
	int		i;

	if (!cmd_argv)
		return ;
	i = 0;
	while (cmd_argv[i])
	{
		if (quote_strchr(cmd_argv[i]) || ft_strchr(cmd_argv[i], '$'))
			cmd_argv[i] = expand_str(cmd_argv[i], 0);
		i++;
	}
}
