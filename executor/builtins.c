#include "../includes/minishell.h"

static int	find_option(char *str)
{
	int	i;

	if (!(str[0] && str[0] == '-'))
		return (0);
	if (!str[1])
		return (1);
	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (i == 1 || str[i])
		return (0);
	return (2);
}

int	ft_echo(t_data *data, t_cmd *cmd)
{
	int	isoption;
	int	i;

	(void)data;
	if (!cmd->args[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	isoption = find_option(cmd->args[1]);
	i = 1;
	while (cmd->args[i])
	{
		if (i > 2 || (i == 2 && isoption == 0))
			ft_putchar_fd(' ', 1);
		if (!(i == 1 && isoption > 0))
			ft_putstr_fd(cmd->args[i], 1);
		i++;
	}
	if (isoption != 2)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_pwd(t_data *data, t_cmd *cmd)
{
	char	*buffer;
	
	if (cmd->args[1])
	{
		print_error(cmd->args[0], "too many arguments");
		return (1);
	}
	if (ft_getenv(data, "PWD"))
		ft_putendl_fd(ft_getenv(data, "PWD"), 1);
	else
	{
		buffer = ft_calloc(200, sizeof(char));
		buffer = getcwd(buffer, 200);
		if (!buffer)
			return (print_error(NULL, NULL), 1);
		ft_putendl_fd(buffer, 1);
		free(buffer);
		buffer = NULL;
	}
	return (0);
}

int	ft_env(t_data *data, t_cmd *cmd)
{
	t_lexer	*tmp;

	if (cmd->args[1])
	{
		print_error(cmd->args[0], "too many arguments");
		return (1);
	}
	tmp = *(data->env);
	while (tmp)
	{
		ft_putendl_fd(tmp->chars, 1);
		tmp = tmp->next;
	}
	return (0);
}

int	(*isbuiltin(char *str))(t_data *, t_cmd *)
{
	if (ft_strncmp(str, "echo", ft_strlen(str) + 1) == 0)
		return (ft_echo);
	// if (ft_strncmp(str, "cd", ft_strlen(str) + 1) == 0)
	// 	return (ft_cd);
	if (ft_strncmp(str, "pwd", ft_strlen(str) + 1) == 0)
		return (ft_pwd);
	// if (ft_strncmp(str, "export", ft_strlen(str) + 1) == 0)
	// 	return (ft_export);
	// if (ft_strncmp(str, "unset", ft_strlen(str) + 1) == 0)
	// 	return (ft_unset);
	if (ft_strncmp(str, "env", ft_strlen(str) + 1) == 0)
		return (ft_env);
	// if (ft_strncmp(str, "exit", ft_strlen(str) + 1) == 0)
	// 	return (ft_exit);
	return (NULL);
}

int	run_builtin(t_data *data, t_cmd *cmd, int ischild)
{
	int	exit_stat;

	exit_stat = (*isbuiltin(cmd->args[0]))(data, cmd);
	if (ischild == 1)
		exit(exit_stat);
	return (exit_stat);
}
