/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:50:28 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:07:49 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_search_lenv(t_lenv *lst, char *s)
{
	t_lenv	*begin;
	char	*ret;

	begin = lst;
	ret = NULL;
	while (lst)
	{
		if (!ft_strcmp(lst->bef, s))
		{
			ret = ft_strdup(lst->aft);
			break ;
		}
		lst = lst->next;
	}
	lst = begin;
	return (ret);
}

int		ft_first_step(char **s, t_var *var, char **tmp)
{
	if (access(*s, F_OK) == 0 && access(*s, X_OK) == 0)
		return (1);
	*tmp = ft_search_lenv(var->lenv, "PATH");
	if (!(*tmp))
	{
		miniprintf(STDERR_FILENO, "42sh: %s: command not found\n", *s);
		return (-1);
	}
	return (0);
}

void	ft_bef_find(int *i, char ***path, char **tmp)
{
	*path = ft_strsplit(*tmp, ':');
	free(*tmp);
	*i = -1;
	while ((*path)[++(*i)])
		ft_write_path(*tmp, *path, *i);
	*i = -1;
}

int		ft_find_exec(char **s, t_var *var)
{
	char	**path;
	char	*tmp;
	int		i;

	var->acces = 0;
	tmp = NULL;
	if ((i = ft_first_step(s, var, &tmp)) != 0)
		return (i);
	ft_bef_find(&i, &path, &tmp);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], *s);
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
			return (ft_join_path(i, path, s, tmp));
		else if (access(tmp, F_OK) == 0 && access(tmp, X_OK) != 0)
			return (ft_join_error(i, path, s, tmp));
		free(tmp);
		free(path[i]);
	}
	free(path);
	miniprintf(STDERR_FILENO, "42sh: %s: command not found\n", *s);
	var->acces = 1;
	return (0);
}
