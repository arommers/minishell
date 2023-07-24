/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 14:53:00 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/24 17:42:10 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	count_parts(char *str, char c)
{
	int		i;
	int		parts;

	i = 0;
	parts = 0;
	while (str[i])
	{
		if (isquote(str[i]))
		{
			if (i != 0 && str[i - 1] != c)
				parts++;
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
			parts++;
		}
		if (str[i])
			i++;
	}
	if (str[i - 1] != c)
		parts++;
	return (parts);
}

static char	**make_tmp_array(char *str, char c, char **tmp_array)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[i])
	{
		c = '\0';
		k = 0;
		if (isquote(str[i]))
		{
			c = str[i];
			k = 1;
		}
		tmp_array[j] = ft_substr(str, i + k, len_till_quote(&str[i + k], c));
		if (!tmp_array[j])
			exit_error(NULL, NULL, 1);
		j++;
		i += len_till_quote(&str[i + k], c) + k * 2;
	}
	tmp_array[j] = NULL;
	return (tmp_array);
}

static char	*join_new_str(char **tmp_array)
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
	return (new_str);
}

// only removes quotes
char	*expand_heredoc_str(char *str)
{
	char	**tmp_array;
	char	*new_str;
	char	c;
	int		parts;

	c = '\0';
	parts = count_parts(str, c);
	tmp_array = ft_calloc(parts + 1, sizeof(char *));
	if (!tmp_array)
		exit_error(NULL, NULL, 1);
	tmp_array = make_tmp_array(str, c, tmp_array);
	new_str = join_new_str(tmp_array);
	return (new_str);
}

// only expands env variables
char	*expand_heredoc_input(char *str)
{
	return (str);
}

// removes quotes and expands env variables
char	*expand_str(char *str)
{
	return (str);
}

// loops through cmd_argv and expands each string
void	expand_cmd(char **cmd_argv)
{
	char	*tmp_str;
	int		i;

	i = 0;
	while (cmd_argv[i])
	{
		if (quote_strchr(cmd_argv[i]) || ft_strchr(cmd_argv[i], '$'))
		{
			tmp_str = expand_str(cmd_argv[i]);
			free(cmd_argv[i]);
			cmd_argv[i] = tmp_str;
		}
		i++;
	}
}
