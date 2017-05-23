/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:45:12 by ggane             #+#    #+#             */
/*   Updated: 2016/11/16 09:50:18 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (*big && len > 0)
	{
		if (len < ft_strlen(little))
			return (NULL);
		j = 0;
		k = i;
		while (big[k] == little[j] && little[j] && big[k])
		{
			j++;
			k++;
		}
		if (little[j] == '\0')
			return ((char *)big + i);
		len--;
		big++;
	}
	return (NULL);
}
