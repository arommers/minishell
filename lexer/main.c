/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:57:54 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/10 18:00:22 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell.h"

/*	store the env variables in a linked list
	each node contains one variable */

void	init_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		add_lex_node(&data->env, 0, ft_strdup(env[i++]));
}

/*	store the arguments in the data struct as struct
	and the env as linked list */

void	init_data(t_data *data, char **env)
{
	data->input = readline(PROMPT);
	if (!data->input)
	{
		ft_putstr_fd("exit\n", 2);
		exit (1);
	}
	data->lexer = NULL;
	data->cmds = NULL;
	data->exit_stat = 0;
	init_env(data, env);
}

/*	Reset the data struct for next cmd. Env stays unchanged */

void	reset_data(t_data *data)
{
	free_cmd_list(&data->cmds);
	data->nr_pipes = 0;
	free(data->input);
	data->input = readline(PROMPT);
	if (!data->input)
	{
		ft_putstr_fd("exit\n", 2);
		exit (1);
	}
	maintain_prompt(data);
}

void	maintain_prompt(t_data *data)
{
	add_history(data->input);
	input_check(data);
	tokenizer(data);
	if (data->lexer && data->lexer->token == PIPE)
		syntax_error(data, data->lexer->token);
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
