#include "../include/minishell.h"

static t_command	*parse_single_command(t_pars **token_stream);


t_command	*interpreter(t_pars *tokens)
{
	t_pars		*current_token;
	t_command	*cmd_list_head;
	t_command	*new_cmd;

	current_token = tokens;
	cmd_list_head = NULL;
	while (current_token)
	{
		new_cmd = parse_single_command(&current_token);
		if (!new_cmd)
		{
			free_command_list(cmd_list_head); // nettoyer en cas d'erreur
			return (NULL);
		}
		add_command_back(&cmd_list_head, new_cmd);
		if (current_token && current_token->type == T_PIPE)
			current_token = current_token->next;
	}
	return (cmd_list_head);
}

static t_command	*parse_single_command(t_pars **token_stream)
{
	t_command	*cmd;
	t_list		*word_list;
	char		*word_copy;

	cmd = new_command();
	if (!cmd)
		return (NULL);
	word_list = NULL;
	while (*token_stream && (*token_stream)->type != T_PIPE)
	{
		if ((*token_stream)->type >= T_REDIR_IN
			&& (*token_stream)->type <= T_HEREDOC)
		{
			if (handle_redirection(cmd, token_stream) != 0)
				return (NULL); // free cmd todo
		}
		else if ((*token_stream)->type == T_WORD)
		{
			word_copy = ft_strdup((*token_stream)->content);
			ft_lstadd_back(&word_list, ft_lstnew(word_copy));
		}
		*token_stream = (*token_stream)->next;
	}
	if (word_list)
	{
		cmd->argv = words_to_argv(word_list);
		ft_lstclear(&word_list, NULL);
	}
	return (cmd);
}

int handle_redirection(t_command *cmd, t_pars **token_ptr)
{
	enum e_type	redir_type;
	t_pars		*filename_token;

	redir_type = (*token_ptr)->type;

	*token_ptr = (*token_ptr)->next;

	filename_token = *token_ptr;
	if (filename_token == NULL || filename_token->type != T_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (-1);
	}

	// fill cmd with redir type
	if (redir_type == T_REDIR_OUT)
		cmd->redirect_out = ft_strdup(filename_token->content);
	else if (redir_type == T_REDIR_IN)
		cmd->redirect_in = ft_strdup(filename_token->content);
	else if (redir_type == T_APPEND)
		cmd->append_out = ft_strdup(filename_token->content);
	else if (redir_type == T_HEREDOC)
		cmd->heredoc_lim = ft_strdup(filename_token->content);

	return (0);

};

char **words_to_argv(t_list *word_list)
{
	int		count;
	char	**argv;
	int		i;
	t_list 	*current_node;

	count = ft_lstsize(word_list);
	argv = ft_calloc(count + 1, sizeof(char *)); //+1 car null à la fin
	if (argv == NULL)
		return(NULL);

	i = 0;
	current_node = word_list;
	while (current_node)
	{
        ft_printf("words_to_argv: Ajout de '%s' à argv[%d]\n", (char *)current_node->content, i);
		argv[i] = (char *)current_node->content;
		i++;
		current_node = current_node->next;
	}
	return (argv);
};