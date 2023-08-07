/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:57:54 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/07 16:09:11 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell.h"

/*	store the env variables in a linked list
	each node contains one variable */

// void	init_env(t_data *data, char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 		add_lex_node(&data->env, 0, ft_strdup(env[i++]));
// }

/*	store the arguments in the data struct as struct
	and the env as linked list */

void	init_data(t_data *data)
{
	data->input = readline(PROMPT);
	data->lexer = NULL;
	data->cmds = NULL;
	// init_env(data, env);
}

/*	Reset the data struct for next cmd. Env stays unchanged */

void	reset_data(t_data *data)
{
	free_cmd_list(&data->cmds);
	data->nr_pipes = 0;
	free(data->input);
	data->input = readline(PROMPT);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc != 1 || argv [1])
		return (1);
	data.env = env;
	init_data(&data);
	while (data.input != NULL)
	{
		tokenizer(&data);
		parser(&data);
		add_history(data.input);
		executor(&data);
		free_lexer(&data.lexer);
		reset_data(&data);
	}
	return (0);
}