/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 10:01:26 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/27 17:00:50 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_j(t_tokens token)
{
	if (token == PIPE)
		return (1);
	else if (token == LESS)
		return (2);
	else if (token == LESSLESS)
		return (3);
	else if (token == GREAT)
		return (4);
	else
		return (5);
}

void	print_lex_list(t_lexer *head)
{
	char			*tmp[] = {
		"WORDS",
		"PIPE",
		"LESS",
		"LESSLESS",
		"GREAT",
		"GREATGREAT",
		NULL,
	};
	t_lexer			*current;
	int				i;
	int				j;

	current = head;
	i = 0;
	while (current)
	{
		if (current->token == 0)
			printf("NODE %d: %s\n", i, current->chars);
		else
		{
			j = check_j(current->token);
			printf("NODE %d: %s\n", i, tmp[j]);
		}
		current = current->next;
		i++;
	}
}

char	*make_str(char **head)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	len = 0;
	while (head[i])
		len += ft_strlen(head[i++]);
	printf("test\n");
	tmp = malloc(len * sizeof(char) + 1);
	i = 0;
	while (head[i])
	{
		j = 0;
		while (head[i][j])
			tmp[k++] = head[i][j++];
		i++;
	}
	tmp[k] = '\0';
	return (tmp);
}

void	print_cmd_list(t_cmd *head)
{
	t_cmd	*current;
	char	*tmp;
	int		i;

	i = 0;
	current = head;
	tmp = make_str(head->args);
	printf("%s\n", tmp);
	while (current)
	{
		printf("CMD_NODE: %d, ARGS: %s TOKEN: %d FILE: %s\n", i++, tmp,
			head->re_dir->token, head->re_dir->chars);
		free(tmp);
		current = current->next;
	}
}
