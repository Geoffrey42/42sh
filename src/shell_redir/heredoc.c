/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:51:24 by ggane             #+#    #+#             */
/*   Updated: 2017/04/25 01:32:58 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_fd_neg(t_var *term, int fd)
{
	DIR		*rep;

	if (errno == EISDIR)
		miniprintf(STDERR_FILENO, "42sh %s: Is a directory\n", term->redir[3]);
	else if (access(term->redir[3], F_OK) == -1)
		miniprintf(STDERR_FILENO,
				"no such file or directory: %s\n", term->redir[3]);
	else if (access(term->redir[3], X_OK) == -1)
	{
		rep = opendir(term->redir[3]);
		if (errno == EACCES)
			miniprintf(STDERR_FILENO,
					"42sh: %s: permission denied\n", term->redir[3]);
		else
			miniprintf(STDERR_FILENO,
					"42sh: %s: Is a directory\n", term->redir[3]);
		closedir(rep);
	}
	close(fd);
}

void	ft_err_direct(int opt, DIR *rep, char *s)
{
	if (opt == 0)
		miniprintf(STDERR_FILENO, "42sh: %s: Is a directory.\n", s);
	else
		miniprintf(STDERR_FILENO, "42sh: Argument invalid.\n");
	closedir(rep);
	return ;
}

void	ft_hdc_read(t_var *term, int fd_tab[2])
{
	int		fd;
	char	*tmp;
	DIR		*rep;

	tmp = ft_strdup("\0");
	if ((fd = open(term->redir[3], O_RDONLY)) < 0)
		ft_fd_neg(term, fd);
	else if (access(term->redir[3], X_OK) == -1)
	{
		rep = opendir(term->redir[3]);
		if (errno == EISDIR)
			return (ft_err_direct(0, rep, term->redir[3]));
		if (errno == EINVAL)
			return (ft_err_direct(1, rep, NULL));
		else
		{
			while (get_next_line(fd, &tmp))
				miniprintf(fd_tab[1], tmp);
			closedir(rep);
			close(fd);
		}
	}
	else if (errno == EISDIR || errno == EINVAL)
		term->error_hdc = 1;
}

void	ft_pid_null_hdc(t_var *term, int fd_tab[2], char *text)
{
	if (!ft_strcmp(term->redir[4], ">") || (!ft_strcmp(term->redir[4], ">>")))
		ft_hdc_out(term, fd_tab, text);
	else
	{
		dup2(fd_tab[1], STDOUT_FILENO);
		close(fd_tab[0]);
		ft_putstr_fd(text, fd_tab[1]);
		if (!ft_strcmp(term->redir[2], "<"))
			ft_hdc_read(term, fd_tab);
		if (term->error_hdc)
		{
			miniprintf(STDERR_FILENO, "42sh: stdin: Is a directory.\n");
			exit(1);
		}
		exit(0);
	}
	exit(0);
}

int		heredoc(t_var *term, int *j)
{
	pid_t	pid;
	char	*text;
	int		fd_tab[2];
	int		status;

	ft_init_heredoc(term);
	if (ft_multiple_opt(&text, term, j) == 0)
		return (0);
	if ((!term->hdc || ((term->hdc && term->numredir == 0) && term->truc == 0))
			&& !term->ifpipe)
	{
		pipe(fd_tab);
		((pid = fork()) > 0) ? waitpid(-1, &status, 0) : (0);
		(pid == 0) ? ft_pid_null_hdc(term, fd_tab, term->hdc_result) : (0);
		dup2(fd_tab[0], STDIN_FILENO);
		term->red = fd_tab[0];
		term->her = fd_tab[1];
		close(fd_tab[1]);
		return (1);
	}
	else
	{
	}
	return (1);
}
