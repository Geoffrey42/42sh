/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redir_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:14:00 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 18:08:28 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	suite_loop_redir(t_var *term, int *i, int *a, int *b)
{
	int		booleen;
	char	car;

	condition_loop(term, a, b);
	booleen = 0;
	while (term->pipe[term->i][(*i)])
	{
		if (((term->pipe[term->i][(*i)] == '\"' && booleen == 0) ||
					(term->pipe[term->i][(*i)] == '\"' && booleen == 0)) &&
				(car = term->pipe[term->i][(*i)]))
			booleen = 1;
		else if ((booleen == 1 && term->pipe[term->i][(*i)] == car))
			booleen = 0;
		else if (((term->pipe[term->i][(*i)] == '<') ||
					(term->pipe[term->i][(*i)] == ' ') ||
					(term->pipe[term->i][(*i)] == '>')) && booleen == 0)
			break ;
		else if ((term->redir[*a][*b] = term->pipe[term->i][(*i)]))
			*b = *b + 1;
		(*i) = (*i) + 1;
	}
	condition_loop(term, a, b);
	if (term->pipe[term->i][(*i)] && term->pipe[term->i][(*i)] == ' ')
		(*i) = (*i) + 1;
}

void	condition_redir(t_var *term, int *i, int *a, int *b)
{
	if (((term->pipe[term->i][(*i)] == '0') || (term->pipe[term->i][(*i)] ==
	'1') || (term->pipe[term->i][(*i)] == '2')) && ((term->pipe[term->i][(*i)
	+ 1] == '>') || (term->pipe[term->i][(*i) + 1] == '<')))
	{
		term->redir[*a][*b] = term->pipe[term->i][(*i)];
		*b = *b + 1;
		(*i) = (*i) + 1;
	}
	while ((term->pipe[term->i][(*i)] && term->pipe[term->i][(*i)] == '<')
			|| (term->pipe[term->i][(*i)] && term->pipe[term->i][(*i)] == '>'))
	{
		term->redir[*a][*b] = term->pipe[term->i][(*i)];
		*b = *b + 1;
		(*i) = (*i) + 1;
	}
}

void	loop_redir(t_var *term, int index, int i)
{
	int		a;
	int		b;
	int		tmp;

	a = 0;
	b = 0;
	tmp = term->i;
	term->i = index;
	while (term->pipe[index][i])
	{
		condition_redir(term, &i, &a, &b);
		if (((term->pipe[index][i - 1] == '>') || (term->pipe[index][i - 1] ==
		'<')) && term->pipe[index][i] == '&' && ((term->pipe[index][i + 1] ==
		'-') || (term->pipe[index][i + 1] == '0') || (term->pipe[index][i + 1]
		== '1') || (term->pipe[index][i + 1] == '2')))
		{
			term->redir[a][b++] = term->pipe[index][i++];
			term->redir[a][b++] = term->pipe[index][i++];
		}
		suite_loop_redir(term, &i, &a, &b);
	}
	while (term->redir[a])
		term->redir[a++][0] = '\0';
	term->i = tmp;
}

int		loop_back_redir(t_var *term, int index, int i)
{
	char	car;
	int		booleen;

	booleen = 0;
	while (term->pipe[index][i])
	{
		if ((term->pipe[index][i] == '\"' && booleen == 0) ||
				(term->pipe[index][i] == '\"' && booleen == 0))
		{
			car = term->pipe[index][i];
			booleen = 1;
		}
		else if ((booleen == 1 && term->pipe[index][i] == car))
			booleen = 0;
		else if (((term->pipe[index][i] == '<') ||
					(term->pipe[index][i] == '>')) && booleen == 0)
			break ;
		i++;
	}
	return (i);
}

void	split_redir(t_var *term, int index)
{
	int		i;
	char	*tmp;

	i = 0;
	ft_count_tab(term, i);
	term->command = ft_free_tab(term->command);
	i = loop_back_redir(term, index, i);
	if ((term->pipe[index][i - 1] == '0') || (term->pipe[index][i - 1] == '1')
	|| (term->pipe[index][i - 1] == '2'))
		i--;
	tmp = strndup(term->pipe[index], i);
	term->command = split_qte(tmp);
	free(tmp);
	loop_redir(term, index, i);
}
