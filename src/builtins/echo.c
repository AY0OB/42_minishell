/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:20:24 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:20:32 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** echo
** + option -n
*/
int	builtin_echo(char **argv)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0)
	{
		newline_flag = 0; // si on trouve -n, on supprime le \n final
		i++;
	}
	// boucle pour afficher les arguments restants
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		// affiche un espace s'il y a un argument après
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
