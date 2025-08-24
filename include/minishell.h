/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 03:57:51 by amairia           #+#    #+#             */
/*   Updated: 2025/08/23 17:30:47 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>

//--------------------------------

# define HD_END	"minishell : warning: here-document \
delimited by end-of-file (wanted '%s')\n"

enum e_type
{
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_WORD,
	T_UNKNOWN,
};

typedef struct s_command
{
	char				**argv;
	char				*redirect_in;
	char				*redirect_out;
	char				*append_out;
	char				*heredoc_lim;
	struct s_command	*next;

}				t_command;

typedef struct s_pars
{
	char			*content;
	enum e_type		type;
	bool			hdq;
	int				*tab;
	int				*dtab;
	struct s_pars	*next;
	struct s_pars	*prev;
}				t_pars;

typedef struct s_data
{
	int	std_err;
	int	std_in;
	int	std_out;
}				t_data;

typedef struct s_env_var
{
	char	*key;
	char	*value;
}				t_env_var;

typedef struct s_all
{
	t_pars	**lst;
	t_data	data;
	t_list	*env_list;
	int		last_exit_status;
}				t_all;

typedef struct s_content
{
	char	quote;
	int		i;
	int		j;
	int		k;
	int		inclu_quote;
}				t_content;

typedef struct s_tab
{
	char	quote;
	int		i;
	int		j;
	int		in_quote;
	int		tab_i;
	int		loc_quote;
}				t_tab;

typedef struct s_env
{
	int	i;
	int	end_quote;
	int	len_base;
}				t_env;

typedef struct s_envbis
{
	int	j;
	int	k;
	int	l;
}				t_envbis;

//------------------------

t_pars		*pars_lstnew(char *content, bool hdq);
int			pars_lstadd_back(t_pars **lst, t_pars *new);
void		pars_lstclear(t_all *all);
t_pars		*pars_lstlast(t_pars *lst);
int			pars_lstsize(t_pars *lst);

int			set_list(t_pars ***lst);
t_all		*set_struct(void);

int			first_pars(char *line, int i);
int			check_quote(char *line);

int			parsing(char *line, t_pars **lst);
int			verif_token(char *line, int i);

int			feed_lst_content(t_pars **lst, char *line, int *i, bool hdq);
bool		set_index(char *line, int *i, int *size, char quote);
bool		set_index_bis(char *line, int *i, int *size, bool hdq);
void		feed_lst_type(t_pars *lst, int is_token);

int			set_int_quote(t_pars *lst, char *line, int i, int j);
int			set_int_dquote(t_pars *lst, char *line, int i, int j);
int			*tmp_index(int i);
int			even_nb(int nb);

void		pars_env(t_pars **lst);
int			add_env(t_pars *lst, char *env_var, t_env *info);

void		feed_new_lst(t_pars *lst, char *env_var, int i);

t_envbis	set_envbis(void);
int			end_env(char *str, t_envbis info, int end_quote);
int			check_tab(int *tab, int *dtab, int len_tab);
int			check_space(char *str);

void		modif_env(char *env, int *i);
char		*set_char(int i, int j);
void		set_new_lst(t_pars **lst, t_pars **new, char *env_var, int i);

int			here_doc(t_pars **lst);
void		check_env_hd(char **line);
void		clear_doc_stop(t_pars *lst);
int			aff_ctrld(char *doc_stop);
void		hd_ctrlc(int sig);

void		skip_space(char *str, int *i);

void		clear_all(t_all *all, char *line);

char		*convert_type_to_str(enum e_type type);
void		print_debug_lst(t_pars *lst);

// interpreter

t_command	**interpreter(t_pars **token);
int			handle_redirection(t_command *cmd, t_pars **token_ptr);
char		**words_to_argv(t_list *word_list);
t_command	*new_command(void);

// debug parsing interpreter

void		print_command_list(t_command *cmd_list);
void		print_argv(char **argv);

//utils
t_command	*last_command(t_command *lst);
int			add_command_back(t_command **list, t_command *new);
void		free_command_list(t_command **cmd_list);
void		free_argv(char **argv);

//executor
int			executor(t_command **cmd_list, char **envp, t_all *all);
int			handle_command_redirections(t_command **cmd);
int			execute_pipeline_check(t_command *cmd_list,
				int pipefd[2], pid_t *last_pid);
void		execute_pipeline_fd(t_command *cmd_list, int pipefd[2], int *in_fd);
void		child_process(t_command *cmd, char **envp,
				int fd[2], t_all *all);

//pathfinder
char		*get_command_path(char *cmd, char **envp);

//builtins
int			execute_builtin(t_command **cmd, t_all *all);
int			is_builtin(char *cmd_name);
int			builtin_unset(char **argv, t_list **env_list_ptr);
int			builtin_pwd(void);
int			builtin_echo(char **argv, int exit_code);
int			builtin_cd(char **argv, t_all *all);
int			builtin_env(t_list *env_list);
int			builtin_exit(char **argv, t_all *all, t_command **cmd);

//env
t_list		*init_environment(char **envp);
void		free_env_var(void *env_var_ptr);
void		print_env_var(void *env_var_ptr);
t_list		*find_env_var(t_list *env_list, const char *key);

//export
int			builtin_export(char **argv, t_list **env_list_ptr);
void		print_sorted_env(char **array);
t_env_var	*split_env_var(const char *arg);
void		env_list_to_array_bis(t_env_var *var,
				char ***array, char **tmp, int i);

//unset
int			builtin_unset(char **argv, t_list **env_list_ptr);

//expender
char		*expand_and_clean_word(char *word, t_all *all);

// signals.c
void		setup_interactive_mode(void);
void		setup_execution_mode(void);

#endif
