/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 07:52:20 by ggane             #+#    #+#             */
/*   Updated: 2016/11/16 07:52:26 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *source;
	unsigned char *dest;

	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	while (n > 0)
	{
		*dest = *source;
		n--;
		dest++;
		source++;
	}
	return (dst);
}
