/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_util.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 17:11:19 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/16 14:54:59 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// checks if char is a letter, digit or underscore
int	isvarchr(char *str, int i)
{
	if (isalnum(str[i]) == 1 || str[i] == '_')
		return (1);
	if (i != 0 && str[i - 1] == '$' && str[i] == '?')
		return (1);
	return (0);
}

// counts len of string till the next variable
int	len_till_var(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] && !(str[i + j] == '$' && isvarchr(str, i + j + 1)))
		j++;
	return (j);
}

// counts len of variable in string
int	len_of_var(char *str, int i)
{
	int	j;

	j = 1;
	while (isvarchr(str, i + j))
		j++;
	return (j);
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
