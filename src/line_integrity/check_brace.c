/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_brace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:12:06 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:32:23 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_check_brace(char c, int *i, char **cpy, int begin)
{
	t_quotes	*qu;

	qu = ft_init_quotes();
	c = ft_end_of_par((*cpy)[*i]);
	begin = *i;
	while ((*cpy)[++(*i)] != '\0' && (*cpy)[*i] != c)
	{
		if ((*cpy)[*i] == ';')
			return (ft_return_brace(qu, c));
		if (((*cpy)[*i] != c && (*cpy)[*i] != (*cpy)[begin]) ||
		(*cpy)[*i] == '`')
			ft_check_par((*cpy)[*i], qu);
	}
	if ((*cpy)[*i] == '\0' || qu->par != 0 || qu->acc != 0 || qu->bra != 0
			|| qu->bac != 0)
	{
		free(qu);
		return (ft_return_syntax((*cpy)[begin]));
	}
	(*cpy)[*i] = '.';
	(*cpy)[begin] = '.';
	free(qu);
	*i = 0;
	return (1);
}
