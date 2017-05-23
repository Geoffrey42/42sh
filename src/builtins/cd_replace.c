/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:59:15 by ggane             #+#    #+#             */
/*   Updated: 2017/04/26 23:26:58 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_replace_cd(t_var *var, char *s)
{
	free(var->lenv->aft);
	var->lenv->aft = ft_strdup(s);
	free(s);
}

void	ft_no_pwd(char *buf, t_lenv **begin, char **old)
{
	char	*tmp;

	tmp = ft_strjoin("PWD=", buf);
	ft_sort_insert(begin, tmp, 'e');
	*old = ft_strdup(buf);
	free(tmp);
	free(buf);
}

void	ft_no_oldpwd(char *old, t_lenv **begin)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", old);
	ft_sort_insert(begin, tmp, 'e');
	free(tmp);
	free(old);
}

void	ft_replace_old(t_var *var, char *old)
{
	t_lenv	*begin;

	begin = var->lenv;
	while (var->lenv)
	{
		if (!ft_strcmp("OLDPWD", var->lenv->bef))
		{
			ft_replace_cd(var, old);
			break ;
		}
		var->lenv = var->lenv->next;
	}
	(var->lenv == NULL) ? ft_no_oldpwd(old, &begin) : (0);
	var->lenv = begin;
}
