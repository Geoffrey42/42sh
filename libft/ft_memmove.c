/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 07:55:14 by ggane             #+#    #+#             */
/*   Updated: 2016/11/16 07:55:49 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned int	i;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	i = -1;
	if (dest > source)
		while (0 < len)
		{
			dest[len - 1] = source[len - 1];
			len--;
		}
	else
		while (++i < len)
			dest[i] = source[i];
	return (dst);
}
