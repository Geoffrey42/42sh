/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:31:02 by ggane             #+#    #+#             */
/*   Updated: 2017/04/25 00:54:08 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_count_tab(t_var *term, int index)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (term->pipe[index][i])
	{
		if ((term->pipe[index][i] == '>') || (term->pipe[index][i] == '<') ||
				(term->pipe[index][i] == ' '))
			count++;
		i++;
	}
	term->redir = (char**)malloc(sizeof(char*) * (count + 1));
	i = 0;
	while (i < count)
		term->redir[i++] = (char*)malloc(sizeof(char) * (count + 1));
	term->redir[i] = NULL;
	term->count_redir = count;
}

int		ft_valid(t_var *term, int i)
{
	if ((ft_strcmp(term->redir[i], ">") == 0) ||
			(ft_strcmp(term->redir[i], ">>") == 0) ||
			(ft_strcmp(term->redir[i], "0>") == 0) ||
			(ft_strcmp(term->redir[i], "1>") == 0) ||
			(ft_strcmp(term->redir[i], "2>") == 0) ||
			(ft_strcmp(term->redir[i], "0>>") == 0) ||
			(ft_strcmp(term->redir[i], "1>>") == 0) ||
			(ft_strcmp(term->redir[i], "2>>") == 0))
		return (1);
	else if ((ft_strcmp(term->redir[i], "<") == 0) ||
			(ft_strcmp(term->redir[i], "1<") == 0) ||
			(ft_strcmp(term->redir[i], "2<") == 0) ||
			(ft_strcmp(term->redir[i], "<&-") == 0))
		return (2);
	else if ((ft_strcmp(term->redir[i], "<<") == 0) ||
			(ft_strcmp(term->redir[i], "1<<") == 0) ||
			(ft_strcmp(term->redir[i], "2<<") == 0))
		return (3);
	return (0);
}

int		more_tall(int out, int in, int err)
{
	if (out >= in && out >= err)
		return (out + 1);
	if (in >= out && in >= err)
		return (in + 1);
	if (err >= in && err >= out)
		return (err + 1);
	return (0);
}

void	ft_free_split(t_var *term, int i)
{
	int	k;

	k = -1;
	if (term->redir != NULL)
	{
		while (++k < term->count_redir)
			free(term->redir[k]);
		free(term->redir);
	}
	split_redir(term, i);
}

void	redir_pipe(t_var *term, int i)
{
	int	j;

	ft_free_split(term, i);
	j = -1;
	while (term->redir[++j] != NULL)
	{
		(ft_valid(term, j) == 4) ? term->repeat = 1 : (0);
		if (ft_valid(term, j) == 4)
			return ;
		if ((term->pipe_out || term->pipe_end) && term->pipe_in)
			return ;
		else if (ft_valid(term, j) == 1)
			redir_out(term, &j);
		else if (ft_valid(term, j) == 2)
			redir_in(term, &j);
		else if (ft_valid(term, j) == 3 && (term->hdc = 1))
			(heredoc(term, &j)) == 0 ? exit(0) : (0);
		else if (term->redir[j] && ft_isdigit(term->redir[j][0]) &&
		term->redir[j][1] == '>' && term->redir[j][2] == '&' &&
		(term->redir[j][3] == '-' || ft_isdigit(term->redir[j][3])) &&
		term->redir[j][4] == '\0')
			ft_aggreg(term->redir[j], &term->aggreg, term);
	}
}
