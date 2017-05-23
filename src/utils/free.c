/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 16:59:11 by ggane             #+#    #+#             */
/*   Updated: 2017/04/13 15:52:30 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_free_struct(t_var *var)
{
	int	i;

	i = 0;
	(!var->opt_quo) ? free(var->copy) : (0);
	while (var->env && var->env[i])
	{
		free(var->env[i]);
		i++;
	}
	free(var->env);
	free(var);
}

void	ft_free_cmd(t_var *var)
{
	int	i;

	i = -1;
	while (var->cmd && var->cmd[++i])
		free(var->cmd[i]);
	if (var->cmd)
		free(var->cmd);
}

void	ft_free_logic(t_var *var)
{
	int	i;

	i = -1;
	while (var->logic && var->logic[++i])
		free(var->logic[i]);
	if (var->logic)
		free(var->logic);
}
