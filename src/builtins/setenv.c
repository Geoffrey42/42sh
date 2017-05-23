/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 17:41:29 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:59:31 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_line_alphabetic(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] < 'A' || (s[i] > 'Z' && s[i] < 'a') || s[i] > 'z')
			return (F);
	return (V);
}

int		ft_error_print(char *s)
{
	miniprintf(STDERR_FILENO, "%s", s);
	return (F);
}

void	ft_setenv_next(t_built *built, t_var *var)
{
	char	*s;
	char	*s1;

	s = ft_strjoin(built->arg[0], "=");
	if (built->arg[1] != NULL)
		s1 = ft_strjoin(s, built->arg[1]);
	else
		s1 = ft_strdup(s);
	free(s);
	ft_sort_insert(&var->lenv, s1, 'e');
	free(s1);
	free(var->name);
	free(var->addr);
	var->name = ft_find_name(var->lenv);
	var->addr = ft_find_addr(var->lenv);
	ft_built_free(built);
}

int		ft_setenv(t_built *built, t_var *var)
{
	int	len;

	len = 0;
	(built->noarg == 0) ? len = ft_len_array(built->arg) : (0);
	if (built->noarg || len == 0)
		return (ft_env(built, var, 0));
	if (len > 2)
	{
		ft_built_free(built);
		return (ft_error_print("42sh: setenv: Too many arguments.\n"));
	}
	if (ft_line_alphabetic(&(built->arg[0][0])))
	{
		ft_built_free(built);
		return (ft_error_print(
		"42sh: setenv: Variable name must contain alphabetics characters.\n"));
	}
	ft_setenv_next(built, var);
	return (V);
}
