/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_placecursor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:18:55 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:42:49 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	place_cursor(t_var *var)
{
	if (!var->comp->split)
	{
		var->comp->j = -1;
		while (++var->comp->j <= (int)ft_strlen(var->comp->array[var->comp->i]))
			tputs(tgetstr("dc", NULL), var->comp->j, ft_outc);
	}
	else
	{
		var->comp->j = -1;
		while (++var->comp->j <= (int)ft_strlen(var->comp->end))
			tputs(tgetstr("dc", NULL), var->comp->j, ft_outc);
		tputs(tgoto(tgetstr("ch", NULL), 0, (ft_prompt_len(var) +
		ft_strlen(var->comp->begin) + ft_strlen(var->comp->array[var->comp->i])
						- 1)), 0, ft_outc);
	}
}

void	ft_place_for_tab(char *line, t_var *var)
{
	int	j;

	j = ft_strlen(line) + ft_prompt_len(var) +
	ft_strlen(var->comp->array[var->comp->i]);
	j = j / var->col;
	while (--var->comp->ligne)
		tputs(tgoto(tgetstr("dl", NULL), 0, 0), 0, ft_outc);
	while (--j >= 0)
		tputs(tgetstr("up", NULL), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("cd", NULL), 0, 0), 0, ft_outc);
	ft_prompt(var);
	ft_putstr(line);
	(var->comp->len != 1) ? print_first_line(line, var) : (0);
}
