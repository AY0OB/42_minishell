/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:34:53 by amairia           #+#    #+#             */
/*   Updated: 2025/09/02 00:01:35 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (1);
	return (0);
}

int	check_pipe_builtins(int exitcode, char **cmd, t_all *all)
{
	if (all->pipe == false)
		return (exitcode);
	if (cmd)
		free(cmd);
	close(all->data.og_in);
	close(all->data.og_out);
	if (all->data.std_in != 0)
		close(all->data.std_in);
	if (all->data.std_out != 1)
		close(all->data.std_out);
	clear_all(all, NULL);
	exit(exitcode);
}

int	execute_builtin(char **cmd, t_all *all)
{
	char	*cmd_name;
	int		exitcode;

	exitcode = 127;
	if (!cmd || !cmd[0])
		return (check_pipe_builtins(0, cmd, all));
	cmd_name = cmd[0];
	if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		exitcode = builtin_pwd();
	else if (ft_strncmp(cmd_name, "echo", 5) == 0)
		exitcode = builtin_echo(cmd, all->last_exit_status);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		exitcode = builtin_cd(cmd, all);
	else if (ft_strncmp(cmd_name, "env", 4) == 0)
		exitcode = builtin_env(all->env_list);
	else if (ft_strncmp(cmd_name, "export", 7) == 0)
		exitcode = builtin_export(cmd, &all->env_list);
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		exitcode = builtin_unset(cmd, &all->env_list);
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		exitcode = builtin_exit(cmd, all);
	return (check_pipe_builtins(exitcode, cmd, all));
}
