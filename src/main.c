/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:11:16 by amairia           #+#    #+#             */
/*   Updated: 2025/08/10 15:32:47 by amairia          ###   ########.fr       */
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

static int	do_prog_bis(char **line, t_all **all)
{
	t_pars	**lst;

	if (set_list(&lst) == -1)
	{
		clear_all(*all, *line);
		return (-1);
	}
	pars_lstclear(*all);
	all[0]->lst = lst;
	return (0);
}

static int	do_prog(char **line, t_all **all,
			t_command **commands, char ***envp)
{
	*line = readline("minishell ");
	if (!*line)
		return (1);
	if (*line && line[0][0])
		add_history((const char *)*line);
	if (*line && line[0][0] && first_pars(*line) == 1
			&& check_quote(*line) == 1)
	{
		if (parsing(*line, all[0]->lst) == -1)
		{
			ft_printf("Alloc error\n");
			clear_all(*all, *line);
			return (-1);
		}
		if (*line)
			free(*line);
		*commands = interpreter(*(all[0]->lst));
		if (*commands)
			all[0]->last_exit_status = executor(*commands, *envp, *all);
		free_command_list(*commands);
		if (do_prog_bis(line, all) == -1)
			return (-1);
		/*if (*line)
			free(*line);
		pars_lstclear(*all);
		if (set_list(&(all[0]->lst)) == -1)
		{
			clear_all(*all, *line);
			return (-1);
		}*/
		setup_interactive_mode();
	}
	return (0);
}

// =============
// FONCTION MAIN
// =============

int	main(int argc, char **argv, char **envp)
{
	char		*line;
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
	check = do_prog(&line, &all, &commands, &envp);
	while (check == 0)
	{
		check = do_prog(&line, &all, &commands, &envp);
		/*line = readline("minishell ");
		if (!line)
			break ;
		if (line && *line)
			add_history((const char *)line);
		if (line && *line && first_pars(line) == 1 && check_quote(line) == 1)
		{
			if (parsing(line, all->lst) == -1)
			{
				ft_printf("Alloc error\n");
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
		}*/
	}
	if (check == -1)
		return (-1);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit_code = all->last_exit_status;
	clear_all(all, NULL);
	return (exit_code);
}
