/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:18:24 by ggane             #+#    #+#             */
/*   Updated: 2017/04/24 23:06:50 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	ft_and_or(int *i, t_var *var, int res)
{
	var->error_hdc = 0;
	if (*i == 0)
	{
		miniprintf(STDERR_FILENO, "42sh: parse error near `%s'\n",
				var->logic[0]);
		var->var_ret = 1;
		return (-1);
	}
	if ((res == V && var->logic[*i][0] == '|') ||
			(res == F && var->logic[*i][0] == '&'))
	{
		var->var_ret = 1;
		(*i)++;
	}
	return (0);
}

static void	ft_no_redir(char **arg, t_var *var, int *ret, int *res)
{
	arg[0] = ft_change(arg[0], -1, 0);
	if (ft_is_builtin(arg[0]) == V)
		var->var_ret = builtins(arg, var);
	else if (arg[0] != NULL)
	{
		if (ft_find_exec(&arg[0], var))
		{
			*ret = ft_execution(var, arg, *ret);
			*res = WEXITSTATUS(*ret);
			if (*res == -1)
				*res = var->var_ret;
			else if (var->i > 0 && var->var_ret <= 100)
				ft_no_red(var, res);
		}
		var->var_ret <= 100 ? var->var_ret = *res : (0);
	}
	else
		var->var_ret = 1;
	ft_freetab(&arg);
}

void		ft_redir_ret(t_var *var, int *res, int i)
{
	if (*res == V && var->var_ret == F && !ft_strcmp(var->logic[i - 1],
			"&&"))
		*res = F;
	else if (*res == F && var->var_ret == V && !ft_strcmp(var->logic[i - 1],
			"||"))
		*res = V;
	else if (*res == V && var->var_ret == V && !ft_strcmp(var->logic[i - 1],
			"||"))
		*res = F;
}

static void	ft_all_redir(t_var *var, int i, int *ret, int *res)
{
	int	kk;

	ft_init_redir(var, var->logic[i]);
	var->aggreg = 0;
	ft_create_file(var->logic[i]);
	var->count_redir = 0;
	if (ft_search_pipe(var) == 1)
		*ret = gift_pipe(var);
	else
		*ret = ft_redir(var, 0, -1);
	ft_freetab(&(var->pipe));
	ft_freetab(&(var->command));
	kk = -1;
	while (++kk < var->count_redir)
		free(var->redir[kk]);
	free(var->redir);
	var->var_ret = WEXITSTATUS(*ret);
	if (*res == -1)
		*res = var->var_ret;
	else if (i > 0)
		ft_redir_ret(var, res, i);
	var->var_ret = *res;
}

int			ft_no_pipe(t_var *var)
{
	int		i;
	int		ret;
	char	**arg;
	int		res;

	i = -1;
	res = -1;
	var->ifpipe = 0;
	while (var->logic[++i] && (var->i = i) > -1)
	{
		if (ft_strcmp(var->logic[i], "||") && ft_strcmp(var->logic[i], "&&"))
		{
			(i > 0 && ft_strcmp(var->logic[i - 1], "||") &&
				ft_strcmp(var->logic[i - 1], "&&")) ? res = -1 : (0);
			(!ft_search_redir(var->logic[i]) &&
				(arg = ft_strsplit_sp(var->logic[i])) != NULL) ?
					ft_no_redir(arg, var, &ret, &res) : (0);
			(ft_search_redir(var->logic[i])) ?
				ft_all_redir(var, i, &ret, &res) : (0);
		}
		else if (ft_and_or(&i, var, res) == -1)
			return (-1);
	}
	i = -1;
	return (var->var_ret);
}
