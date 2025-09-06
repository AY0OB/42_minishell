/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolavale <rolavale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 03:57:51 by amairia           #+#    #+#             */
/*   Updated: 2025/09/05 16:56:24 by amairia          ###   ########.fr       */
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
# include <sys/wait.h>

//--------------------------------

# define HD_END	"minishell : warning: here-document \
delimited by end-of-file (wanted '%s')\n"

extern int	g_check_ctrlc;

enum e_type
{
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_WORD,
	T_FILE,
	T_UNKNOWN,
};

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

typedef struct s_pipe_info
{
	int	last_fd;
	int	pipe_fd[2];
}				t_pipe_info;

typedef struct s_data
{
	int	pipe_done;
	int	nb_pipeline;
	int	og_in;
	int	og_out;
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
	t_pars		**lst;
	t_data		data;
	t_pipe_info	pipe_info;
	t_list		*env_list;
	bool		pipe;
	int			last_exit_status;
	bool		faile_open;
	bool		is_builtin;
	pid_t		*tab_pid;
	bool		tab_pid_check;
	int			i_pid;
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
void		free_content(void *content);

int			set_list(t_pars ***lst);
t_all		*set_struct(void);

int			first_pars(char *line, int i);
int			check_quote(char *line);

int			parsing(char *line, t_pars **lst, t_all *all);
int			verif_token(char *line, int i);

int			feed_lst_content(t_pars **lst, char *line, int *i, bool hdq);
bool		set_index(char *line, int *i, int *size, char quote);
bool		set_index_bis(char *line, int *i, int *size, bool hdq);
void		feed_lst_type(t_pars *lst, int is_token);

int			set_int_quote(t_pars *lst, char *line, int i, int j);
int			set_int_dquote(t_pars *lst, char *line, int i, int j);
int			*tmp_index(int i);
int			even_nb(int nb);

void		pars_exitcode(t_pars **lst, int exitcode, int pipe_done);

void		pars_env(t_pars **lst, t_all *all);
int			add_env(t_pars *lst, char *env_var, t_env *info);
char		*ft_getenv(char *env_name, t_list *env_list);
char		**env_list_to_array(t_list *env_list, int size);

void		feed_new_lst(t_pars *lst, char *env_var, int i);

t_envbis	set_envbis(void);
int			end_env(char *str, t_envbis info, int end_quote);
int			check_tab(int *tab, int *dtab, int len_tab);
int			check_space(char *str);

void		modif_env(char *env, int *i);
char		*set_char(int i, int j);
void		set_new_lst(t_pars **lst, t_pars **new, char *env_var, int i);

int			here_doc(t_pars **lst, t_list *env_list);
void		check_env_hd(char **line, t_list *env_list);
void		clear_doc_stop(t_pars *lst);
int			aff_ctrld(char *doc_stop);
void		hd_ctrlc(int sig);

void		skip_space(char *str, int *i);

void		clear_all(t_all *all, char *line);

char		*convert_type_to_str(enum e_type type);
void		print_debug_lst(t_pars *lst);
void		ft_exit(int cderr);

//utils
void		free_argv(char **argv);

//pathfinder
char		*get_command_path(char *cmd, t_list *env_list);

//executor
int			executor(t_all *all);
void		set_redirections(t_pars *lst, t_all *all);
void		set_redirections_pipe(t_all *all);
int			trytoopen(t_pars *lst, t_all *all, int fd);
int			check_redir(enum e_type type);
void		clear_fd(t_all *all);
int			check_redir(enum e_type type);
char		**feed_cmd(t_all *all);
void		ft_execve(t_all *all, char **cmd_path, char ***cmd);
void		builtin(t_all *all);
void		dup_redir_built(t_all *all);
int			set_redirections_pipe_bis(t_all *all);
void		set_pipe_fd(t_all *all);
void		dup_redir_pipe(t_all *all);
int			set_cmd_pipe(t_all *all, char ***cmd, char **cmd_path);
t_pars		*set_lst_place(t_all *all);
void		check_faile_and_exec(t_all *all);
void		exec_pipe(t_all *all);
void		redir_dup_exec_check_fork(t_all *all, char **cmd, pid_t *pid);
void		exec_cmd(t_all *all, char **cmd, char *cmd_path);
int			free_and_close(t_all *all, char ***cmd);

//builtins
int			execute_builtin(char **cmd, t_all *all, int exitcode);
int			is_builtin(char *cmd_name);
int			builtin_unset(char **cmd, t_list **env_list_ptr);
int			builtin_pwd(void);
int			builtin_echo(char **cmd);
int			builtin_cd(char **cmd, t_all *all);
int			builtin_env(t_list *env_list);
int			builtin_exit(char **argv, t_all *all);

//env
t_list		*init_environment(char **envp);
void		free_env_var(void *env_var_ptr);
void		print_env_var(void *env_var_ptr);
t_list		*find_env_var(t_list *env_list, const char *key);
char		**ft_get_env_array(t_list *env_list);

//export
int			builtin_export(char **cmd, t_list **env_list_ptr, t_all *all);
void		print_sorted_env(char **array);
t_env_var	*split_env_var(const char *arg, t_all *all);
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
