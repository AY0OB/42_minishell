#include "../../include/minishell.h"

// sépare "KEY=VALUE" en KEY et VALUE
// retourne un t_env_var alloué. L'appelant doit le free
static t_env_var	*split_env_var(const char *arg)
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
	// on devrait vérifier les allocations de key et value
	return (var);
}

int	builtin_export(char **argv, t_list **env_list_ptr)
{
	t_env_var	*new_var;
	t_list		*existing_node;
	int			i;

	i = 1;
	while (argv[i])
	{
		new_var = split_env_var(argv[i]);
		if (!new_var)
		{
			// gérer erreur de format "export VAR"
			i++;
			continue;
		}
		existing_node = find_env_var(*env_list_ptr, new_var->key);
		if (existing_node) // maj de la var
		{
			free(((t_env_var *)existing_node->content)->value);
			((t_env_var *)existing_node->content)->value = new_var->value;
			free(new_var->key); // key useless
			free(new_var);
		}
		else // ajout de la var
			ft_lstadd_back(env_list_ptr, ft_lstnew(new_var));
		i++;
	}
	return (0);
}