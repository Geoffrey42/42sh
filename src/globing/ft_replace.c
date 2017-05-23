/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:56:01 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:24:32 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

void	ft_deltab(void *ad, size_t size)
{
	size_t	i;
	void	**tab;

	if (ad == NULL)
		return ;
	tab = (void**)ad;
	i = 0;
	while (i < size)
	{
		if (tab[i] != NULL)
			ft_memdel(&tab[i]);
		i++;
	}
	ft_memdel((void**)&tab);
}

size_t	ft_strsplit_size(char **split)
{
	size_t	size;

	size = 0;
	while (split[size] != NULL)
		size++;
	return (size);
}

char	*ft_replace(char *str, char *to_delete, char *to_put)
{
	char	**split;
	char	*result;

	if (ft_strstr(str, to_delete) == NULL)
		return (str);
	split = ft_explode(str, to_delete);
	result = ft_implode(split, to_put);
	ft_strdel(&str);
	ft_deltab(split, ft_strsplit_size(split));
	return (result);
}
