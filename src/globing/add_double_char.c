/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_double_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:19:02 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:22:37 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int	is_not_contained(char *str, char **lst)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (0);
	while (lst[i] != NULL)
	{
		if (ft_strcmp(lst[i], str) == 0)
			return (0);
		i++;
	}
	return (1);
}

static void	copy_double_char(char **str, char **tocpy, int *y)
{
	int		i;

	i = 0;
	while (tocpy[i] != NULL)
	{
		if (tocpy[i][0] != '\0' && is_not_contained(tocpy[i], str))
		{
			str[*y] = ft_strdup(tocpy[i]);
			(*y)++;
			str[*y] = NULL;
		}
		i++;
	}
}

void		free_double_char(char **str)
{
	int		i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != NULL)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

int			get_size_double_char(char **str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != NULL)
		i++;
	return (i);
}

char		**add_double_char(char **l1, char **l2)
{
	char	**addition;
	int		y;

	addition = (char**)malloc((get_size_double_char(l1) +
				get_size_double_char(l2) + 1) * sizeof(char*));
	y = 0;
	addition[0] = NULL;
	if (l1 != NULL)
	{
		copy_double_char(addition, l1, &y);
		free_double_char(l1);
	}
	if (l2 != NULL)
	{
		copy_double_char(addition, l2, &y);
		free_double_char(l2);
	}
	return (addition);
}
