/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:22:34 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:23:13 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		loop_tilde(t_var *term, char ***tabl, int i)
{
	char	*tmp;
	int		x;
	int		j;

	x = 1;
	j = ft_strlen(term->home);
	tmp = ft_strdup((*tabl)[i]);
	(*tabl)[i] = ft_free((*tabl)[i]);
	(*tabl)[i] = ft_strdup(term->home);
	while (tmp[x])
		(*tabl)[i][j++] = tmp[x++];
	(*tabl)[i][j] = '\0';
	tmp = ft_free(tmp);
}

void		tilde(t_var *term, char ***tabl)
{
	int		i;

	i = 0;
	if (term->home)
	{
		while ((*tabl)[i])
		{
			if (ft_strcmp(((*tabl))[i], "~") == 0)
			{
				(*tabl)[i] = ft_free((*tabl)[i]);
				(*tabl)[i] = ft_strdup(term->home);
			}
			if ((ft_strncmp((*tabl)[i], "~/", 2) == 0))
				loop_tilde(term, tabl, i);
			i++;
		}
	}
}
