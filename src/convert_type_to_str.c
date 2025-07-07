/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_type_to_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:35:37 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:36:07 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*convert_type_to_str(enum e_type type)
{
	switch (type)
	{
		case T_WORD:
			return ("WORD");
		case T_PIPE:
			return ("PIPE");
		case T_REDIR_IN:
			return ("REDIR_IN");
		case T_REDIR_OUT:
			return ("REDIR_OUT");
		case T_APPEND:
			return ("APPEND");
		case T_HEREDOC:
			return ("HERE_DOC");
		default :
			return ("INCONNU");
	}
}
