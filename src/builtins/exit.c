/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:40:18 by amairia           #+#    #+#             */
/*   Updated: 2025/07/19 23:40:19 by amairia          ###   ########.fr       */
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

static void	builtin_exit_bis(char *str, t_all *all, t_command **cmd)
{
	long long	exit_code;

	if (!str)
	{
		exit_code = all->last_exit_status;
		clear_all(all, NULL);
		free_command_list(cmd);
		exit(exit_code);
	}
}

int	builtin_exit(char **argv, t_all *all, t_command **cmd)
{
	long long	exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	builtin_exit_bis(argv[1], all, cmd);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clear_all(all, NULL);
		free_command_list(cmd);
		exit(255);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoi(argv[1]);
	clear_all(all, NULL);
	free_command_list(cmd);
	exit((unsigned char)exit_code);
}
