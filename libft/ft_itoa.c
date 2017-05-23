/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 07:47:00 by ggane             #+#    #+#             */
/*   Updated: 2016/11/16 07:47:29 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		nlen;

	nlen = ft_len_nb(n);
	sign = n < 0 ? 1 : 0;
	if (!(str = (char *)malloc(sizeof(char) * nlen + sign + 1)))
		return (NULL);
	str = str + nlen + sign;
	*str = '\0';
	if (!n)
		*--str = '0';
	while (n != 0)
	{
		*--str = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (sign == 1)
		*--str = '-';
	return (str);
}
