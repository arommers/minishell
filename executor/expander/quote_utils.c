/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 17:09:53 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/29 18:54:00 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

// searches string for quotes, returns first one encountered
char	*quote_strchr(char *str)
{
	char	*single_quote;
	char	*double_quote;

	single_quote = ft_strchr(str, '\'');
	double_quote = ft_strchr(str, '\"');
	if (single_quote && double_quote)
	{
		if (single_quote < double_quote)
			return (single_quote);
		else
			return (double_quote);
	}
	if (single_quote)
		return (single_quote);
	if (double_quote)
		return (double_quote);
	return (NULL);
}

// checks if char is quote
int	isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

// counts len of string till the given quote
int	len_till_quote(char *str, char quote)
{
	char	*find_quote;
	int		full_len;
	int		quote_len;

	full_len = ft_strlen(str);
	if (quote == '\0')
	{
		find_quote = quote_strchr(str);
		if (!find_quote)
			return (full_len);
		quote = find_quote[0];
	}
	quote_len = ft_strlen(ft_strchr(str, quote));
	return (full_len - quote_len);
}
