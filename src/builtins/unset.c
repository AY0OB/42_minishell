/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:42:37 by amairia           #+#    #+#             */
/*   Updated: 2025/07/20 16:57:13 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	unset_bis(t_list **env_list_ptr, t_list *current, t_list *prev)
{
	if (prev == NULL)
		*env_list_ptr = current->next;
	else
		prev->next = current->next;
	ft_lstdelone(current, free_env_var);
}

int	builtin_unset(char **argv, t_list **env_list_ptr)
{
	t_list	*current;
	t_list	*prev;
	int		i;

	i = 1;
	while (argv[i])
	{
		current = *env_list_ptr;
		prev = NULL;
		while (current)
		{
			if (ft_strncmp(((t_env_var *)current->content)->key,
					argv[i], ft_strlen(argv[i]) + 1) == 0)
			{
				unset_bis(env_list_ptr, current, prev);
				/*if (prev == NULL)
					*env_list_ptr = current->next;
				else
					prev->next = current->next;
				ft_lstdelone(current, free_env_var);*/
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}
