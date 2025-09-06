/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolavale <rolavale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:11:16 by amairia           #+#    #+#             */
/*   Updated: 2025/09/06 16:01:17 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_check_ctrlc;

// =============
// FONCTION MAIN
// =============

int	main(int argc, char **argv, char **envp)
{
	t_all		*all;
	int			exit_code;
	int			check;

	(void)argc;
	(void)argv;
	all = set_struct();
	if (!all)
		return (-1);
	all->env_list = init_environment(envp);
	setup_interactive_mode();
	check = do_prog(NULL, &all);
	while (check == 0)
	{
		check = do_prog(NULL, &all);
	}
	if (check == -1)
		return (-1);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit_code = all->last_exit_status;
	clear_all(all, NULL);
	return (exit_code);
}
