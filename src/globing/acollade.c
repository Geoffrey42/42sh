/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acollade.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:19:02 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:22:24 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int		get_size_accolade(char *accolade)
{
	int	i;
	int	count;
	int	count_acc;

	i = 1;
	count = 1;
	count_acc = 1;
	while (accolade[i] != '\0' && count_acc > 0)
	{
		if (accolade[i] == ',' && count_acc == 1)
			count++;
		else if (accolade[i] == '{')
			count_acc++;
		else if (accolade[i] == '}')
			count_acc--;
		i++;
	}
	return (count);
}

static int		verif_accolades(char **listing)
{
	int		i;
	int		y;

	i = 0;
	while (listing[i] != NULL)
	{
		y = 0;
		while (listing[i][y])
		{
			if (listing[i][y] == '{')
				return (i);
			y++;
		}
		i++;
	}
	return (-1);
}

static char		**transform(char *str, int i)
{
	char	**res;
	int		y;
	int		position;

	position = 0;
	y = 0;
	res = NULL;
	while (str[i] && res == NULL)
	{
		if (str[i] == '{')
			res = (char**)malloc((get_size_accolade(&(str[i])) + 1)
					* sizeof(char*));
		else
			i++;
	}
	while (y < get_size_accolade(&(str[i])))
	{
		res[y] = parsing(str, position);
		position++;
		y++;
	}
	res[y] = NULL;
	str[0] = '\0';
	return (res);
}

char			**split_accolades(char *str)
{
	char	**listing;
	char	**temp;
	int		pos;

	listing = (char**)malloc(2 * sizeof(char*));
	listing[0] = ft_strdup(str);
	listing[1] = NULL;
	while ((pos = verif_accolades(listing)) != -1)
	{
		temp = transform(listing[pos], 0);
		listing = add_double_char(listing, temp);
	}
	return (listing);
}
