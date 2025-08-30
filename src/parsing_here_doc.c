/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolavale <rolavale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:39:19 by amairia           #+#    #+#             */
/*   Updated: 2025/08/27 19:00:54 by rolavale         ###   ########.fr       */
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

static int	feed_fic(char *doc_stop, int fd, bool hdq)
{
	char	*line;

	signal(SIGINT, hd_ctrlc);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (aff_ctrld(doc_stop));
		if (ft_strncmp("	", line, 2) == 0)
		{
			free(line);
			return (-1);
		}
		if (ft_strncmp(doc_stop, line, ft_strlen(doc_stop) + 1) == 0)
			break ;
		if (!hdq)
			check_env_hd(&line);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	free(line);
	return (0);
}

static int	add_ficname(char *doc_stop, char **ficname, bool hdq)
{
	int		fd;

	ficname[0] = open_tmp_file();
	if (!ficname[0])
		return (-1);
	fd = open(ficname[0], O_TRUNC | O_WRONLY, S_IRWXU);
	if (feed_fic(doc_stop, fd, hdq) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	here_doc(t_pars **lst)
{
	t_pars	*tmp_lst;
	char	*ficname;
	int		check;

	check = 0;
	ficname = NULL;
	tmp_lst = *lst;
	while (tmp_lst)
	{
		if (tmp_lst->type == T_HEREDOC)
		{
			check = add_ficname(tmp_lst->next->content, &ficname,
					tmp_lst->next->hdq);
			free(tmp_lst->content);
			tmp_lst->content = ft_strdup(ficname);
			clear_doc_stop(tmp_lst);
			free(ficname);
		}
		tmp_lst = tmp_lst->next;
	}
	return (check);
}
