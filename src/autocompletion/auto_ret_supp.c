/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_ret_supp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:55:27 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:45:27 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ret_del_supp(char *line, t_var *var)
{
	if (!var->comp->split)
	{
		while (var->comp->ligne--)
			tputs(tgoto(tgetstr("dl", NULL), 0, 0), 0, ft_outc);
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
		ft_prompt(var);
		ft_putstr(line);
		return (line);
	}
	else
		return (ft_strjoin(var->comp->begin, var->comp->end));
}
