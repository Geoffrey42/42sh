/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:33:49 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 15:33:54 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_len_array(char **str)
{
	int		x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

char		**ft_dup_array(char **array)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	if (!array)
		return (NULL);
	ret = (char**)malloc(sizeof(char*) * (ft_len_array(array) + 2));
	while (array[i])
	{
		ret[i] = ft_strdup(array[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
