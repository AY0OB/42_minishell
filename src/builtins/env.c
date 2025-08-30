/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:39:50 by amairia           #+#    #+#             */
/*   Updated: 2025/08/24 20:35:31 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env_var(void *env_var_ptr)
{
	t_env_var	*var;

	var = (t_env_var *)env_var_ptr;
	if (var && var->value)
	{
		ft_putstr_fd(var->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(var->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

int	builtin_env(t_list *env_list)
{
	ft_lstiter(env_list, print_env_var);
	return (0);
}
