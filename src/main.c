/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:11:16 by amairia           #+#    #+#             */
/*   Updated: 2025/08/26 18:14:22 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

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

	if (set_list(&lst) == -1)
	{
		clear_all(*all, NULL);
		return (-1);
	}
	pars_lstclear(*all);
	all[0]->lst = lst;
	return (0);
}

static int	do_prog(char *line, t_all **all,
			t_command **commands, char ***envp)
{
	int	check;

	line = readline("minishell ");
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
		if (check == 0)
		{
			*commands = interpreter((all[0]->lst));
			//if (*commands)
				//all[0]->last_exit_status = executor(*commands, *envp, *all);
			all[0]->last_exit_status = executor(*commands, *envp, *all);
			free_command_list(*commands);
		}
		if (do_prog_bis(all) == -1)
			return (-1);
		setup_interactive_mode();
	}
	free(line);
	return (0);
}

// =============
// FONCTION MAIN
// =============

int	main(int argc, char **argv, char **envp)
{
	t_all		*all;
	t_command	*commands;
	int			exit_code;
	int			check;

	(void)argc;
	(void)argv;
	all = set_struct();
	if (!all)
		return (-1);
	all->env_list = init_environment(envp);
	setup_interactive_mode();
	check = do_prog(NULL, &all, &commands, &envp);
	while (check == 0)
	{
		check = do_prog(NULL, &all, &commands, &envp);
	}
	if (check == -1)
		return (-1);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit_code = all->last_exit_status;
	clear_all(all, NULL);
	return (exit_code);
}
