/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:56:01 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:35:19 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_add_end(t_point *p, char *s)
{
	t_point	*beg;

	beg = p;
	while (p->next)
		p = p->next;
	p->next = (t_point *)malloc(sizeof(t_point));
	p->next->s = ft_strdup(s);
	free(s);
	p->next->next = NULL;
	p = beg;
}
