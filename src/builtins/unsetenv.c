/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 20:41:55 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:59:45 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_free_link(t_lenv **begin, t_var *var)
{
	t_lenv	*tmp;

	tmp = var->lenv;
	*begin = tmp->next;
	free(tmp->bef);
	free(tmp->aft);
	free(tmp);
}

void	ft_free_next_link(t_var *var)
{
	t_lenv	*tmp;

	tmp = var->lenv->next;
	var->lenv->next = var->lenv->next->next;
	free(tmp->bef);
	free(tmp->aft);
	free(tmp);
}

int		ft_unsetenv_next(t_built *built, t_var *var, t_lenv **begin)
{
	if (built->noarg)
	{
		ft_built_free(built);
		return (ft_error_print("Too few arguments.\n"));
	}
	if (var->lenv == NULL)
	{
		ft_built_free(built);
		return (V);
	}
	*begin = var->lenv;
	return (5);
}

int		ft_unsetenv(t_built *built, t_var *var)
{
	int		i;
	t_lenv	*begin;

	if ((i = ft_unsetenv_next(built, var, &begin)) != 5)
		return (i);
	i = -1;
	while (built->arg && built->arg[++i])
	{
		if (!ft_strcmp(var->lenv->bef, built->arg[0]))
			ft_free_link(&begin, var);
		while (var->lenv && var->lenv->next)
		{
			if (!ft_strcmp(built->arg[i], var->lenv->next->bef))
				ft_free_next_link(var);
			var->lenv = var->lenv->next;
		}
		var->lenv = begin;
	}
	var->lenv = begin;
	free(var->name);
	free(var->addr);
	var->name = ft_find_name(var->lenv);
	var->addr = ft_find_addr(var->lenv);
	ft_built_free(built);
	return (V);
}
