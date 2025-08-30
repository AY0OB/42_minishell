/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:34:53 by amairia           #+#    #+#             */
/*   Updated: 2025/08/28 16:38:11 by amairia          ###   ########.fr       */
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

int	execute_builtin(char **cmd, t_all *all)
{
	char	*cmd_name;

	if (!cmd || !cmd[0])
		return (0);
	cmd_name = cmd[0];
	if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		return (builtin_echo(cmd, all->last_exit_status));
	if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (builtin_cd(cmd, all));
	if (ft_strncmp(cmd_name, "env", 4) == 0)
		return (builtin_env(all->env_list));
	if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (builtin_export(cmd, &all->env_list));
	if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (builtin_unset(cmd, &all->env_list));
	if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (builtin_exit(cmd, all));
	return (127);
}
