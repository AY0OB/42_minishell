/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:14:07 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:14:27 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** cd
*/
int	builtin_cd(char **argv)
{
	// pas d'arg = on fait rien
	if (!argv[1])
		return (0);
	// 'cd' ne prend qu'un seul argument
	if (argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1); // code d'erreur
	}
	// on utilise chdir
	if (chdir(argv[1]) != 0)
	{
		// if échec
		perror("minishell: cd");
		return (1);
	}
	return (0);
}
