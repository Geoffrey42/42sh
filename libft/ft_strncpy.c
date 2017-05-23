/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:13:21 by ggane             #+#    #+#             */
/*   Updated: 2016/11/16 08:13:42 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	char	*temp;
	size_t	i;

	i = -1;
	temp = dest;
	while (++i < len && src[i])
		dest[i] = src[i];
	while (i < len)
		dest[i++] = '\0';
	return (temp);
}
