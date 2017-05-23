/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:47:04 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:25:58 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static void	parsing_3(char **str, int *i, int count)
{
	while (str[0][*i] && count > 0)
	{
		if (str[0][*i] == '{')
			count++;
		else if (str[0][*i] == '}')
			count--;
		(*i)++;
	}
}

static char	*parsing_2(char *str, char *cpy, int i, int y)
{
	int	count;

	count = 1;
	while (str[i] && !(str[i] == ',' && count == 1) && count > 0)
	{
		if (str[i] == '{')
			count++;
		else if (str[i] == '}')
			count--;
		if (count > 0)
			cpy[y] = str[i];
		i++;
		y++;
	}
	parsing_3(&str, &i, count);
	while (str[i])
	{
		cpy[y] = str[i];
		i++;
		y++;
	}
	cpy[y] = '\0';
	return (cpy);
}

char		*parsing(char *str, int pos)
{
	char	*cpy;
	int		i;
	int		y;

	i = 0;
	y = 0;
	cpy = (char*)malloc((ft_strlen(str) + 1) * sizeof(char));
	while (str[i] && str[i] != '{')
	{
		cpy[y] = str[i];
		y++;
		i++;
	}
	i++;
	while (str[i] && pos != 0)
	{
		if (str[i] == ',')
			pos--;
		i++;
	}
	return (parsing_2(str, cpy, i, y));
}
