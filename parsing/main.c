/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:57:54 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/02 16:57:02 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	store_env(t_data *data, char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		data->env[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	data->env[i] = NULL;
// }

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc != 1 || argv[1])
		return (1);
	data.env = env;
	data.input = readline(PROMPT);
	data.lexer = NULL;
	data.cmds = NULL;
	while (data.input != NULL)
	{
		tokenizer(&data);
		parser(&data);
		add_history(data.input);
		executor(&data);
		// free_lexer(&data.lexer);
		free(data.input);
		data.input = readline(PROMPT);
	}
	return (0);
}
