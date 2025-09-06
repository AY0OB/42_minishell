/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:46:57 by amairia           #+#    #+#             */
/*   Updated: 2025/09/05 16:51:14 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_redirections_pipe_bis(t_all *all)
{
	if (all->data.pipe_done == all->data.nb_pipeline)
	{
		close(all->pipe_info.last_fd);
		return (-1);
	}
	return (0);
}

void	set_pipe_fd(t_all *all)
{
	pipe(all->pipe_info.pipe_fd);
	if (all->data.std_in == 0 && all->data.pipe_done != 0)
		all->data.std_in = all->pipe_info.last_fd;
	else if (all->pipe_info.last_fd != -1)
		close(all->pipe_info.last_fd);
	all->pipe_info.last_fd = all->pipe_info.pipe_fd[0];
	if (all->data.std_out == 1
		&& all->data.pipe_done != all->data.nb_pipeline - 1)
		all->data.std_out = all->pipe_info.pipe_fd[1];
	else
		close(all->pipe_info.pipe_fd[1]);
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

int	set_cmd_pipe(t_all *all, char ***cmd, char **cmd_path)
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
