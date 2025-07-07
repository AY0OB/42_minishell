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
		default:
			return ("INCONNU");
	}
}