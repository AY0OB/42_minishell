/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:40:18 by amairia           #+#    #+#             */
/*   Updated: 2025/08/30 17:07:53 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_numeric(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	exit_bis(t_all *all, char **argv, int exitcode)
{
	clear_all(all, NULL);
	free(argv);
	exit(exitcode);
}

int	builtin_exit(char **argv, t_all *all)
{
	int	exitcode;

	exitcode = all->last_exit_status;
	if (!all->pipe)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!argv[1])
		exit_bis(all, argv, exitcode);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_bis(all, argv, 2);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		if (all->pipe)
			exit_bis(all, argv, 1);
		return (1);
	}
	exit_bis(all, argv, ft_atoi(argv[1]));
	return (0);
}
