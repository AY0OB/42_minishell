/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:17:10 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:19:59 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h> // pour PATH_MAX

int	builtin_pwd(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX) != NULL) //getcwd pour le chemin courant
	{
		// print
		ft_putstr_fd(buffer, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}
