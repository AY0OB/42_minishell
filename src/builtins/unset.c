#include "../../include/minishell.h"

// TODO: utiliser ft_lstremove_if
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
			if (ft_strncmp(((t_env_var*)current->content)->key, argv[i], ft_strlen(argv[i]) + 1) == 0)
			{
				if (prev == NULL) // pn supprime le premier élément
					*env_list_ptr = current->next;
				else // on supprime un élément au milieu ou à la fin
					prev->next = current->next;
				ft_lstdelone(current, free_env_var);
				break; // on a trouvé et supprimé, on passe à l'arg suivant
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}