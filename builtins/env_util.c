/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_util.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 16:13:46 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/28 15:28:39 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*append_value(char *orig_str, char *new_str, int varlen)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(orig_str, &new_str[varlen + 1]);
	if (!tmp_str)
		print_error(NULL, NULL);
	free(new_str);
	return (tmp_str);
}

// searches environment for variable to replace its value, or adds new variable
// str =	new environment string ("var=value")
// var =	variable of which the value is to be replaced
// isplus =	1 if str was originally of the form "var+=value"
int	alter_env(t_data *data, char *str, char *var, int isplus)
{
	t_lexer	*tmp;

	tmp = *(data->env);
	while (tmp)
	{
		if (ft_strncmp(tmp->chars, var, ft_strlen(var)) == 0
			&& tmp->chars[ft_strlen(var)] == '=')
		{
			if (isplus == 1)
			{
				str = append_value(tmp->chars, str, ft_strlen(var));
				if (!str)
					return (1);
			}
			free(tmp->chars);
			tmp->chars = str;
			return (0);
		}
		tmp = tmp->next;
	}
	if (add_lex_node(data->env, 0, str) == 0)
		return (print_error(NULL, NULL), free(str), 1);
	return (0);
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

// uses getcwd to store current working directory in buffer,
// then uses ft_strdup so all superfluous memory space can be freed
char	*get_pwd(t_data *data)
{
	char	*buffer;
	char	*pwd;

	buffer = ft_calloc(200, sizeof(char));
	if (!buffer)
		return (print_error(NULL, NULL), NULL);
	buffer = getcwd(buffer, 200);
	if (buffer)
		pwd = ft_strdup(buffer);
	else
		pwd = ft_strdup(data->cwd);
	if (!pwd)
		print_error(NULL, NULL);
	if (buffer)
		free(buffer);
	return (pwd);
}
