/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:37:44 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:38:01 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// fonction pour libérer un maillon de notre environnement
void	free_env_var(void *env_var_ptr)
{
	t_env_var	*var;

	if (!env_var_ptr)
		return ;
	var = (t_env_var *)env_var_ptr;
	free(var->key);
	free(var->value);
	free(var);
}

// initialise notre liste d'environnement à partir de l'envp
t_list	*init_environment(char **envp)
{
	t_list		*env_list;
	t_env_var	*var;
	char		*equal_sign;
	int			i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		var = ft_calloc(1, sizeof(t_env_var));
		if (!var)
			return (NULL); // gérer l'erreur d'allocation
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			var->key = ft_substr(envp[i], 0, equal_sign - envp[i]);
			var->value = ft_strdup(equal_sign + 1);
		}
		ft_lstadd_back(&env_list, ft_lstnew(var));
		i++;
	}
	return (env_list);
}

/*
** cherche une variable d'environnement par sa clé dans la liste
** retourne un pointeur sur le maillon t_list correspondant si trouvé
** sinon, retourne NULL
*/
t_list	*find_env_var(t_list *env_list, const char *key)
{
	t_env_var	*current_var;

	while (env_list)
	{
		current_var = (t_env_var *)env_list->content;
		if (ft_strncmp(current_var->key, key, ft_strlen(key) + 1) == 0)
			return (env_list); // on retourne le maillon, pas juste le contenu
		env_list = env_list->next;
	}
	return (NULL);
}
