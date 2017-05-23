/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redir_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:23:59 by ggane             #+#    #+#             */
/*   Updated: 2017/04/24 04:19:35 by piranucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		fd_dup(char *str)
{
	if ((ft_strcmp(str, "2>&1") == 0) || (ft_strcmp(str, "1<&2") == 0))
		dup2(STDOUT_FILENO, STDERR_FILENO);
	else if ((ft_strcmp(str, "1>&2") == 0) || (ft_strcmp(str, "2<&1") == 0))
		dup2(STDERR_FILENO, STDOUT_FILENO);
	else if ((ft_strcmp(str, "1>&0") == 0) || (ft_strcmp(str, "0<&1") == 0))
		dup2(STDIN_FILENO, STDOUT_FILENO);
	else if ((ft_strcmp(str, "0>&1") == 0) || (ft_strcmp(str, "1<&0") == 0))
		dup2(STDOUT_FILENO, STDIN_FILENO);
	else if ((ft_strcmp(str, "2>&0") == 0) || (ft_strcmp(str, "0<&2") == 0))
		dup2(STDIN_FILENO, STDERR_FILENO);
	else if ((ft_strcmp(str, "0>&2") == 0) || (ft_strcmp(str, "2<&0") == 0))
		dup2(STDERR_FILENO, STDIN_FILENO);
	else if ((ft_strcmp(str, "0>&-") == 0) || (ft_strcmp(str, "0<&-") == 0)
			|| (ft_strcmp(str, "<&-") == 0))
		close(STDIN_FILENO);
	else if ((ft_strcmp(str, "1>&-") == 0) || (ft_strcmp(str, "1<&-") == 0))
		close(STDOUT_FILENO);
	else if ((ft_strcmp(str, "2>&-") == 0) || (ft_strcmp(str, "2<&-") == 0))
		close(STDERR_FILENO);
	else
		return (-1);
	return (1);
}

void	fork_redir_out(t_var *term, int j)
{
	if ((ft_strcmp(term->redir[term->out], ">") == 0) ||
			(ft_strcmp(term->redir[term->out], ">>") == 0))
		dup2(term->fd_out, STDOUT_FILENO);
	if ((ft_strcmp(term->redir[term->in], "0>") == 0) ||
			(ft_strcmp(term->redir[term->in], "0>>") == 0))
		dup2(term->fd_in, STDIN_FILENO);
	if ((ft_strcmp(term->redir[term->err], "2>") == 0) ||
			(ft_strcmp(term->redir[term->err], "2>>") == 0))
		dup2(term->fd_err, STDERR_FILENO);
	fd_dup(term->redir[j - 1]);
}

void	loop_init_redir(t_var *term, int *j)
{
	while (term->redir[*j])
	{
		if ((ft_strcmp(term->redir[*j], ">") == 0) ||
				(ft_strcmp(term->redir[*j], ">>") == 0))
		{
			term->out = *j;
			term->red = 1;
		}
		if ((ft_strcmp(term->redir[*j], "2>") == 0) ||
				(ft_strcmp(term->redir[*j], "2>>") == 0))
		{
			term->err = *j;
			term->red = 2;
		}
		if ((ft_strcmp(term->redir[*j], "0>") == 0) ||
				(ft_strcmp(term->redir[*j], "0>>") == 0))
			term->in = *j;
		*j = *j + 1;
	}
}

void	open_file_out(char **tabl, int *fd, int i, int flag)
{
	DIR	*rep;

	if (tabl[i + 1][0] == '$')
		return ;
	if ((*fd = open(tabl[i + 1], O_WRONLY | O_CREAT | flag, 0644)) < 0)
	{
		if (errno == EISDIR)
			miniprintf(STDERR_FILENO, "42sh %s: Is a directory\n", tabl[i + 1]);
		else if (access(tabl[i + 1], F_OK) == -1)
			miniprintf(STDERR_FILENO,
			"no such file or directory: %s\n", tabl[i + 1]);
		else if (access(tabl[i + 1], X_OK) == -1)
		{
			rep = opendir(tabl[i + 1]);
			if (errno == EACCES)
				miniprintf(STDERR_FILENO,
					"42sh: %s: permission denied\n", tabl[i + 1]);
			else
				miniprintf(STDERR_FILENO,
					"42sh: %s: Is a directory\n", tabl[i + 1]);
			closedir(rep);
		}
		close(*fd);
		return ;
	}
}

void	redir_out(t_var *term, int *j)
{
	term->out = 0;
	term->in = 0;
	term->err = 0;
	loop_init_redir(term, j);
	if (ft_strcmp(term->redir[term->out], ">") == 0)
		open_file_out(term->redir, &term->fd_out, term->out, O_TRUNC);
	if (ft_strcmp(term->redir[term->out], ">>") == 0)
		open_file_out(term->redir, &term->fd_out, term->out, O_APPEND);
	if (ft_strcmp(term->redir[term->err], "2>") == 0)
		open_file_out(term->redir, &term->fd_err, term->err, O_TRUNC);
	if (ft_strcmp(term->redir[term->err], "2>>") == 0)
		open_file_out(term->redir, &term->fd_err, term->err, O_APPEND);
	if (ft_strcmp(term->redir[term->in], "0>") == 0)
		open_file_out(term->redir, &term->fd_in, term->in, O_TRUNC);
	if (ft_strcmp(term->redir[term->in], "0>>") == 0)
		open_file_out(term->redir, &term->fd_in, term->in, O_APPEND);
	fork_redir_out(term, *j);
	*j = more_tall(term->out, term->in, term->err);
}
