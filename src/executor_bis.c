/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:20:33 by amairia           #+#    #+#             */
/*   Updated: 2025/08/29 16:36:33 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_bis(t_all *all, char ***cmd, char **cmd_path, char **envp)
{
	cmd[0] = feed_cmd(all);
	if (!cmd[0])
		return (-1);
	cmd_path[0] = get_command_path(cmd[0][0], envp);
	if (!cmd_path[0])
	{
		ft_printf("minishell: command not found: %s\n", cmd[0][0]);
		all->last_exit_status = 127;
		free(cmd[0]);
		return (-1);
	}
	return (0);
}

void	exec(t_all *all, char **envp)
{
	pid_t	pid;
	int	status;
	char	**cmd;
	char	*cmd_path;

	cmd = NULL;
	cmd_path = NULL;
	if (exec_bis(all, &cmd, &cmd_path, envp) == -1)
		return ;
	pid = fork();
	if (pid == 0)
		execve(cmd_path, cmd, envp);
	free(cmd);
	free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		all->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		all->last_exit_status = 128 + WTERMSIG(status);
	else
		all->last_exit_status = 1;
	return ;
}

void	dup_redir(t_all *all, char **envp)
{
	int	og_in;
	int	og_out;

	og_in = dup(STDIN_FILENO);
	og_out = dup(STDOUT_FILENO);
	if (all->data.std_in != 0)
		dup2(all->data.std_in, STDIN_FILENO);
	if (all->data.std_out != 1)
		dup2(all->data.std_out, STDOUT_FILENO);
	exec(all, envp);
	all->faile_open = false;
	dup2(og_in, STDIN_FILENO);
	dup2(og_out, STDOUT_FILENO);
	close(og_in);
	close(og_out);
	if (all->data.std_in != 0)
	{
		close(all->data.std_in);
		all->data.std_in = 0;
	}
	if (all->data.std_out != 1)
	{
		close(all->data.std_out);
		all->data.std_out = 1;
	}
}

void	set_redirections(t_pars *lst, t_all *all, char **envp)
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
	dup_redir(all, envp);
}
