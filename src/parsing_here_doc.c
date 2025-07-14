/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:39:19 by amairia           #+#    #+#             */
/*   Updated: 2025/07/11 15:08:03 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*set_ficname(void)
{
	char	*ficname;

	ficname = ft_calloc(sizeof(char), 17);
	if (!ficname)
	{
		ft_printf("Alloc error\n");
		return (NULL);
	}
	ft_memset(ficname, '0', 16);
	ficname[0] = '/';
	ficname[1] = 't';
	ficname[2] = 'm';
	ficname[3] = 'p';
	ficname[4] = '/';
	ficname[5] = 'h';
	ficname[6] = 'd';
	return (ficname);
}

static char	*open_tmp_file(void)
{
	int		fd;
	int		i;
	char	*ficname;

	ficname = set_ficname();
	if (!ficname)
		return (NULL);
	i = 15;
	fd = open(ficname, O_EXCL | O_CREAT, S_IRWXU);
	while (fd == -1 && i > 1)
	{
		if (ficname[i] == '9')
			i--;
		ficname[i] += 1;
		fd = open(ficname, O_EXCL | O_CREAT, S_IRWXU);
	}
	if (fd > 2)
		close(fd);
	return (ficname);
}

static	int	feed_fic(char *doc_stop, int fd)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		close(fd);
		return (-1);
	}
	while (ft_strncmp((const char *)doc_stop,
			(const char *)line, ft_strlen(line)) != 0)
	{
		check_env_hd(&line);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline("> ");
		if (!line)
		{
			close(fd);
			return (-1);
		}
	}
	free(line);
	return (0);
}

static char	*add_ficname(char *doc_stop)
{
	int		fd;
	char	*ficname;

	ficname = open_tmp_file();
	if (!ficname)
		return (NULL);
	fd = open(ficname, O_TRUNC | O_WRONLY, S_IRWXU);
	if (feed_fic(doc_stop, fd) == -1)
	{
		free(ficname);
		return (NULL);
	}
	close(fd);
	return (ficname);
}

int	here_doc(t_pars **lst)
{
	t_pars	*tmp_lst;

	tmp_lst = *lst;
	while (tmp_lst)
	{
		if (tmp_lst->type == T_HEREDOC)
		{
			free(tmp_lst->content);
			tmp_lst->content = add_ficname(tmp_lst->next->content);
			if (tmp_lst->content == NULL)
				return (-1);
			clear_doc_stop(tmp_lst);
		}
		tmp_lst = tmp_lst->next;
	}
	return (0);
}
