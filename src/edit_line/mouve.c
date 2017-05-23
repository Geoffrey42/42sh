/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:42:54 by ggane             #+#    #+#             */
/*   Updated: 2017/04/25 16:25:01 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_left(t_var *var)
{
	var->index--;
	tputs(tgetstr("le", NULL), 0, ft_outc);
	if ((var->index + ft_prompt_len(var)) % var->col == 0)
		var->multiline--;
}

void	ft_right(t_var *var)
{
	var->index++;
	if ((var->index + ft_prompt_len(var)) % var->col == 0)
	{
		tputs(tgoto(tgetstr("do", NULL), 0, 0), 0, ft_outc);
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
		var->multiline++;
	}
	else
		tputs(tgetstr("nd", NULL), 0, ft_outc);
}

void	ft_prev_word(t_var *var, char *line)
{
	while (var->index > 0 && !ft_iswspace(line[var->index]))
		ft_left(var);
	while (var->index > 0 && ft_iswspace(line[var->index]))
		ft_left(var);
	while (var->index > 0 && !ft_iswspace(line[var->index]))
		ft_left(var);
	if (var->index > 0)
		ft_right(var);
}

void	ft_next_word(t_var *var, char *line, int len)
{
	while (var->index < len && !ft_iswspace(line[var->index]))
		ft_right(var);
	while (var->index < len && ft_iswspace(line[var->index]))
		ft_right(var);
}
