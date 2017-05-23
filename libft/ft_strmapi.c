/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:11:33 by ggane             #+#    #+#             */
/*   Updated: 2016/11/16 08:11:44 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new_s;

	if (!s || !f || !(new_s = ft_strdup(s)))
		return (NULL);
	i = -1;
	while (new_s && new_s[++i])
		new_s[i] = f(i, new_s[i]);
	return (new_s);
}
