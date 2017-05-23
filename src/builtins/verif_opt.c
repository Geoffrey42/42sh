/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 17:41:29 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:59:58 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_print_usage_nuoh(char cmd, char opt)
{
	if (cmd == 'n')
	{
		miniprintf(STDERR_FILENO,
			"42sh: unsetenv: illegal option -- %c\n", opt);
		miniprintf(STDERR_FILENO, "usage: unsetenv [name]\n");
	}
	else if (cmd == 'u')
	{
		miniprintf(STDERR_FILENO, "42sh: unset: illegal option -- %c\n", opt);
		miniprintf(STDERR_FILENO, "usage: unset [name]\n");
	}
	else if (cmd == 'o')
	{
		miniprintf(STDERR_FILENO, "42sh: echo: illegal option -- %c\n", opt);
		miniprintf(STDERR_FILENO, "usage: echo [-n] [string...]\n");
	}
	else if (cmd == 'h')
	{
		miniprintf(STDERR_FILENO, "42sh: history: illegal option -- %c\n", opt);
		miniprintf(STDERR_FILENO, "usage: history\n");
	}
	else if (cmd == 'x')
		miniprintf(STDERR_FILENO,
			"42sh: exit: illegal option -- %c\nusage: exit [n]\n", opt);
}

int		ft_print_usage(char cmd, char opt)
{
	if (cmd == 'c')
	{
		miniprintf(STDERR_FILENO, "42sh: cd: illegal option -- %c\n", opt);
		miniprintf(STDERR_FILENO, "usage: cd [directory] or cd - or cd ~\n");
	}
	else if (cmd == 'v')
	{
		miniprintf(STDERR_FILENO, "42sh: env: illegal option -- %c\n", opt);
		miniprintf(STDERR_FILENO, "usage: env [-i] [name=value]\n");
	}
	else if (cmd == 'e')
	{
		miniprintf(STDERR_FILENO, "42sh: export: illegal option -- %c\n", opt);
		miniprintf(STDERR_FILENO, "usage: export name[=word] or export -p\n");
	}
	else if (cmd == 's')
	{
		miniprintf(STDERR_FILENO, "42sh: setenv: illegal option -- %c\n", opt);
		miniprintf(STDERR_FILENO, "usage: setenv [name value]\n");
	}
	else
		ft_print_usage_nuoh(cmd, opt);
	return (F);
}

int		ft_verif_opt_env(t_built *built)
{
	if (!ft_strcmp(built->name, "unsetenv"))
		if (built->first != 0)
			return (ft_print_usage('n', built->first));
	if (!ft_strcmp(built->name, "unset"))
		if (built->first != 0)
			return (ft_print_usage('u', built->first));
	if (!ft_strcmp(built->name, "history"))
		if (built->first != 0)
			return (ft_print_usage('h', built->first));
	return (V);
}

int		ft_verif_opt(t_built *built)
{
	if (!ft_strcmp(built->name, "exit"))
		if (built->first != 0)
			return (ft_print_usage('x', built->first));
	if (!ft_strcmp(built->name, "cd"))
		if (built->first != 0)
			return (ft_print_usage('c', built->first));
	if (!ft_strcmp(built->name, "env"))
	{
		if (built->first != 0 && built->first != 'i')
			return (ft_print_usage('v', built->first));
		if (built->error != 0)
			return (ft_print_usage('v', built->error));
	}
	if (!ft_strcmp(built->name, "export"))
	{
		if (built->first != 0 && built->first != 'p')
			return (ft_print_usage('e', built->first));
		if (built->error != 0)
			return (ft_print_usage('e', built->error));
	}
	if (!ft_strcmp(built->name, "setenv"))
		if (built->first != 0)
			return (ft_print_usage('s', built->first));
	return (ft_verif_opt_env(built));
}
