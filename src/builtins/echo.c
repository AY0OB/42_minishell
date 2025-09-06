/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:39:39 by amairia           #+#    #+#             */
/*   Updated: 2025/09/05 13:40:48 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	aff_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i++], 1);
	}
}

static bool	check_flags(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (false);
	return (true);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = 1;
	while (argv[i] && check_flags(argv[i]))
	{
		newline_flag = 0;
		i++;
	}
	while (argv[i])
	{
		aff_str(argv[i]);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
