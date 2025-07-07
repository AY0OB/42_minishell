/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:12:40 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 20:13:07 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_debug_lst(t_pars *lst)
{
	t_pars	*current;
	int		i;

	current = lst;
	i = 0;
	ft_printf("--- [DEBUG] Liste des tokens parsés ---\n");
	if (current == NULL)
	{
		ft_printf("(Liste vide)\n");
		ft_printf("----------------------------------------\n");
		return ;
	}
	while (current != NULL)
	{
		ft_printf("Token #%d:\n", i);
		ft_printf("  - Contenu : [%s]\n", current->content);
		ft_printf("  - Type    : %s\n", convert_type_to_str(current->type));
		ft_printf("\n");
		current = current->next;
		i++;
	}
	ft_printf("----------------------------------------\n");
}
