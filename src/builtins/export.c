/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:40:33 by amairia           #+#    #+#             */
/*   Updated: 2025/08/21 21:31:46 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_list_to_array(t_list *env_list, int size)
{
	char		**array;
	int			i;
	t_env_var	*var;
	char		*tmp;

	array = ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	tmp = NULL;
	i = 0;
	while (env_list)
	{
		var = (t_env_var *)env_list->content;
		if (var->value)
		{
			env_list_to_array_bis(var, &array, &tmp, i);
		}
		else
			array[i] = ft_strdup(var->key);
		env_list = env_list->next;
		i++;
	}
	return (array);
}

static void	sort_env_array(char **array, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(array[j], array[j + 1], -1) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	display_sorted_env(t_list *env_list)
{
	char	**array;
	int		size;

	size = ft_lstsize(env_list);
	if (size == 0)
		return (0);
	array = env_list_to_array(env_list, size);
	if (!array)
		return (1);
	sort_env_array(array, size);
	print_sorted_env(array);
	free_argv(array);
	return (0);
}

static int	export_bis(t_env_var *new_var, int *i)
{
	if (!new_var)
	{
		++*i;
		return (-1);
	}
	return (0);
}

int	builtin_export(char **argv, t_list **env_list_ptr, t_all *all)
{
	t_env_var	*new_var;
	t_list		*existing_node;
	int			i;

	if (!argv[1])
		return (display_sorted_env(*env_list_ptr));
	i = 1;
	while (argv[i])
	{
		new_var = split_env_var(argv[i], all);
		if (export_bis(new_var, &i) == -1)
			continue ;
		existing_node = find_env_var(*env_list_ptr, new_var->key);
		if (existing_node)
		{
			free(((t_env_var *)existing_node->content)->value);
			((t_env_var *)existing_node->content)->value = new_var->value;
			free(new_var->key);
			free(new_var);
		}
		else
			ft_lstadd_back(env_list_ptr, ft_lstnew(new_var));
		i++;
	}
	return (0);
}
