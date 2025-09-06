/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolavale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:15:47 by rolavale          #+#    #+#             */
/*   Updated: 2025/09/03 15:58:33 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_redirections_built(t_pars *lst, t_all *all)
{
	while (lst)
	{
		if (check_redir(lst->type) == 1)
		{
			if (trytoopen(lst, all, 0) == -1)
			{
				all->faile_open = true;
				clear_fd(all);
				all->last_exit_status = 1;
				return ;
			}
		}
		lst = lst->next;
	}
	dup_redir_built(all);
}

static int	builtin_check(t_pars **lst)
{
	t_pars	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			if (is_builtin(tmp->content))
				return (1);
			else
				return (-1);
		}
		tmp = tmp->next;
	}
	return (-1);
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
}

void	wait_all_pid(t_all *all)
{
	int	i;

	if (!all->tab_pid)
		return ;
	i = 0;
	while (i < all->data.nb_pipeline && all->tab_pid[i] != -1)
	{
		set_exitcode_pipe(all, all->tab_pid[i]);
		i++;
	}
}

int	executor(t_all *all)
{
	if (all->pipe == false && builtin_check(all->lst) == 1)
		set_redirections_built(*(all->lst), all);
	else if (all->pipe == false)
		set_redirections(*(all->lst), all);
	else
	{
		all->i_pid = 0;
		set_redirections_pipe(all);
		wait_all_pid(all);
		if (all->tab_pid_check)
		{
			free(all->tab_pid);
			all->tab_pid_check = false;
		}
		all->pipe_info.last_fd = -1;
		all->pipe_info.pipe_fd[0] = -1;
		all->pipe_info.pipe_fd[1] = -1;
	}
	return (0);
}
