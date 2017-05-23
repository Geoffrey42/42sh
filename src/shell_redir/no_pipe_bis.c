/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 06:24:03 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 18:00:38 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		ft_no_red(t_var *var, int *res)
{
	if (*res == V && var->var_ret == F &&
	!ft_strcmp(var->logic[var->i - 1], "&&"))
		*res = F;
	else if (*res == F && var->var_ret == V &&
	!ft_strcmp(var->logic[var->i - 1], "||"))
		*res = V;
	else if (*res == V && var->var_ret == V &&
	!ft_strcmp(var->logic[var->i - 1], "||"))
		*res = F;
}
