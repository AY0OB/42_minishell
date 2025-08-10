/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:39:39 by amairia           #+#    #+#             */
/*   Updated: 2025/08/10 19:55:07 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	aff_str(char *str, int exit_code)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			ft_putnbr_fd(exit_code, 1);
			i += 2;
		}
		else
			write(1, &str[i++], 1);
	}
}

int	builtin_echo(char **argv, int exit_code)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0)
	{
		newline_flag = 0;
		i++;
	}
	while (argv[i])
	{
		//ft_putstr_fd(argv[i], STDOUT_FILENO);
		aff_str(argv[i], exit_code);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
