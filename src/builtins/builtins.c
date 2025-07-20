/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:34:53 by amairia           #+#    #+#             */
/*   Updated: 2025/07/19 23:35:43 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	execute_builtin(t_command *cmd, t_all *all)
{
	char	*cmd_name;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (127);
	cmd_name = cmd->argv[0];
	if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (builtin_cd(cmd->argv, all));
	if (ft_strncmp(cmd_name, "env", 4) == 0)
		return (builtin_env(all->env_list));
	if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (builtin_export(cmd->argv, &all->env_list));
	if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (builtin_unset(cmd->argv, &all->env_list));
	if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (builtin_exit(cmd->argv, all));
	return (127);
}
