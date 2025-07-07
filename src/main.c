/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:06:25 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:43:30 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	compare_line_set(const char *line, char *line_set, int i, int j)
{
	if (j == 4)
	{
		if ((line_set[0] == 'e' && line_set[1] == 'x'
				&& line_set[2] == 'i' && line_set[3] == 't')
			&& (((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
				|| line[i] == '\n' || !line[i]))
			return (0);
	}
	return (1);
}

static int	test_end(const char *line)
{
	char	*line_set;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!line)
		return (0);
	line_set = ft_calloc(sizeof(char), 4);
	while (line[i] && j < 4)
	{
		if ((line[i] < 9 || line[i] > 13) && line[i] != 32)
		{
			line_set[j] = line[i];
			j++;
		}
		i++;
	}
	j = compare_line_set(line, line_set, i, j);
	free(line_set);
	return (j);
}

static int	set_list(t_pars ***lst)
{
	*lst = NULL;
	*lst = malloc(sizeof(t_pars *));
	if (!(*lst))
	{
		ft_printf("Alloc error\n");
		return (-1);
	}
	**lst = NULL;
	return (0);
}

static t_all	*set_struct(void)
{
	t_all		*all;
	t_pars		**lst;

	all = malloc(sizeof(t_all));
	if (!all)
	{
		ft_putstr_fd("Alloc error\n", STDOUT_FILENO);
		return (NULL);
	}
	if (set_list(&lst) == -1)
	{
		free(all);
		return (NULL);
	}
	all->lst = lst;
	all->data.std_err = 0;
	all->data.std_in = 0;
	all->data.std_out = 1;
	all->env_list = NULL;
	return (all);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_all		*all;
	t_pars		**tokens;
	t_command	*commands;

	(void)argc;
	(void)argv;
	all = set_struct();
	if (!all)
		return (-1);
	all->env_list = init_environment(envp); // init env
	tokens = all->lst; // lisibilité, marre de se trimballer cette merde partout
	while (1)
	{
		line = readline("minishell ");
		if (line)
			add_history((const char *)line);
		if (test_end((const char *)line) != 1)
			break ;
		if (first_pars(line) == 1 && check_quote(line) == 1)
		{
			parsing(line, tokens); //lexer, mots, redir
			commands = interpreter(*tokens); // Parsing
			print_command_list(commands); // ça bug ?
			executor(commands, envp, all); // on lance des trucs et des machins
			// free_command_list(commands); // on nettoie
		}
		if (line)
			free(line);
		pars_lstclear(all->lst);
	}
	clear_all(all, line);
	return (0);
}
