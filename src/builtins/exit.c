/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 08:17:51 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:56:00 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_built_free(t_built *built)
{
	int	i;

	i = -1;
	free(built->name);
	if (built->noarg == 0)
	{
		while (built->arg[++i])
			free(built->arg[i]);
		free(built->arg);
	}
	free(built);
}

int		ft_exit(t_built *built, t_var *var)
{
	int	ret;
	int	i;

	ret = var->var_ret;
	if (built->noarg == 0)
	{
		if (built->arg[1] != NULL)
			miniprintf(STDERR_FILENO, "42sh: exit: too many arguments.\n");
		else
		{
			i = -1;
			while (built->arg[0][++i])
				if (built->arg[0][i] < '0' || built->arg[0][i] > '9')
				{
					miniprintf(STDERR_FILENO,
					"42sh: exit: numeric arguments required.\n");
					ft_built_free(built);
					return (F);
				}
			ret = ft_atoi(built->arg[0]);
		}
	}
	ft_built_free(built);
	exit(ret);
	return (V);
}
