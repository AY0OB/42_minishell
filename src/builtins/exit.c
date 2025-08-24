/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:40:18 by amairia           #+#    #+#             */
/*   Updated: 2025/08/24 23:26:44 by amairia          ###   ########.fr       */
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

static void	check(t_all *all, t_command *cmd, int exit_cd)
{
	bool	pipe;

	pipe = all->pipe;
	free_command_list(cmd);
	clear_all(all, NULL);
	if (pipe)
		ft_exit(exit_cd);
	exit(exit_cd);
}

static void	builtin_exit_bis(char *str, t_all *all, t_command *cmd)
{
	long long	exit_code;

	if (!str)
	{
		exit_code = all->last_exit_status;
		check(all, cmd, exit_code);
	}
}

static void	clear_list(t_all *all, t_command *cmd)
{
	if (all->pipe)
	{
		clear_all(all, NULL);
		free_command_list(cmd);
	}
}

int	builtin_exit(char **argv, t_all *all, t_command *cmd)
{
	long long	exit_code;

	if (!all->pipe)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	builtin_exit_bis(argv[1], all, cmd);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		check(all, cmd, 255);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		clear_list(all, cmd);
		return (1);
	}
	exit_code = ft_atoi(argv[1]);
	check(all, cmd, (int)exit_code);
	return (0);
}
