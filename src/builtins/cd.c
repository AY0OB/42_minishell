/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:36:51 by amairia           #+#    #+#             */
/*   Updated: 2025/07/29 18:39:32 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	update_env_var(t_list **env_list,
		const char *key, const char *value)
{
	t_list		*node;
	t_env_var	*new_var;

	node = find_env_var(*env_list, key);
	if (node)
	{
		free(((t_env_var *)node->content)->value);
		((t_env_var *)node->content)->value = ft_strdup(value);
	}
	else
	{
		new_var = ft_calloc(1, sizeof(t_env_var));
		if (!new_var)
			return ;
		new_var->key = ft_strdup(key);
		new_var->value = ft_strdup(value);
		ft_lstadd_back(env_list, ft_lstnew(new_var));
	}
}

static int	cd_bis(t_all **all, char *old_pwd, char *new_pwd)
{
	if (getcwd(new_pwd, PATH_MAX) == NULL)
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	update_env_var(&(all[0]->env_list), "OLDPWD", old_pwd);
	update_env_var(&(all[0]->env_list), "PWD", new_pwd);
	return (0);
}

int	builtin_cd(char **argv, t_all *all)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (!argv[1])
		return (0);
	if (argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (getcwd(old_pwd, PATH_MAX) == NULL)
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	/*
	if (getcwd(new_pwd, PATH_MAX) == NULL)
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	update_env_var(&all->env_list, "OLDPWD", old_pwd);
	update_env_var(&all->env_list, "PWD", new_pwd);
	return (0);*/
	return (cd_bis(&all, old_pwd, new_pwd)); // ICI
}
