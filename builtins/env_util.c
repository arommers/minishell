/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_util.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 16:13:46 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/17 18:00:56 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	add_to_env(t_data *data, char *str)
{
	char	*tmp_str;

	tmp_str = ft_strdup(str);
	if (!tmp_str)
		return (print_error(NULL, NULL), 1);
	if (add_lex_node(data->env, 0, tmp_str) == 0)
		return (print_error(NULL, NULL), 1);
	return (0);
}

int	alter_env(t_data *data, char *str, char *var)
{
	t_lexer	*tmp;
	char	*tmp_str;
	int		len;

	len = ft_strlen(var);
	tmp = *(data->env);
	while (tmp)
	{
		if (ft_strncmp(tmp->chars, var, len) == 0 && tmp->chars[len] == '=')
		{
			tmp_str = ft_strdup(str);
			if (!tmp_str)
				return (print_error(NULL, NULL), 1);
			free(tmp->chars);
			tmp->chars = tmp_str;
			return (0);
		}
		tmp = tmp->next;
	}
	return (add_to_env(data, str));
}

// our version of getenv(), searches environment for variable value
char	*ft_getenv(t_data *data, char *var)
{
	t_lexer	*tmp;

	tmp = *(data->env);
	while (tmp)
	{
		if (ft_strncmp(var, tmp->chars, ft_strlen(var)) == 0
			&& tmp->chars[ft_strlen(var)] == '=')
		{
			return (ft_strchr(tmp->chars, '=') + 1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_pwd(void)
{
	char	*buffer;
	char	*pwd;

	buffer = ft_calloc(200, sizeof(char));
	if (!buffer)
		return (print_error(NULL, NULL), NULL);
	buffer = getcwd(buffer, 200);
	if (!buffer)
		return (print_error(NULL, NULL), NULL);
	pwd = ft_strdup(buffer);
	if (!pwd)
		print_error(NULL, NULL);
	free(buffer);
	return (pwd);
}
