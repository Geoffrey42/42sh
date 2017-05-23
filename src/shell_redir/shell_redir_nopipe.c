/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redir_nopipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:46:31 by ggane             #+#    #+#             */
/*   Updated: 2017/04/20 06:51:09 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_loop_in_redir(t_var *term, int *j)
{
	while (term->redir[++(*j)])
	{
		tilde(term, &term->redir);
		if (ft_valid(term, *j) == 1)
			redir_out(term, j);
		else if (ft_valid(term, *j) == 2)
			redir_in(term, j);
		else if (ft_valid(term, *j) == 3)
		{
			if (heredoc(term, j) == 0)
				exit(0);
		}
		else if (term->redir[*j] && ft_isdigit(term->redir[*j][0]) &&
		term->redir[*j][1] == '>' && term->redir[*j][2] == '&' &&
		(term->redir[*j][3] == '-' || ft_isdigit(term->redir[*j][3])) &&
		term->redir[*j][4] == '\0')
			ft_aggreg(term->redir[*j], &term->aggreg, term);
		term->redir = ft_free_tab(term->redir);
		ft_exec(term->command, term);
	}
	init_termios(term);
}

int		ft_access_redir(t_var *term)
{
	init_termios(term);
	term->var_ret = 127;
	return (127);
}

int		ft_redir(t_var *term, int i, int j)
{
	pid_t	pid;
	int		ret;

	ret = 1;
	split_redir(term, i);
	init_std(term);
	if (term->command[0] == NULL)
		miniprintf(STDERR_FILENO, "42sh: command not found\n");
	if (term->command[0] == NULL)
		return (F);
	if (ft_is_builtin(term->command[0]) == F)
		ft_find_exec((&term->command[0]), term);
	if (term->acces == 1)
		return (ft_access_redir(term));
	if ((pid = fork()) == 0)
		ft_loop_in_redir(term, &j);
	else if (ft_is_builtin(term->command[0]) && !parent_exec(pid, &ret, term))
	{
		init_termios(term);
		return (wait(&ret));
	}
	init_termios(term);
	wait(&ret);
	ft_freetab(&(term->command));
	return (ret);
}
