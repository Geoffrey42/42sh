/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 01:29:52 by lprunier          #+#    #+#             */
/*   Updated: 2017/04/25 01:31:24 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_multiple_opt(char **text, t_var *term, int *j)
{
	(void)text;
	if ((term->hdc_result = loop_init_heredoc(term, j)) == NULL)
	{
		free(term->tmp);
		return (0);
	}
	if ((!ft_strcmp(term->redir[2], ">") || !ft_strcmp(term->redir[2], ">>"))
			&& term->ifpipe == 0)
	{
		term->truc = 1;
		redir_out(term, j);
	}
	return (5);
}

void	ft_hdc_out(t_var *term, int fd_tab[2], char *text)
{
	int		fd;
	int		fd_bis;
	char	buf[2];
	char	*tmp;

	tmp = ft_strdup("\0");
	close(fd_tab[0]);
	if (!ft_strcmp(term->redir[4], ">>"))
		fd = open(term->redir[5], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(term->redir[5], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, text, ft_strlen(text));
	if (!ft_strcmp(term->redir[2], "<"))
	{
		fd_bis = open(term->redir[3], O_RDONLY);
		while (read(fd_bis, buf, 1))
		{
			tmp = ft_strjoin(tmp, buf);
			ft_bzero(buf, 2);
		}
		write(fd, tmp, ft_strlen(tmp));
		close(fd_bis);
		close(fd);
	}
}
