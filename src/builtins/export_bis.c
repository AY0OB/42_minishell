/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 03:54:04 by amairia           #+#    #+#             */
/*   Updated: 2025/07/20 04:28:27 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_var	*split_env_var(const char *arg)
{
	t_env_var	*var;
	char		*equal_sign;

	var = ft_calloc(1, sizeof(t_env_var));
	if (!var)
		return (NULL);
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		free(var);
		return (NULL);
	}
	var->key = ft_substr(arg, 0, equal_sign - arg);
	var->value = ft_strdup(equal_sign + 1);
	return (var);
}

void	print_sorted_env(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(array[i], STDOUT_FILENO);
		i++;
	}
}
