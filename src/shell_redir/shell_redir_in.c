/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redir_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:19:55 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 18:06:54 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	loop_init_redir_in(t_var *term, int *j)
{
	while (term->redir[*j])
	{
		if (ft_strcmp(term->redir[*j], "<") == 0)
			term->in = *j;
		if (ft_strcmp(term->redir[*j], "1<") == 0)
			term->out = *j;
		if (ft_strcmp(term->redir[*j], "2<") == 0)
			term->err = *j;
		*j = *j + 1;
	}
}

void	fork_redir_in(t_var *term, int j)
{
	if ((ft_strcmp(term->redir[term->in], "<") == 0))
		dup2(term->fd_in, STDIN_FILENO);
	if (ft_strcmp(term->redir[term->out], "1<") == 0)
		dup2(term->fd_out, STDOUT_FILENO);
	if ((ft_strcmp(term->redir[term->err], "2<") == 0))
		dup2(term->fd_err, STDERR_FILENO);
	fd_dup(term->redir[j - 1]);
}

void	open_file_in(char **tabl, int *fd, int i)
{
	DIR	*rep;

	if ((*fd = open(tabl[i + 1], O_RDONLY)) < 0)
	{
		if (access(tabl[i + 1], F_OK) == -1)
			miniprintf(STDERR_FILENO,
				"42sh: no such file or directory: %s\n", tab[i + 1]);
		else if (access(tabl[i + 1], X_OK) == -1)
		{
			rep = opendir(tabl[i + 1]);
			if (errno == EACCES)
				miniprintf(STDERR_FILENO,
					"42sh: %s: Permission denied\n", tab[i + 1]);
			else
				miniprintf(STDERR_FILENO,
					"42sh: %s: Is a directory\n", tab[i + 1]);
			closedir(rep);
		}
		close(*fd);
		exit(-1);
	}
}

void	redir_in(t_var *term, int *j)
{
	int	i;

	term->out = 0;
	term->in = 0;
	term->err = 0;
	i = *j - 1;
	loop_init_redir_in(term, j);
	if (ft_strcmp(term->redir[term->in], "<") == 0)
		open_file_in(term->redir, &term->fd_in, term->in);
	if (ft_strcmp(term->redir[term->out], "1<") == 0)
		open_file_in(term->redir, &term->fd_out, term->out);
	if (ft_strcmp(term->redir[term->err], "2<") == 0)
		open_file_in(term->redir, &term->fd_err, term->err);
	fork_redir_in(term, *j);
	while (term->redir[i++])
		if (ft_strcmp(term->redir[i], ">") == 0)
		{
			redir_out(term, &i);
			break ;
		}
	*j = more_tall(term->out, term->in, term->err);
}
