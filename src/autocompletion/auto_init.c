/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 12:56:27 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:40:17 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_initial_tab(char *line, t_var *var, struct winsize *ws)
{
	init_tab(line, var);
	var->comp->i = 1;
	(var->comp->array[0] == NULL) ? var->comp->i = 0 : (0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, ws);
}

void	init_tab(char *line, t_var *var)
{
	if (!(var->comp = (t_comp *)malloc(sizeof(t_comp))))
		ft_error_malloc();
	var->comp->prec = 0;
	var->comp->split = 0;
	var->comp->ligne = 0;
	var->comp->i = 0;
	var->comp->j = 0;
	var->comp->res = 0;
	if (!(var->comp->begin = (char *)malloc(sizeof(char) * var->index + 1)))
		ft_error_malloc();
	if ((ft_strlen(line) - var->index) > 0)
	{
		if (!(var->comp->end = (char *)malloc(sizeof(char) *
			((int)ft_strlen(line) - var->index + 1))))
			ft_error_malloc();
	}
	else
		var->comp->end = ft_strdup("\0");
	split_line(line, var);
}

void	ft_init_tabulation(t_var *var, int *i, int col)
{
	*i = -1;
	var->nb_line = 0;
	var->comp->space = 0;
	var->comp->nb_word = col / (max_len(var->comp->array) + 1);
	var->comp->col = var->comp->nb_word;
}
