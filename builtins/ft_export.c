/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 16:00:55 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/23 15:28:28 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// returns if variable has no new value, otherwise alters environment
static int	export_var(t_data *data, char *str, char *var)
{
	char	*tmp_str;

	if (!ft_strchr(str, '='))
		return (0);
	tmp_str = ft_strdup(str);
	if (!tmp_str)
		return (print_error(NULL, NULL), 1);
	return (alter_env(data, tmp_str, var));
}

// checks if the variable consists only of valid variable chars
static int	check_var(char *var)
{
	int	i;

	if (!var[0] || ft_isdigit(var[0]))
		return (builtin_error("export", var, NULL), 1);
	i = 0;
	while (var[i])
	{
		if (isvarchr(&var[i], 0) == 0)
			return (builtin_error("export", var, NULL), 1);
		i++;
	}
	return (0);
}

// looks for the variable part of the string and returns it
static char	*find_var(char *str)
{
	char	*var;
	int		len;

	if (!str[0] || ft_isdigit(str[0]) || str[0] == '=' || !ft_strchr(str, '='))
		var = ft_strdup(str);
	else
	{
		len = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
		var = ft_substr(str, 0, len);
	}
	if (!var)
		return (print_error(NULL, NULL), NULL);
	return (var);
}

// loops through the arguments, takes the variable from each argument, 
// checks it, changes exit stat if there is an error, exports it if not
int	ft_export(t_data *data, t_cmd *cmd)
{
	char	*var;
	int		exit_stat;
	int		ret;
	int		i;

	if (!cmd->args[1])
		return (ft_env(data, cmd));
	exit_stat = 0;
	i = 1;
	while (cmd->args[i])
	{
		var = find_var(cmd->args[i]);
		if (!var)
			return (1);
		ret = check_var(var);
		if (ret == 1)
			exit_stat = ret;
		if (ret == 0 && export_var(data, cmd->args[i], var) == 1)
			return (free(var), 1);
		free(var);
		i++;
	}
	return (exit_stat);
}
