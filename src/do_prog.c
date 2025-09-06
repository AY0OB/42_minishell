/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_prog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:01:45 by amairia           #+#    #+#             */
/*   Updated: 2025/09/06 16:22:48 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_pars(char **line, t_all **all)
{
	int	check;

	check = parsing(*line, all[0]->lst, *all);
	if (check == -1)
	{
		ft_printf("Alloc error\n");
		clear_all(*all, *line);
	}
	return (check);
}

static int	do_prog_bis(t_all **all)
{
	t_pars	**lst;

	setup_interactive_mode();
	if (set_list(&lst) == -1)
	{
		clear_all(*all, NULL);
		return (-1);
	}
	pars_lstclear(*all);
	all[0]->lst = lst;
	if (all[0]->last_exit_status == 131)
		ft_printf("Quit\n");
	if (all[0]->last_exit_status == 141)
		all[0]->last_exit_status = 0;
	return (0);
}

static void	check_ctrlc(t_all *all)
{
	if (g_check_ctrlc == 130)
		all->last_exit_status = 130;
}

static void	exitcode_prog(char *line, t_all **all)
{
	if (line[0])
		all[0]->last_exit_status = 2;
	else
		all[0]->last_exit_status = 0;
}

int	do_prog(char *line, t_all **all)
{
	int	check;

	line = readline("minishell ");
	check_ctrlc(all[0]);
	if (!line)
		return (1);
	if (line && line[0])
		add_history((const char *)line);
	if (line && line[0] && first_pars(line, 0) == 1
		&& check_quote(line) == 1)
	{
		check = check_pars(&line, all);
		if (check == -1)
			return (-1);
		if (check == 0 && all[0]->lst[0]->content[0])
			executor(*all);
		if (check == 1)
			all[0]->last_exit_status = 130;
		if (do_prog_bis(all) == -1)
			return (-1);
	}
	else
		exitcode_prog(line, all);
	free(line);
	return (0);
}
