/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:20:33 by amairia           #+#    #+#             */
/*   Updated: 2025/09/04 19:52:30 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_cmd(t_all *all, char ***cmd, char **cmd_path)
{
	cmd[0] = feed_cmd(all);
	if (!cmd[0])
		return (-1);
	if (!cmd[0][0])
	{
		all->last_exit_status = 0;
		if (all->faile_open)
			all->last_exit_status = 1;
		all->faile_open = false;
		free(cmd[0]);
		return (-1);
	}
	cmd_path[0] = get_command_path(cmd[0][0], all->env_list);
	if (!cmd_path[0])
	{
		ft_printf("minishell: command not found: %s\n", cmd[0][0]);
		all->last_exit_status = 127;
		if (all->faile_open)
			all->last_exit_status = 1;
		all->faile_open = false;
		free(cmd[0]);
		return (-1);
	}
	return (0);
}

void	set_exitcode(t_all *all, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		all->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		all->last_exit_status = 128 + WTERMSIG(status);
	else
		all->last_exit_status = 1;
}

void	exec(t_all *all)
{
	pid_t	pid;
	char	**cmd;
	char	*cmd_path;

	cmd = NULL;
	cmd_path = NULL;
	if (set_cmd(all, &cmd, &cmd_path) == -1)
	{
		clear_fd(all);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		close(all->data.og_in);
		close(all->data.og_out);
		if (all->data.std_in != 0)
			close(all->data.std_in);
		if (all->data.std_out != 1)
			close(all->data.std_out);
		ft_execve(all, &cmd_path, &cmd);
	}
	free(cmd);
	free(cmd_path);
	set_exitcode(all, pid);
}

void	dup_redir(t_all *all)
{
	all->data.og_in = dup(STDIN_FILENO);
	all->data.og_out = dup(STDOUT_FILENO);
	if (all->data.std_in != 0)
		dup2(all->data.std_in, STDIN_FILENO);
	if (all->data.std_out != 1)
		dup2(all->data.std_out, STDOUT_FILENO);
	exec(all);
	all->faile_open = false;
	dup2(all->data.og_in, STDIN_FILENO);
	dup2(all->data.og_out, STDOUT_FILENO);
	close(all->data.og_in);
	close(all->data.og_out);
	clear_fd(all);
}

void	set_redirections(t_pars *lst, t_all *all)
{
	while (lst)
	{
		if (check_redir(lst->type) == 1)
		{
			if (trytoopen(lst, all, 0) == -1)
			{
				all->faile_open = true;
				break ;
			}
		}
		lst = lst->next;
	}
	if (all->faile_open)
	{
		clear_fd(all);
		all->last_exit_status = 1;
		all->faile_open = false;
		return ;
	}
	dup_redir(all);
}
