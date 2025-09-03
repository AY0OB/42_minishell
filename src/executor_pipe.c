/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 23:16:31 by amairia           #+#    #+#             */
/*   Updated: 2025/09/03 16:44:24 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_and_close(t_all *all, char ***cmd)
{
	free(cmd[0]);
	all->faile_open = false;
	all->last_exit_status = 0;
	clear_fd(all);
	return (-1);
}

int	set_cmd_pipe(t_all *all, char ***cmd, char **cmd_path, char **envp)
{
	cmd[0] = feed_cmd(all);
	if (!cmd[0])
		return (-1);
	if (!cmd[0][0])
		return (free_and_close(all, cmd));
	if (is_builtin(cmd[0][0]) == 1)
	{
		all->is_builtin = true;
		return (0);
	}
	cmd_path[0] = get_command_path(cmd[0][0], envp);
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

void	dup_redir_pipe(t_all *all)
{
	all->data.og_in = dup(STDIN_FILENO);
	all->data.og_out = dup(STDOUT_FILENO);
	if (all->data.std_in != 0)
		dup2(all->data.std_in, STDIN_FILENO);
	if (all->data.std_out != 1)
		dup2(all->data.std_out, STDOUT_FILENO);
}

void	exec_cmd(t_all *all, char **cmd, char *cmd_path, char **envp)
{
	dup_redir_pipe(all);
	if (all->is_builtin)
		execute_builtin(cmd, all);
	close(all->data.og_in);
	close(all->data.og_out);
	if (all->data.std_in != 0)
		close(all->data.std_in);
	if (all->data.std_out != 1)
		close(all->data.std_out);
	execve(cmd_path, cmd, envp);
}

void	set_exitcode_pipe(t_all *all, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		all->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		all->last_exit_status = 128 + WTERMSIG(status);
	else
		all->last_exit_status = 1;
	if (all->faile_open)
		all->last_exit_status = 1;
	all->faile_open = false;
	clear_fd(all);
}

void	exec_pipe(t_all *all, char **envp)
{
	pid_t	pid;
	char	**cmd;
	char	*cmd_path;

	cmd = NULL;
	cmd_path = NULL;
	if (set_cmd_pipe(all, &cmd, &cmd_path, envp) == -1)
	{
		clear_fd(all);
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_cmd(all, cmd, cmd_path, envp);
	all->is_builtin = false;
	free(cmd);
	if (cmd_path)
		free(cmd_path);
	set_exitcode_pipe(all, pid);
}

void	set_pipe_data(t_all *all)
{
	int		nb_pipeline;
	t_pars	*tmp;

	nb_pipeline = 1;
	tmp = *(all->lst);
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			nb_pipeline++;
		tmp = tmp->next;
	}
	all->data.nb_pipeline = nb_pipeline;
	all->data.pipe_done = 0;
}

t_pars	*set_lst_place(t_all *all)
{
	int		curr_done;
	t_pars	*tmp;

	curr_done = 0;
	tmp = *(all->lst);
	while (tmp && curr_done < all->data.pipe_done)
	{
		if (tmp->type == T_PIPE)
			curr_done++;
		tmp = tmp->next;
	}
	return (tmp);
}

void	check_faile_and_exec(t_all *all, char **envp)
{
	if (all->faile_open)
	{
		clear_fd(all);
		all->last_exit_status = 1;
		all->faile_open = false;
	}
	else
		exec_pipe(all, envp);
	all->data.pipe_done++;
}

void	set_redirections_pipe(t_all *all, char **envp)
{
	t_pars	*tmp;

	set_pipe_data(all);
	while (1)
	{
		if (all->data.pipe_done == all->data.nb_pipeline)
			break ;
		tmp = set_lst_place(all);
		pars_exitcode(all->lst, all->last_exit_status, all->data.pipe_done);
		while (tmp && tmp->type != T_PIPE)
		{
			if (check_redir(tmp->type) == 1)
			{
				if (trytoopen(tmp, all, 0) == -1)
				{
					all->faile_open = true;
					break ;
				}
			}
			tmp = tmp->next;
		}
		check_faile_and_exec(all, envp);
	}
	all->data.pipe_done = 0;
}
