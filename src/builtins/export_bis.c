/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 03:54:04 by amairia           #+#    #+#             */
/*   Updated: 2025/07/20 16:58:37 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_list_to_array_bis(t_env_var *var,
		char **array, char *tmp, int i)
{
	tmp = ft_strjoin(var->key, "=\"");
	array[i] = ft_strjoin(tmp, var->value);
	free(tmp);
	tmp = array[i];
	array[i] = ft_strjoin(tmp, "\"");
	free(tmp);
}

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
