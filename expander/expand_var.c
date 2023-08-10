/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_var.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 16:06:34 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/10 16:26:22 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// counts size of array by counting variables + parts inbetween
static int	count_parts(char *str, int parts)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == '$' && isvarchr(str[i + 1]))
		{
			if (i - 1 != j)
				parts++;
			while (isvarchr(str[i + 1]))
				i++;
			j = i;
			parts++;
		}
		i++;
	}
	if (str[j + 1])
		parts++;
	return (parts);
}

// splits string into array of variables and parts inbetween
static char	**make_tmp_array(char *str, char **tmp_array)
{
	int	(*ft_len)(char *);
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && isvarchr(str[i + 1]))
			ft_len = len_of_var;
		else
			ft_len = len_till_var;
		tmp_array[j] = ft_substr(str, i, ft_len(&str[i]));
		if (!tmp_array[j])
			return (print_error(NULL, NULL), free_chrarray(tmp_array));
		j++;
		i += ft_len(&str[i]);
	}
	tmp_array[j] = NULL;
	return (tmp_array);
}

// takes variable and replaces it with its value from env
char	*get_var(char *str)
{
	char	*tmp_str;

	if (!getenv(str + 1))
		tmp_str = ft_strdup("");
	else
		tmp_str = ft_strdup(getenv(str + 1));
	if (!tmp_str)
		print_error(NULL, NULL);
	free(str);
	return (tmp_str);
}

// makes temporary array, expands the variable parts, and joins
// it back together (NEED TO ADD $ARG, $? AND $digit)
char	*expand_var(char *str)
{
	char	**tmp_array;
	int		parts;
	int		i;

	parts = 0;
	parts = count_parts(str, parts);
	tmp_array = ft_calloc(parts + 1, sizeof(char *));
	if (!tmp_array)
	{
		print_error(NULL, NULL);
		return (free(str), NULL);
	}
	tmp_array = make_tmp_array(str, tmp_array);
	if (!tmp_array)
		return (free(str), NULL);
	free(str);
	i = 0;
	while (tmp_array[i])
	{
		if (tmp_array[i][0] == '$' && isvarchr(tmp_array[i][1]))
			tmp_array[i] = get_var(tmp_array[i]);
		if (!tmp_array[i])
			return (free_chrarray(tmp_array));
		i++;
	}
	return (join_new_str(tmp_array));
}
