/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 23:16:31 by amairia           #+#    #+#             */
/*   Updated: 2025/09/04 15:17:31 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_pipe_data(t_all *all)
{
	int		nb_pipeline;
	int		i;
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
	all->tab_pid = ft_calloc(sizeof(pid_t), nb_pipeline);
	if (!all->tab_pid)
		return (-1);
	all->tab_pid_check = true;
	i = 0;
	while (i < nb_pipeline)
		all->tab_pid[i++] = -1;
	return (0);
}

void	set_redirections_pipe(t_all *all)
{
	t_pars	*tmp;

	if (set_pipe_data(all) == -1)
		return ;
	while (1)
	{
		if (set_redirections_pipe_bis(all) == -1)
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
		check_faile_and_exec(all);
	}
	all->data.pipe_done = 0;
}
