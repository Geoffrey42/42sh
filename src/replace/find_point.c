/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:37:18 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:34:25 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	ft_increase_i(char *s, int *i)
{
	while (s[*i] >= '0' && s[*i] <= '9')
		(*i)++;
}

int			ft_find_point(char *s)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
		if (s[i] == '{')
		{
			j = ++i - 1;
			if (s[i] >= 'a' && s[i] <= 'z' && s[++i] == '.' && s[i + 1] == '.'
					&& s[i + 2] >= 'a' && s[i + 2] <= 'z' && s[i + 3] == '}')
				return (2);
			else if (s[i] >= 'A' && s[i] <= 'Z' && s[++i] == '.' && s[i + 1] ==
				'.' && s[i + 2] >= 'A' && s[i + 2] <= 'Z' && s[i + 3] == '}')
				return (2);
			while (s[i] >= '0' && s[i] <= '9')
				i++;
			if (s[i] == '.' && s[++i] == '.' && ++i > 0)
			{
				ft_increase_i(s, &i);
				if (s[i - 1] != '.' && s[i] == '}')
					return (3);
			}
			i = j;
		}
	return (F);
}

int			ft_find_nbr(char *s, int i)
{
	int		len;
	char	*nb;
	int		ret;

	len = i;
	ret = 0;
	while (s[len] >= '0' && s[len] <= '9')
		len++;
	nb = ft_strsub(s, i, len - i);
	ret = ft_atoi(nb);
	free(nb);
	return (ret);
}
