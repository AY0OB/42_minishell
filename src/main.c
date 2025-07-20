/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:11:16 by amairia           #+#    #+#             */
/*   Updated: 2025/07/20 01:11:50 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

// ==========================
// FONCTIONS D'INITIALISATION
// ==========================

static int	set_list(t_pars ***lst)
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

static t_all	*set_struct(void)
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
	all->env_list = NULL;
	return (all);
}

// =============
// FONCTION MAIN
// =============

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_all		*all;
	t_command	*commands;

	(void)argc;
	(void)argv;
	all = set_struct();
	if (!all)
		return (-1);
	all->env_list = init_environment(envp);
	setup_interactive_mode();
	while (1)
	{
		line = readline("minishell ");
		if (!line)
			break ;
		if (line && *line)
			add_history((const char *)line);
		if (line && *line && first_pars(line) == 1 && check_quote(line) == 1)
		{
			if (parsing(line, all->lst) == -1)
			{
				ft_printf("Allco error\n");
				clear_all(all, line);
				return (-1);
			}
			commands = interpreter(*(all->lst));
			if (commands)
				all->last_exit_status = executor(commands, envp, all);
			free_command_list(commands);
			if (line)
				free(line);
			pars_lstclear(all);
			if (set_list(&(all->lst)) == -1)
			{
				clear_all(all, line);
				return (-1);
			}
			setup_interactive_mode();
		}
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	clear_all(all, line);
	return (all->last_exit_status);
}
