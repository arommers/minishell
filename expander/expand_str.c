/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_str.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 14:53:00 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/09 15:36:18 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// counts size of array by counting quoted + unquoted parts
static int	count_parts(char *str, char c, int parts)
{
	int		i;

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

// splits string into array of quoted and unquoted parts
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
		tmp_array[j] = ft_substr(str, i,
				len_till_quote(&str[i + k], c) + k * 2);
		if (!tmp_array[j])
			return (free_chrarray(tmp_array));
		j++;
		i += len_till_quote(&str[i + k], c) + k * 2;
	}
	tmp_array[j] = NULL;
	return (tmp_array);
}

// loops through array, removes quotes, expands variables if necessary
static char	**expand_tmp_array(char **tmp_array, int isheredoc)
{
	char	*tmp_str;
	int		i;

	i = 0;
	while (tmp_array[i])
	{
		if (isheredoc == 0 && tmp_array[i][0] != '\''
			&& ft_strchr(tmp_array[i], '$'))
		{
			tmp_array[i] = expand_var(tmp_array[i]);
			if (!tmp_array[i])
				return (free_chrarray(tmp_array));
		}
		if (isquote(tmp_array[i][0]))
		{
			tmp_str = ft_substr(tmp_array[i], 1,
					ft_strlen(tmp_array[i]) - 2);
			if (!tmp_str)
				return (free_chrarray(tmp_array));
			free(tmp_array[i]);
			tmp_array[i] = tmp_str;
		}
		i++;
	}
	return (tmp_array);
}

// makes temporary array, expands the right parts, and joins it back together
char	*expand_str(char *str, int isheredoc)
{
	char	**tmp_array;
	char	c;
	int		parts;

	c = '\0';
	parts = 0;
	parts = count_parts(str, c, parts);
	tmp_array = ft_calloc(parts + 1, sizeof(char *));
	if (!tmp_array)
		return (free(str), NULL);
	tmp_array = make_tmp_array(str, c, tmp_array);
	if (!tmp_array)
		return (free(str), NULL);
	free(str);
	tmp_array = expand_tmp_array(tmp_array, isheredoc);
	if (!tmp_array)
		return (NULL);
	return (join_new_str(tmp_array));
}
