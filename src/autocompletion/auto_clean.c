/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:12:08 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:33:46 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_free_comp(t_var *var)
{
	int	i;

	i = -1;
	while (var->comp->array[++i])
		free(var->comp->array[i]);
	free(var->comp->array);
	free(var->comp->end);
	free(var->comp->begin);
	free(var->comp);
}

char	*check_and_clean(char *line, t_var *var)
{
	char	*tmp;

	if (var->comp->split)
	{
		tmp = begin_clean(var->comp->begin);
		free(line);
		return (tmp);
	}
	else
	{
		tmp = begin_clean(line);
		free(line);
		return (tmp);
	}
	return (NULL);
}

void	clean_enter(t_var *var)
{
	tputs(tgetstr("me", NULL), 0, ft_outc);
	(var->comp->i == 0) ? var->comp->i = 0 : var->comp->i--;
	while (var->comp->ligne--)
		tputs(tgoto(tgetstr("dl", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
}
