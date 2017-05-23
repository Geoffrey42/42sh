/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:07:41 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 15:35:51 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	int		i;

	ret = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (ret)
	{
		i = -1;
		while (s1[++i])
			ret[i] = s1[i];
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}
