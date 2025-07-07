#include "../include/minishell.h"

void	print_argv(char **argv)
{
	int	i;

	ft_printf("  - argv: [");
	if (argv == NULL)
	{
		ft_printf("NULL");
	}
	else
	{
		i = 0;
		while (argv[i] != NULL)
		{
			ft_printf("'%s'", argv[i]);
			if (argv[i + 1] != NULL)
			{
				ft_printf(", ");
			}
			i++;
		}
	}
	ft_printf("]\n");
}

void print_command_list(t_command *cmd_list)
{

	t_command	*current;
	int		i;

	current = cmd_list;
	i = 0;
	ft_printf("--- [DEBUG] Liste des commands parsés ---\n");
	if (current == NULL)
	{
		ft_printf("(Liste vide)\n");
		ft_printf("----------------------------------------\n");
		return;
	}
	while (current != NULL)
	{
		ft_printf("Command #%d:\n", i);
		print_argv(current->argv);
		ft_printf("  - redirect_in : %s\n", current->redirect_in);
		ft_printf("  - redirect_out : %s\n", current->redirect_out);
		ft_printf("  - append_out : %s\n", current->append_out);
		ft_printf("  - heredoc_lim : %s\n", current->heredoc_lim);
		ft_printf("\n");

		current = current->next;
		i++;
	}
	ft_printf("----------------------------------------\n");

};