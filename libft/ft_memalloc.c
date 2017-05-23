/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 07:51:58 by ggane             #+#    #+#             */
/*   Updated: 2016/11/16 07:52:09 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *new;

	if ((new = (void *)malloc(sizeof(void) * size)))
	{
		ft_bzero(new, size);
		return (new);
	}
	return (NULL);
}
