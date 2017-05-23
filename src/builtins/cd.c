/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 16:59:12 by ggane             #+#    #+#             */
/*   Updated: 2017/04/26 23:23:53 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_go_home(char *arg, t_var *var)
{
	t_lenv	*begin;
	char	*s;

	begin = var->lenv;
	s = NULL;
	while (var->lenv)
	{
		if ((!ft_strcmp(var->lenv->bef, "HOME") && ((arg && arg[0] != '-') ||
		!arg)) || (!ft_strcmp(var->lenv->bef, "OLDPWD") &&
			arg && arg[0] == '-'))
			s = ft_strdup(var->lenv->aft);
		var->lenv = var->lenv->next;
	}
	var->lenv = begin;
	return (s);
}

int		ft_go_cd(t_var *var, char *buf)
{
	char	*old;
	t_lenv	*begin;

	begin = var->lenv;
	while (var->lenv)
	{
		if (!ft_strcmp("PWD", var->lenv->bef))
		{
			old = ft_strdup(var->lenv->aft);
			ft_replace_cd(var, buf);
			break ;
		}
		var->lenv = var->lenv->next;
	}
	(var->lenv == NULL) ? ft_no_pwd(buf, &begin, &old) : (0);
	var->lenv = begin;
	ft_replace_old(var, old);
	free(var->addr);
	var->addr = ft_find_addr(var->lenv);
	return (V);
}

int		ft_print_error(char *s)
{
	miniprintf(STDERR_FILENO, "%s", s);
	return (F);
}

int		ft_cd_errors(char *path, t_built *built)
{
	if (path == NULL)
	{
		ft_built_free(built);
		return (ft_print_error("42sh: cd: No such file or directory.\n"));
	}
	if (chdir(path) < 0)
	{
		miniprintf(STDERR_FILENO,
			"42sh: cd: %s: No such file or directory.\n", path);
		free(path);
		ft_built_free(built);
		return (F);
	}
	return (V);
}

int		ft_cd(t_built *built, t_var *var)
{
	char	*path;
	char	*buf;

	buf = NULL;
	if (built->noarg == 0 && built->arg[1] != NULL)
	{
		ft_built_free(built);
		return (ft_print_error("42sh: cd: Too many arguments.\n"));
	}
	if (built->noarg == 1)
		path = ft_go_home(NULL, var);
	else if (!ft_strcmp(built->arg[0], "~") || !ft_strcmp(built->arg[0], "-"))
		path = ft_go_home(built->arg[0], var);
	else
		path = ft_strdup(built->arg[0]);
	if (ft_cd_errors(path, built) == F)
		return (F);
	buf = getcwd(buf, ft_strlen(path));
	free(path);
	ft_built_free(built);
	return (ft_go_cd(var, buf));
}
