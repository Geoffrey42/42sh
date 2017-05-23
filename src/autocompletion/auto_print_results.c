/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_results.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:53:22 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:44:20 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_result(char *line, t_var *var)
{
	tputs(tgoto(tgetstr("ce", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(ft_prompt_len(var) + ft_strlen(line))), 0, ft_outc);
	ft_putstr(var->comp->array[0]);
	(var->comp->split) ? ft_putstr(var->comp->end) : (0);
	tputs(tgoto(tgetstr("dl", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
	ft_prompt(var);
	ft_putstr(line);
	ft_putstr(var->comp->array[0]);
	(var->comp->split) ? ft_putstr(var->comp->end) : (0);
	tputs(tgoto(tgetstr("ch", NULL), 0, (ft_prompt_len(var) + ft_strlen(line)
					+ ft_strlen(var->comp->array[0]))), 0, ft_outc);
}
