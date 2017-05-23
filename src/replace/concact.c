/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concact.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:35:22 by ggane             #+#    #+#             */
/*   Updated: 2017/04/20 00:09:33 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_swap(int *a, int *b)
{
	*a += *b;
	*b = *a - *b;
	*a -= *b;
}

void	ft_swap_char(char *a, char *b)
{
	*a += *b;
	*b = *a - *b;
	*a -= *b;
}

void	ft_increm(t_point *p, int *i)
{
	while (p->s[*i] != '.')
		(*i)++;
	*i += 2;
}

void	ft_concat_nbr(t_point *p)
{
	char	*bef;
	char	*aft;
	int		point;
	int		to_go;
	int		i;

	i = ft_strlen(p->s);
	while (i > 0)
		if (p->s[--i] == '{' && ft_find_point(&(p->s[i])) == 3)
			break ;
	bef = ft_strsub(p->s, 0, i);
	point = ft_find_nbr(p->s, ++i);
	ft_increm(p, &i);
	to_go = ft_find_nbr(p->s, i);
	while (p->s[i] != '}')
		i++;
	i++;
	aft = ft_strsub(p->s, i, ft_strlen(p->s) - i + 1);
	free(p->s);
	(to_go < point) ? ft_swap(&to_go, &point) : (0);
	p->s = ft_strjoin_int(bef, to_go, aft);
	while (point < to_go)
		ft_add_end(p, ft_strjoin_int(bef, point++, aft));
	free(bef);
	free(aft);
}

void	ft_concat(t_point *p)
{
	char	*bef;
	char	*aft;
	char	point;
	char	to_go;
	int		i;

	i = ft_strlen(p->s);
	while (i > 0)
		if (p->s[--i] == '{' && ft_find_point(&(p->s[i])) == 2)
			break ;
	bef = ft_strsub(p->s, 0, i);
	point = p->s[++i];
	i += 3;
	to_go = p->s[i++];
	i++;
	aft = ft_strsub(p->s, i, ft_strlen(p->s) - i + 1);
	free(p->s);
	if (to_go < point)
		ft_swap_char(&to_go, &point);
	p->s = ft_strjoin_char(bef, to_go, aft);
	while (point < to_go)
		ft_add_end(p, ft_strjoin_char(bef, point++, aft));
	free(bef);
	free(aft);
}
