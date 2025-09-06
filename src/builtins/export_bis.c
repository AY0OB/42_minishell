/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolavale <rolavale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 03:54:04 by amairia           #+#    #+#             */
/*   Updated: 2025/09/06 16:44:09 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_list_to_array_bis(t_env_var *var,
		char ***array, char **tmp, int i)
{
	*tmp = ft_strjoin(var->key, "=\"");
	array[0][i] = ft_strjoin(*tmp, var->value);
	free(*tmp);
	*tmp = array[0][i];
	array[0][i] = ft_strjoin(*tmp, "\"");
	free(*tmp);
}

static bool	ft_check_env_name(const char *str, t_all *all)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			all->last_exit_status = 1;
			return (true);
		}
		i++;
	}
	all->last_exit_status = 0;
	return (false);
}

t_env_var	*split_env_var(const char *arg, t_all *all)
{
	t_env_var	*var;
	char		*equal_sign;

	if (arg[0] == '=' || ft_check_env_name(arg, all) == true)
	{
		ft_putstr_fd("minishell:export: `", 2);
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (NULL);
	}
	var = ft_calloc(1, sizeof(t_env_var));
	if (!var)
		return (NULL);
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		var->key = ft_strdup(arg);
		var->value = NULL;
		return (var);
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
		if (array[i][0] != '_' || array[i][1] != '=')
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putendl_fd(array[i], STDOUT_FILENO);
		}
		i++;
	}
}
