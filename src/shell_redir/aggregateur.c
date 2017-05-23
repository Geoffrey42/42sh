/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregateur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:50:48 by ggane             #+#    #+#             */
/*   Updated: 2017/04/18 15:25:05 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_return_aggreg(int *i)
{
	int	from;
	int	to;

	from = *i % 10;
	to = *i / 10;
	dup2(to, from);
	*i = 0;
}

void	ft_aggreg(char *s, int *aggreg, t_var *term)
{
	char	*tmp;

	term->from = 0;
	term->to = 0;
	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[0] = s[0];
	tmp[1] = '\0';
	term->from = ft_atoi(tmp);
	if (s[3] == '-')
		term->to = -1;
	else
	{
		tmp[0] = s[3];
		term->to = ft_atoi(tmp);
	}
	if (term->to == -1 && !(term->from == 2 && term->ifpipe == 1))
		close(term->from);
	else if (term->to != -1)
	{
		if (term->to != 1 || (term->to == 1 && term->ifpipe == 0))
			dup2(term->to, term->from);
		*aggreg = term->from * 10 + term->to;
	}
	free(tmp);
}
