/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 08:17:26 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:55:04 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_print_environment(t_var *var, int i)
{
	t_lenv	*begin;

	begin = var->lenv;
	while (var->lenv)
	{
		if ((i == 0 && var->lenv->c == 'e') || (i == 1))
			miniprintf(STDOUT_FILENO, "%s=%s\n", var->lenv->bef,
				var->lenv->aft);
		var->lenv = var->lenv->next;
	}
	var->lenv = begin;
	(i == 1) ? ft_free_var_cpy(var) : (0);
	return (V);
}

void	ft_init_var_logic(char **exec, t_var *var_cpy, int *i)
{
	*i = -1;
	if (!exec)
		return ;
	var_cpy->logic = (char **)malloc(sizeof(char *) * 2);
	var_cpy->logic[0] = NULL;
	var_cpy->logic[1] = NULL;
}

int		ft_pre_env(t_built *built, t_var *var)
{
	if (built->first == 0 && built->noarg)
	{
		ft_built_free(built);
		return (ft_print_environment(var, 0));
	}
	else if (built->first == 'i' && built->noarg)
	{
		ft_built_free(built);
		return (V);
	}
	return (5);
}

int		ft_env(t_built *built, t_var *var, int i)
{
	t_var	*var_cpy;
	char	**exec;
	int		ret;

	if ((ret = ft_pre_env(built, var)) != 5)
		return (ret);
	exec = ft_copy_var(built, &var_cpy, var);
	ft_init_var_logic(exec, var_cpy, &i);
	while (exec[++i])
	{
		exec[i] = ft_supp_space(exec[i]);
		var_cpy->logic[0] = ft_strdup(exec[i]);
		ft_no_pipe(var_cpy);
		if (!exec[i + 1] && ft_is_in(exec[i], '=') && !ft_is_in(exec[i], ' '))
		{
			ft_built_free(built);
			ft_freetab(&exec);
			return (ft_print_environment(var_cpy, 1));
		}
	}
	ft_freetab(&exec);
	ret = var_cpy->var_ret;
	ft_free_var_cpy(var_cpy);
	ft_built_free(built);
	return (ret);
}
