/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:57:54 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/28 13:16:14 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	store the env variables in a linked list
	each node contains one variable */

void	init_env(t_data *data, char **env)
{
	int	i;

	data->env = ft_calloc(1, sizeof(t_lexer *));
	i = 0;
	while (env[i])
	{
		add_lex_node(data->env, 0, ft_strdup(env[i]));
		i++;
	}
}

/*	store the arguments in the data struct as struct
	and the env as linked list */

void	init_data(t_data *data, char **env)
{
	g_exit_status = 0;
	init_signals(1);
	data->input = readline(PROMPT);
	if (!data->input)
	{
		ft_putstr_fd("exit\n", 2);
		exit (1);
	}
	data->lexer = NULL;
	data->cmds = NULL;
	data->pipe_1 = NULL;
	data->pipe_2 = NULL;
	init_env(data, env);
}

/*	Reset the data struct for next cmd. Env stays unchanged */

void	reset_data(t_data *data)
{
	free_cmd_list(&data->cmds);
	if (data->pipe_1)
		free(data->pipe_1);
	if (data->pipe_2)
		free(data->pipe_2);
	data->pipe_1 = NULL;
	data->pipe_2 = NULL;
	data->nr_pipes = 0;
	free(data->input);
	init_signals(1);
	data->input = readline(PROMPT);
	if (!data->input)
	{
		ft_putstr_fd("exit\n", 2);
		exit (1);
	}
	maintain_prompt(data);
}

/*	- Maintains a loop that will displays a prompt
	- Parses and executes the input when valid
	- Checks input for syntax errors */

void	maintain_prompt(t_data *data)
{
	add_history(data->input);
	input_check(data);
	if (!tokenizer(data))
		reset_data(data);
	if (data->lexer && data->lexer->token == PIPE)
		syntax_error(data, data->lexer->token);
	// if (check_last(&data->lexer))
	// 	syntax_error(data, PIPE);
	parser(data);
	if (data->cmds)
		executor(data);
	reset_data(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc != 1 || argv [1])
		return (1);
	init_data(&data, env);
	maintain_prompt(&data);
	return (0);
}
