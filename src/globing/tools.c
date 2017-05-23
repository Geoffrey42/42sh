/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 18:58:36 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:27:21 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

int			find(char *str)
{
	while (*str)
	{
		if (ft_strchr(SYNTAX, *str))
			return (1);
		str++;
	}
	return (0);
}

void		kill_star_in_brackets(char **str)
{
	char	*temp;
	int		i;
	int		y;
	int		pos;

	i = 0;
	y = 0;
	pos = 0;
	temp = *str;
	*str = (char*)malloc((ft_strlen(temp) + 1) * sizeof(char));
	while (temp[i])
	{
		if (temp[i] == '[')
			pos++;
		if (temp[i] == ']')
			pos--;
		while (temp[i] == '*' && pos > 0)
			i++;
		str[0][y] = temp[i];
		i++;
		y++;
	}
	str[0][y] = '\0';
	free(temp);
}
