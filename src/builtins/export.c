/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 20:47:20 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:56:12 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int	ft_export_print(t_var *var)
{
	t_lenv	*begin;

	begin = var->lenv;
	while (var->lenv)
	{
		miniprintf(STDOUT_FILENO, "export %s", var->lenv->bef);
		if (var->lenv->aft[0] != '\0')
			miniprintf(STDOUT_FILENO, "=\"%s\"\n", var->lenv->aft);
		else
			miniprintf(STDOUT_FILENO, "\n");
		var->lenv = var->lenv->next;
	}
	var->lenv = begin;
	return (V);
}

int	ft_export(t_built *built, t_var *var)
{
	int		i;
	char	c;

	if (built->noarg)
	{
		ft_built_free(built);
		return (ft_export_print(var));
	}
	i = -1;
	if (built->arg && built->arg[0])
		if ((c = built->arg[0][0]) < 'A' || (c > 'Z' && c < 'a') || c > 'z')
		{
			miniprintf(STDERR_FILENO, "42sh: export: Variable name must %s",
			"begin with alphabetic character.\n");
			ft_built_free(built);
			return (F);
		}
	while (built->arg[++i])
		ft_sort_insert(&var->lenv, built->arg[i], 'e');
	free(var->name);
	free(var->addr);
	var->name = ft_find_name(var->lenv);
	var->addr = ft_find_addr(var->lenv);
	ft_built_free(built);
	return (V);
}
