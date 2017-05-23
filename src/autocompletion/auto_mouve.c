/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_mouve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 12:49:27 by ggane             #+#    #+#             */
/*   Updated: 2017/04/26 22:50:13 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_enter_tab(t_var *var, char *line)
{
	char	*ret;

	if (var->comp->len > 1)
	{
		if (!var->comp->array[var->comp->i])
			var->comp->i = 0;
		else
			var->comp->i++;
		clean_enter(var);
	}
	else
	{
		tputs(tgoto(tgetstr("dl", NULL), 0, 0), 0, ft_outc);
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
		ft_prompt(var);
	}
	var->comp->len = 0;
	if (var->comp->split)
		ret = ret_join_split(line, var);
	else
		ret = ret_single_line(line, var);
	return (ret);
}

void	ft_move_le_ri(int opt, t_var *var, int len)
{
	if (opt == 0)
	{
		if (var->comp->i == 0)
			var->comp->i = len - 1;
		else
			var->comp->i = var->comp->i - 1;
	}
	else
	{
		if (var->comp->i == len)
			var->comp->i = -1;
		else
			var->comp->i = var->comp->i + 1;
	}
}

void	ft_move_down(t_var *var, int len)
{
	if (var->comp->i + var->comp->col >= len)
	{
		while (var->comp->i - var->comp->col + 1 >= 0)
			var->comp->i -= var->comp->col;
		var->comp->i++;
	}
	else
		var->comp->i += var->comp->col;
}

void	ft_move_up(t_var *var, int len)
{
	if (var->comp->i - var->comp->col < 0)
	{
		while (var->comp->i + var->comp->col - 1 < len)
			var->comp->i += var->comp->col;
		var->comp->i--;
		if (var->comp->i < 0 || var->comp->i >= len)
			var->comp->i = len - 1;
	}
	else
		var->comp->i -= var->comp->col;
}
