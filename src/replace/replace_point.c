/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:34:08 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:35:42 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_sep_point(t_point *p)
{
	t_point	*begin;

	begin = p;
	while (p != NULL)
	{
		if (ft_find_point(p->s) == 2)
		{
			ft_concat(p);
			p = begin;
		}
		else if (ft_find_point(p->s) == 3)
		{
			ft_concat_nbr(p);
			p = begin;
		}
		else
			p = p->next;
	}
}

void	ft_replace_tmp(char **s, t_point **p)
{
	char	*tmp;

	tmp = ft_strjoin(*s, " ");
	free(*s);
	*s = ft_strjoin(tmp, (*p)->s);
	free(tmp);
	free((*p)->s);
	*p = (*p)->next;
}

char	*replace(char *line)
{
	t_point	*p;
	t_point	*beg;
	char	*s;

	if (ft_find_point(line) == F)
		return (line);
	p = (t_point *)malloc(sizeof(t_point));
	p->s = ft_strdup(line);
	p->next = NULL;
	ft_sep_point(p);
	s = ft_strdup("\0");
	beg = p;
	while (p)
		ft_replace_tmp(&s, &p);
	p = beg;
	while (p)
	{
		beg = p;
		p = p->next;
		free(beg);
	}
	free(line);
	return (s);
}

char	*replace_d_point(char *line)
{
	char	**array;
	int		i;
	char	*tmp;
	char	*ret;

	if (ft_find_point(line) == F)
		return (line);
	array = ft_strsplit_sp(line);
	ret = ft_strdup("\0");
	i = -1;
	while (array[++i])
	{
		array[i] = replace(array[i]);
		tmp = ft_strjoin(ret, " ");
		free(ret);
		ret = ft_strjoin(tmp, array[i]);
		free(tmp);
	}
	ft_freetab(&array);
	free(line);
	return (ret);
}
