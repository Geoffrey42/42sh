/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:32:37 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:15:23 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_supp_char(char *line, int *index)
{
	char	*ret;
	int		len;
	int		i;

	if (*index == 0)
		return (line);
	len = ft_strlen(line);
	(len < 2) ? len = 2 : (0);
	ret = (char *)malloc(sizeof(char) * (len));
	i = 0;
	while (i < *index - 1)
	{
		ret[i] = line[i];
		i++;
	}
	while (i < len - 1)
	{
		ret[i] = line[i + 1];
		i++;
	}
	ret[i] = '\0';
	(*index)--;
	free(line);
	return (ret);
}

char	*ft_del_char(char *line, int *index)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(line);
	if (*index == len)
		return (line);
	(len < 2) ? len = 2 : (0);
	ret = (char *)malloc(sizeof(char) * (len));
	i = 0;
	while (i < *index)
	{
		ret[i] = line[i];
		i++;
	}
	while (i < len - 1)
	{
		ret[i] = line[i + 1];
		i++;
	}
	ret[len - 1] = '\0';
	free(line);
	return (ret);
}
