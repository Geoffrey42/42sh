/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:05:04 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:58:24 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_add_history(char *s, t_hist **h)
{
	t_hist	*tmp;

	if (*h == NULL)
	{
		*h = (t_hist *)malloc(sizeof(t_hist));
		(*h)->s = ft_strdup(s);
		(*h)->end = 1;
		(*h)->prev = NULL;
		(*h)->next = NULL;
	}
	else if ((*h)->end == 1 && ft_strcmp(s, (*h)->s))
	{
		tmp = *h;
		*h = (t_hist *)malloc(sizeof(t_hist));
		(*h)->s = ft_strdup(s);
		(*h)->end = 1;
		tmp->prev = *h;
		(*h)->next = tmp;
		(*h)->prev = NULL;
	}
	else if ((*h)->end == 0 && (*h)->end++ >= -1)
	{
		free((*h)->s);
		(*h)->s = ft_strdup(s);
	}
}

int		ft_history(t_hist *h)
{
	int	i;

	i = 0;
	while (h && h->next)
		h = h->next;
	while (h && h->prev)
	{
		(h->end == 1) ? miniprintf(STDOUT_FILENO, "%d  %s\n", i, h->s) : (0);
		(h->end == 1) ? i++ : (0);
		h = h->prev;
	}
	(h->end == 1) ? miniprintf(STDOUT_FILENO, "%d  %s\n", i, h->s) : (0);
	return (V);
}

void	ft_temp_link(t_var *var, char **line)
{
	t_hist	*tmp;

	tmp = var->h;
	var->h = (t_hist *)malloc(sizeof(t_hist));
	var->h->s = ft_strdup(*line);
	var->h->end = 0;
	tmp->prev = var->h;
	var->h->next = tmp;
	var->h->prev = NULL;
}

void	ft_history_move(char way, t_var *var, char **line)
{
	if (var->h && var->h->prev == NULL && var->h->end == 1)
		ft_temp_link(var, line);
	else if (var->h && var->h->prev == NULL && var->h->end == 0)
	{
		free(var->h->s);
		var->h->s = ft_strdup(*line);
	}
	if ((way == 'u' && (var->h == NULL || var->h->next == NULL)) || (way == 'd'
	&& (var->h == NULL || var->h->prev == NULL)))
	{
		tputs(tgetstr("bl", NULL), 0, ft_outc);
		return ;
	}
	while (var->index > 0)
		ft_left(var);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	(way == 'u') ? var->h = var->h->next : (0);
	(way == 'd') ? var->h = var->h->prev : (0);
	miniprintf(STDOUT_FILENO, "%s", var->h->s);
	free(*line);
	*line = ft_strdup(var->h->s);
	var->index = ft_strlen(*line);
	var->multiline = (ft_prompt_len(var) + var->index) / var->col;
}
