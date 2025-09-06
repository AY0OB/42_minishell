/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolavale <rolavale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 21:39:47 by amairia           #+#    #+#             */
/*   Updated: 2025/09/04 20:05:23 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_list(t_pars ***lst)
{
	*lst = NULL;
	*lst = malloc(sizeof(t_pars *));
	if (!(*lst))
	{
		ft_printf("Alloc error\n");
		return (-1);
	}
	**lst = NULL;
	return (0);
}

static void	set_data(t_all *all)
{
	all->data.std_in = 0;
	all->data.std_out = 1;
	all->data.pipe_done = 0;
	all->data.nb_pipeline = 1;
	all->pipe_info.last_fd = -1;
	all->pipe_info.pipe_fd[0] = -1;
	all->pipe_info.pipe_fd[1] = -1;
}

t_all	*set_struct(void)
{
	t_all		*all;
	t_pars		**lst;

	all = malloc(sizeof(t_all));
	if (!all)
	{
		ft_putstr_fd("Alloc error\n", STDOUT_FILENO);
		return (NULL);
	}
	if (set_list(&lst) == -1)
	{
		free(all);
		return (NULL);
	}
	all->lst = lst;
	all->last_exit_status = 0;
	all->pipe = false;
	all->faile_open = false;
	all->is_builtin = false;
	all->env_list = NULL;
	all->tab_pid = NULL;
	all->tab_pid_check = false;
	set_data(all);
	return (all);
}
