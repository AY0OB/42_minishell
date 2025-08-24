/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 21:39:47 by amairia           #+#    #+#             */
/*   Updated: 2025/08/21 21:40:29 by amairia          ###   ########.fr       */
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
	all->data.std_err = 0;
	all->data.std_in = 0;
	all->data.std_out = 1;
	all->last_exit_status = 0;
	all->pipe = false;
	all->env_list = NULL;
	return (all);
}
